/*  
  Synth 
 
  Example using a potentiometer to control the amplitude of a sinewave
  with Mozzi sonification library. This example has been further modified
  to support more user input control. 

  Demonstrates the use of Oscil to play a wavetable, and analog input for control.

  This example goes with a tutorial on the Mozzi site:
  http://sensorium.github.io/Mozzi/learn/introductory-tutorial/
  
  The circuit:
    Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
    check the README or http://sensorium.github.com/Mozzi/

  Potentiometer connected to analog pin 0:
     Center pin of the potentiometer goes to the analog pin.
     Side pins of the potentiometer go to +5V and ground

 +5V ---|
              /    
  A0 ----\  potentiometer 
              /    
 GND ---|

  Mozzi help/discussion/announcements:
  https://groups.google.com/forum/#!forum/mozzi-users

  Tim Barrass 2013, CC by-nc-sa.
  Modified Oct. 26 by Shea Kennedy
*/

//#include <ADC.h>  // Teensy 3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
//Include these for vibrato functionality
#include <tables/cos2048_int8.h> // table for Oscils to play
#include <mozzi_midi.h> // for mtof
#include <mozzi_fixmath.h>

//the control rate of the vibrato
#define CONTROL_RATE 64 // powers of 2 please

//for sine wave
// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

//for vibrato
// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
//Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCos(COS2048_DATA);
//Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aVibrato(COS2048_DATA);

//pin for vibrato control
const char INPUT_PIN = 0; // set the input for the knob to analog pin 0
const char INPUT_PIN1 = 1; // set the input for the knob to analog pin 1

const byte volume = 100; // this is a multiplication factor to make the audio out louder
//byte intensity = 0; //vibrato intensity
byte decimation = 0; //decimation intensity
byte pitch = 0; //pitch intensity


void setup(){
  startMozzi(CONTROL_RATE);
//  aSin.setFreq(1760);
//  aVibrato.setFreq(15.f);
  startMozzi(); // :))
}


void updateControl(){
  // read the variable resistor for volume
  int sensor_value = mozziAnalogRead(INPUT_PIN); // value is 0-1023
  int sensor_value1 = mozziAnalogRead(INPUT_PIN1); // value is 0-1023
  
  // map it to an 8 bit range for efficient calculations in updateAudio
  decimation = map(sensor_value, 0, 1023, 1, 255);  
  pitch = map(sensor_value1, 0, 1023, 0, 255);
  aSin.setFreq(760+(10*pitch));
  
  // print the value to the Serial monitor for debugging
  //Serial.print("volume = ");
  //Serial.println((int)volume);
}


int updateAudio(){
  //Q15n16 vibrato = (Q15n16) aVibrato.next();
  //return aCos.phMod(vibrato); // phase modulation to modulate frequency
  return ((int)aSin.next() * volume *decimation)>>8; // shift back into range after multiplying by 8 bit value
}


void loop(){
  audioHook(); // required here
}
