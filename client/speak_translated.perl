#
#  The following program reads the contents of a file containing a phoneme
# sequence for the Speakjet chip, converts it into a corresponding byte
# sequence which is sent to the speech synthesizer.
#  Please note that the serial line used in the following is named "LTA32:"
# which obviously is an OpenVMS LAT-device name. To use this program on 
# any other system, the only thing necessary to change should be this 
# device definition.
# 
# 08-FEB-2009, B. Ulmann fecit (ulmann@vaxman.de, http://www.vaxman.de).
#

use strict;
use warnings;
use Time::HiRes qw/usleep/;

die "Usage: speak_translated <filename>\n" if @ARGV != 1;

my $debug = 1;
my $input_file = $ARGV[0];

###############################################################################

#
# The following hash contains all allophones which can be spoken by the 
# SpeakJet chip.
#
my %allophone = 
(
  P0   => [0, 0],    # Pauses
  P1   => [1, 100],
  P2   => [2, 200],
  P3   => [3, 700],
  P4   => [4, 30],
  P5   => [5, 60],
  P6   => [6, 90],
  FAST => [7, 0],    # Play next phoneme with double speed
  SLOW => [8, 0],    # Play next phoneme 1.5 times slower
  STRS => [9, 0],    # Play next phoneme with a bit stress in the voice
  RELX => [10, 0],   # Relax again...
  IY   => [128, 70],
  IH   => [129, 70],
  EY   => [130, 70],
  EH   => [131, 70],
  AY   => [132, 70],
  AX   => [133, 70],
  UX   => [134, 70],
  OH   => [135, 70],
  AW   => [136, 70],
  OW   => [137, 70],
  UH   => [138, 70],
  UW   => [139, 70],
  MM   => [140, 70],
  NE   => [141, 70],
  NO   => [142, 70],
  NGE  => [143, 70],
  NGO  => [144, 70],
  LE   => [145, 70],
  LO   => [146, 70],
  WW   => [147, 70],
  RR   => [148, 70],
  IYRR => [149, 200],
  EYRR => [150, 200],
  AXRR => [151, 190],
  AWRR => [152, 200],
  OWRR => [153, 185],
  EYIY => [154, 165],
  OHIY => [155, 200],
  OWIY => [156, 225],
  OHIH => [157, 185],
  IYEH => [158, 170],
  EHLL => [159, 140],
  IYUW => [160, 180],
  AXUW => [161, 170],
  IHWW => [162, 170],
  AYWW => [163, 200],
  OWWW => [164, 131],
  JH   => [165, 70],
  VV   => [166, 70],
  ZZ   => [167, 70],
  ZH   => [168, 70],
  DH   => [169, 70],
  BE   => [170, 45],
  BO   => [171, 45],
  EB   => [172, 10],
  OB   => [173, 10],
  DE   => [174, 45],
  DO   => [175, 45],
  ED   => [176, 10],
  OD   => [177, 10],
  GE   => [178, 55],
  GO   => [179, 55],
  EG   => [180, 55],
  OG   => [181, 55],
  CH   => [182, 70],
  HE   => [183, 70],
  HO   => [184, 70],
  WH   => [185, 70],
  FF   => [186, 70],
  SE   => [187, 40],
  SO   => [188, 40],
  SH   => [189, 50],
  TH   => [190, 40],
  TT   => [191, 50],
  TU   => [192, 70],
  TS   => [193, 170],
  KE   => [194, 55],
  KO   => [195, 55],
  EK   => [196, 55],
  OK   => [197, 45],
  PE   => [198, 99],
  PO   => [199, 99],
  R0   => [200, 80],
  R1   => [201, 80],
  R2   => [202, 80],
  R3   => [203, 80],
  R4   => [204, 80],
  R5   => [205, 80],
  R6   => [206, 80],
  R7   => [207, 80],
  R8   => [208, 80],
  R9   => [209, 80],
  A0   => [210, 300],
  A1   => [211, 101],
  A2   => [212, 102],
  A3   => [213, 540],
  A4   => [214, 530],
  A5   => [215, 500],
  A6   => [216, 135],
  A7   => [217, 600],
  A8   => [218, 300],
  A9   => [219, 250],
  B0   => [220, 200],
  B1   => [221, 270],
  B2   => [222, 280],
  B3   => [223, 260],
  B4   => [224, 300],
  B5   => [225, 100],
  B6   => [226, 104],
  B7   => [227, 100],
  B8   => [228, 270],
  B9   => [229, 262],
  C0   => [230, 160],
  C1   => [231, 300],
  C2   => [232, 182],
  C3   => [233, 120],
  C4   => [234, 175],
  C5   => [235, 350],
  C6   => [236, 160],
  C7   => [237, 260],
  C8   => [238, 95],
  C9   => [239, 75],
  D0   => [240, 95],
  D1   => [241, 95],
  D2   => [242, 95],
  D3   => [243, 95],
  D4   => [244, 95],
  D5   => [245, 95],
  D6   => [246, 95],
  D7   => [247, 95],
  D8   => [248, 95],
  D9   => [249, 95],
  D10  => [250, 95],
  D11  => [251, 95],
  M0   => [252, 120],
  M1   => [253, 250],
  M2   => [254, 530],
);

open INPUT, "<$input_file" or die "Could not open $input_file!\n";

my ($duration, $word) = (0, '');
while (my $line = <INPUT>)
{
  for my $phoneme (split (/\s+/, $line))
  {
    next unless $phoneme;
    if ($phoneme eq '_')
    {
      printf ("%60s: %d ms\n", $word, $duration) if $debug;
      usleep ($duration * 1300);
      ($duration, $word) = (0, '');
    }
    else
    {
      $word .= $phoneme;
      $duration += $allophone{$phoneme}[1];
      print chr($allophone{$phoneme}[0]);
    }
  }
}

close INPUT
