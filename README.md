Introduction
============
Florian is a prototype software + hardware text-to-speech solution. It provides a command-line tool to take program arguments as input, uses the CMU pronouncing dictionary to first convert text to phonemes, then to Speakjet phoneme codes.

It then uses the built-in Teensy UART functionality to stream this to the Teensy over USB, which contains a simple program to interact with the Speakjet and provide buffer management.

The audio output is then run through a passive two pole low-pass filter and an LM386-based amplifier.

Prerequisites for compilation
-----------------------------

Development of both client and embedded code requires the [AVR compiler] (http://www.pjrc.com/teensy/loader.html). This is available for Mac, Windows and Linux. I've had success compiling and running the Florian codebase on both Windows and Mac.

Prerequisites for running
-------------------------

You'll need a Teensy USB development board hooked up to a Speakjet. See [my prototype] (http://deity.co.nz/post/22865128321/florian). The pinouts are fairly easy to discern from the codebase.
