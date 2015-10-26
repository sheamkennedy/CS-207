# CS-207 - Four Step Sequencer/Synthesizer

DESCRIPTION:

  The aim of this project is to build a device that both functions as a simple synthesizer as well as a four-step      sequencer. 

  This project focuses on the creation of an Arduino sketch (program) which will rely on a sound synthesis library     called Mozzi to output a variety of sound waveforms. A physical interface will be constructed consisting of inputs   like: switches, knobs and sliders that will be used to take in user inputs and will alter or modify the sound being   output by the synthesizer. Furthermore the project will look at arranging the synthesized sound in to a pattern of   notes (a sequence) which the user can also manipulate through user inputs.

CONFIGURATION:

  The schematic for this project is still under construction. No configuration is currently available.

INSTALLATION INSTRUCTIONS:

  This project relies on the MOZZI library. To install the MOZZI library follow these instructions:
  
  1) Download the MOZZI library here: http://sensorium.github.io/Mozzi/
  
  2) Unzip the downloaded file and name the resulting file as something useful like MOZZI.
  
  3) Now in the Arduino IDE go to Sketch > Import Library and select Add Library from the dropdown list.
  
  4) Find the unzipped MOZZI folder on your computer and open it. You should now see the MOZZI library at the bottom   of the dropdown menu. This means that the library was installed and is now available for you to use in your          project.

MANIFEST:
  
  So far this project includes the following files:
  
  MozziGuts.h
  
  Oscil.h
  
  tables/sin2048_int8.h
  
  tables/cos2048_int8.h
  
  mozzi_midi.h
  
  mozzi_fixmath.h

COPYRIGHT NOTICE:

This project is liscenced under (CC BY 4.0). More information on this liscence can be found in the Liscence.txt file.

CREDITS:

There are two sources of inspiration to be credited for this project idea:

The first is an eight-step Arduino sequencer created by Instructables user TobaTobias found at the following link: 
http://www.instructables.com/id/Arduino-Step-Sequencer/

The second is a four-step Arduino sequencer that utilizes the Mozzi Library. This project was created by Denny George and is found at the following link:
https://anarcissist.wordpress.com/2013/11/09/arduino-noise-four-step-sequencer/

I'd also like to credit the MOZZI library for it's use in this project.

CONTACT INFORMATION:

Email: sheamkennedy@gmail.com

