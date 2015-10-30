# CS-207 - Four Step Sequencer/Synthesizer

DESCRIPTION:

  The aim of this project is to build a device that both functions as a simple synthesizer as well as a four-step      sequencer. 

  This project focuses on the creation of an Arduino sketch (program) which will rely on a sound synthesis library     called Mozzi to output a variety of sound waveforms. A physical interface will be constructed consisting of inputs   like: switches, knobs and sliders that will be used to take in user inputs and will alter or modify the sound being   output by the synthesizer. Furthermore the project will look at arranging the synthesized sound in to a pattern of   notes (a sequence) which the user can also manipulate through user inputs.
  
FEATURES:
  The synthesizer being built will consist of the following features:
  
  Wave Type Selection - a knob which allows the user to select the type of waveform that is 	being output by the      synthesizer
  
  Decimation - a knob which controls a variable that will be multiplied by the current output wave signal at a         specified rate thus changing the waves amplitude and decimating the sound produced.
  
  Pitch - a knob which will alter the pitch of the sound being output by the synthesizer.
  
  Master Volume - a slider which controls the volume of the output sound.
  
  Audio Out Jack - a 1/4” output jack which will allow the user to listen to the produced sound with headphones or     hook the synthesizer up to an amplifier.

  The sequencer will consist of the following features:

  Tempo - a knob which controls the speed at which the sounds in the sequence are	triggered.
  
  Step Pattern Selection - a switch which allows the user to choose the pattern in which 	the notes play. The first    pattern will be the original pattern which is in the order 1-2-3-4. The second pattern will be a reversed pattern    which plays the notes in the order 4-3-2-1.
  

CONFIGURATION:

  The schematic for this project is still under construction. The provided schematic below is not yet up to date.
  
  ![Schematic](http://s9.postimg.org/9uym9ce73/Screen_Shot_2015_10_30_at_4_59_21_PM.png)

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

  This project is liscenced under (CC BY 4.0). More information on this liscence can be found in the Liscence.txt      file.

CREDITS:

  There are two sources of inspiration to be credited for this project idea:

  The first is an eight-step Arduino sequencer created by Instructables user TobaTobias found at the following link: 
  http://www.instructables.com/id/Arduino-Step-Sequencer/

  The second is a four-step Arduino sequencer that utilizes the Mozzi Library. This project was created by Denny       George and is found at the following link:
  https://anarcissist.wordpress.com/2013/11/09/arduino-noise-four-step-sequencer/

  The example sketch that will be implemented and modified for this project is sinewave.ino, (Barrass, 2012). This     example works by outputting a sine wave by referencing one of Mozzi’s wavetables.

  I'd also like to credit the MOZZI library for it's use in this project.

CONTACT INFORMATION:

  Email: sheamkennedy@gmail.com

