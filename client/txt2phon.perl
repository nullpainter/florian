#
#  The following program converts English written texts into sequences of 
# phonemes suitable for controlling the Speakjet speech synthesizer chip. 
# It therefore makes use of the Carnegie Mellon Pronounciation dictionary.
# The program reads texts from text files and writes phoneme sequence to 
# output files.
# 
# 08-FEB-2009, B. Ulmann fecit (ulmann@vaxman.de, http://www.vaxman.de).
#

use strict;
use warnings;
use Time::HiRes qw/usleep/;

my $debug = 1;
my $dictionary_file = 'cmudict.0.7a';
my $device = 'LTA32:';

my %cmu2sj =
(
  AA0 => 'AW',
  AA1 => 'AW',
  AA2 => 'AW',
  AE0 => 'AY',
  AE1 => 'AY',
  AE2 => 'AY',
  AH0 => 'EY',
  AH1 => 'UX',
  AH2 => 'UX',
  AO0 => 'OH',
  AO1 => 'AW AW',
  AO2 => 'AW AW',
  AW0 => 'OW',
  AW1 => 'AXUW',
  AW2 => 'AXUW',
  AY0 => 'OHIH',
  AY1 => 'OHIH',
  AY2 => 'OHIH',
  B   => 'EB',
  CH  => 'CH',
  D   => 'ED',
  DH  => 'DH',
  EH0 => 'EH',
  EH1 => 'EH',
  EH2 => 'EH',
  ER0 => 'AXRR',
  ER1 => 'AXRR',
  ER2 => 'AXRR',
  EY0 => 'EY',
  EY1 => 'EYIY',
  EY2 => 'EYIY',
  F   => 'FF',
  G   => 'GE',
  HH  => 'HE',
  IH0 => 'IH',
  IH1 => 'IH',
  IH2 => 'IH IH',
  IY0 => 'IY',
  IY1 => 'IY IY',
  IY2 => 'IY IY IY',
  JH  => 'JH',
  K   => 'KE', # EK?
  L   => 'LE',
  M   => 'MM',
  N   => 'NE',
  NG  => 'NGE',
  OW0 => 'OH',
  OW1 => 'OW OW',
  OW2 => 'OW OW',
  OY0 => 'OWIY',
  OY1 => 'OWIY',
  OY2 => 'OWIY',
  P   => 'PO', # PE?
  R   => 'RR',
  S   => 'SE',
  SH  => 'SH',
  T   => 'TT',
  TH  => 'DH',
  UH0 => 'UH',
  UH1 => 'UH UH',
  UH2 => 'UH UH',
  UW0 => 'UW',
  UW1 => 'UW UW',
  UW2 => 'UW UW UW',
  V   => 'VV',
  W   => 'WW',
  Y   => 'IYEH',
  Z   => 'ZZ',
  ZH  => 'ZH',
);

open DICT, "<$dictionary_file" or 
  die "Could not open dictionary $dictionary_file!\n";

my %dictionary;
my $dictionary_counter = 0;

while (chomp (my $line = <DICT>))
{
  next if $line =~ m/^##/;

  # Perform some preprocessing
  my ($word, $pron) = $line =~ m/^(\S+)\s+(.*)$/;
  $word = uc ($word);
  $pron = uc ($pron);

  # Skip over comments
  if ($word eq ";;;") {
   next;
  }

  my $speak_pron = '';
  for my $value (split (/\s+/, $pron))
  {
    if ($cmu2sj{$value})
    {
      $speak_pron .= "$cmu2sj{$value} ";
    }
    else
    {
      die "Could not find phoneme $value in conversion dictionary!\n";
    }
  }

  $dictionary{$word} = $speak_pron;
  print "\r$dictionary_counter" if !(++$dictionary_counter % 1000);

#  last if $dictionary_counter > 1000;
}
print "\r$dictionary_counter entries read from $dictionary_file.\n" if $debug;

close DICT;

# End of preliminaries - now convert the raw text to a phoneme stream.
print 'Please enter input filename: ';
while (chomp (my $input_file = <STDIN>))
{
  print "Reading input file $input_file...\n";
  open INPUT, "<$input_file" or die "Could not open input file $input_file!\n";
  my @input = <INPUT>;
  close INPUT;

  my $text = join (' ', @input);

  # Preprocess raw text data
  print "Raw data: $text\n" if $debug;
  $text = uc ($text);
  $text =~ tr/(),;'"?!:/      .../;
  $text =~ s/-/ /g; # No hyphens between words allowed!

  $text =~ s/\s+/\|/sg; # Insert proper word delimiters
  $text =~ s/\./\|\./sg;

  my @elements = split (/\|/, $text);
  my $translated = '';
  for my $word (@elements)
  {
    if ($word eq '.')
    {
      $translated .= ' P3 _ ';
    }
    else
    {
      if ($dictionary{$word})
      {
        $dictionary{$word} =~ s/IYEH EY/IYEH/g;    # Eg. "formulation"
        $dictionary{$word} =~ s/IYEH IH RR/IYRR/g; # Eg. "years"
        $translated .= "$dictionary{$word} P5 _ ";
      }
      else
      {
        $translated .= ' M0 P5 _ ';
      }
    }
  }

  $translated =~ s/_ /_\n/g;
  print "Translated text: $translated\n" if $debug;

  my $output_file = $input_file;
  $output_file =~ s/^(.+)\..+$/$1.pho/;
  print "Writing output file $output_file...\n";

  open OUTPUT, ">$output_file" or die "Could not open $output_file!\n";
  print OUTPUT "$translated\n";
  close OUTPUT;

  print 'Please enter input filename: ';
}
