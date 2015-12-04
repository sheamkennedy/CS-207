/*  
  Synth 
  
  This program consists of 2 parts: a synthesizer and a 16-step apreggiator. 
  
  Part 1)
  The synthesizer allows the user to choose a specific waveform to be sounded and for 
  vibrato to be turned on or off. The synthesizer has a master volume control, decimator 
  control and a pitch control knob for modifying the sound.
  
  Part 2)
  The arpeggiator takes the synthesized sound and plays it in a 16-step pattern in
  which each step in the pattern is of a different pitch. There are 2 patterns to 
  choose from using a switch. A tempo knob has also been implemented to control
  the speed of the arpeggio.
  
  The circuit:
  A schematic of this circuit can be found in README.md at the following link
  https://github.com/sheamkennedy/CS-207/blob/master/README.md
  Mozzi help/discussion/announcements:
  https://groups.google.com/forum/#!forum/mozzi-users
  
  Tim Barrass 2013, CC by-nc-sa.
  Modified Nov. 21 by Shea Kennedy
*/

// Include stuff needed for Mozzi program
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template

// Include the waveform tables being used by the synthesizer
#include <tables/sin2048_int8.h> // Sine wavetable
#include <tables/triangle2048_int8.h> // Sriangle wavetable
#include <tables/saw2048_int8.h> // Saw wavetable
#include <tables/square_analogue512_int8.h> // Square wavetable

// Include delay for use in arpeggio
#include <EventDelay.h> // Since Mozzi does not allow delay commands to be used we use this instead

// Include these for vibrato functionality
#include <tables/cos2048_int8.h> // Cos wavetable for vibrato's oscillator
#include <mozzi_midi.h> // For mtof
#include <mozzi_fixmath.h>

// Defines the control rate of the Mozzi
#define CONTROL_RATE 64 // must be a power of 2

// For all of the sound waves being used
// Use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
// Gives meaningful names to our waveforms
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
Oscil<TRIANGLE2048_NUM_CELLS, AUDIO_RATE> aTriangle(TRIANGLE2048_DATA);
Oscil<SAW2048_NUM_CELLS, AUDIO_RATE> aSaw(SAW2048_DATA);
Oscil<SQUARE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aSquare(SQUARE_ANALOGUE512_DATA);

// Give our event delay a meaningful variable name
EventDelay arpeggioChangeDelay;

// For the waves being used to create vibrato
// Use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
// Gives meaningful names to our waveforms
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCos(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aVibrato(COS2048_DATA);

// Set analog pins as inputs so we can use potentiometers to control the device
const char INPUT_PIN = 0; // set the input for the knob to analog pin 0
const char INPUT_PIN1 = 1; // set the input for the knob to analog pin 1
const char INPUT_PIN2 = 2; // set the input for the knob to analog pin 2

// Set up digital pins to be used as switches 
#define STOP_PIN 7 // Switch for arpeggios pattern change
#define STOP_PIN2 8 // First switch for choosing waveform
#define STOP_PIN3 10 // Second switch for choosing waveform
#define STOP_PIN4 6 // Switch for turning on/off vibrato (works by setting the variable "depth")

// Constants
const byte volume = 100; // This is a multiplication factor to make the audio out louder if higher or quiter if lower

// Global Variables
byte decimation = 0; // Decimation intensity
byte pitch = 0; //Pitch intensity
char arpstep = 1; // Arpeggiator step
byte pitchstep = 0; // Pitch step
byte tempo = 0; // Tempo of arpeggiator
byte switchSetting = 0; // Variable to store the setting of a series of switches to determine which waveform should play
float depth = 0.1; // Depth of vibrato

// This is our initializing statement/setup:
void setup(){
  // Setup up digital pins as inputs
  pinMode(STOP_PIN, INPUT);
  pinMode(STOP_PIN2, INPUT);
  pinMode(STOP_PIN3, INPUT);
  pinMode(STOP_PIN4, INPUT);
  
  // Begins Mozzi at the control rate specified above
  startMozzi(CONTROL_RATE);

  // Set the vibrato's frequency here since it is to be constant
  aVibrato.setFreq(1500.0f);

  // Initialize the arpeggiators tempo
  //arpeggioChangeDelay.set(tempo);
  
}

//This updates what the value being read from the potentiometers is at any given time:
void updateControl(){
  // Read analog pin values
  int sensor_value = mozziAnalogRead(INPUT_PIN); // Read potentiometer value for tempo
  int sensor_value1 = mozziAnalogRead(INPUT_PIN1); // Read potentiometer value for pitch
  int sensor_value2 = mozziAnalogRead(INPUT_PIN2); // Read potentiometer value for decimator

  // Read digital pin values
  int patternSwitch = digitalRead(STOP_PIN); // Reads switch value for pattern
  int patternSwitch2 = digitalRead(STOP_PIN2); // Reads switch 1 value for waveform
  int patternSwitch10 = digitalRead(STOP_PIN3); // Reads switch 2 value for waveform
  int vibratoSwitch = digitalRead(STOP_PIN4); // Reads switch value for vibrato

  // A formula that determines the degree of vibrato based on the depth
  float vibrato = depth * aVibrato.next();
  
  // Change global variables based on the orientation of each analog potentiometer
  tempo = map(sensor_value, 1, 1023, 0, 255); // Starts at 1 because we don't want tempo to be zero
  pitch = map(sensor_value1, 0, 1023, 0, 255);
  decimation = map(sensor_value2, 0, 1023, 1, 255); // Starts at 1 so decimation can equal zero

  // Updates argeggio to match newly set tempo
  arpeggioChangeDelay.set(tempo);

  // Condition checks if switch is on/off and sets vibrato depth accordingly
  if(vibratoSwitch == LOW){ 
    depth = 0; // When depth is zero the vibrato becomes zero (off)
  } else if(vibratoSwitch == HIGH){ 
    depth = 0.1; // Vibrato turns (on) with a depth factor of 0.1
  }

  // Condition checks orientation of pattern switch and plays the corresponding pattern
  if(patternSwitch == LOW){
  for(int arpeggio = 0; arpeggio < 5; arpeggio++){
    // Condition checks if tempo delay has carried out before proceeding
    if(arpeggioChangeDelay.ready()){
      arpstep = 1-arpstep; // Changes arpstep between values 0 and 1 (if 0 we hear silence, if 1 we hear sound)
      pitchstep = pitchstep + 1; // Increments the step of the arpeggio we are on (there are a total of 16 steps)
      // Reset pitchstep once we have reached the final step in the arpeggio
      if(pitchstep == 32){
        pitchstep = 0;
      }
      arpeggioChangeDelay.start(); // Delay before playing next note in arpeggio based on tempo 
    }
    // Set the overall pitch of all waveforms (note only one is actually playing)
    aSin.setFreq(760+(10*pitch)+(pitchstep*120) + vibrato);
    aTriangle.setFreq(760+(10*pitch)+(pitchstep*120) + vibrato);
    aSaw.setFreq(760+(10*pitch)+(pitchstep*120) + vibrato);
    aSquare.setFreq(760+(10*pitch)+(pitchstep*120) + vibrato);
  }
  } else {
  for(int arpeggio = 0; arpeggio < 5; arpeggio++){
    // Condition checks if tempo delay has carried out before proceeding
    if(arpeggioChangeDelay.ready()){
      arpstep = 1-arpstep; // Changes arpstep between values 0 and 1 (if 0 we hear silence, if 1 we hear sound)
      pitchstep = pitchstep + 1; // Increments the step of the arpeggio we are on (there are a total of 16 steps)
      // Reset pitchstep once we have reached the final step in the arpeggio
      // 32 because there is a 16-step sequence containing 16 sound on's and 16 sound off's
      
      if(pitchstep == 32){ 
        pitchstep = 0;
      }
      arpeggioChangeDelay.start(); // Delay before playing next note in arpeggio based on tempo 
    }  
    // Set the overall pitch of all waveforms (note only one is actually playing)
    aSin.setFreq(760+(10*pitch)+(pitchstep*960) + vibrato);
    aTriangle.setFreq(760+(10*pitch)+(pitchstep*960) + vibrato);
    aSaw.setFreq(760+(10*pitch)+(pitchstep*960) + vibrato);
    aSquare.setFreq(760+(10*pitch)+(pitchstep*960) + vibrato);
  }    
  }

  // This series of if-else statements checks the orientation of 2 switches which together have a combined number
  // of 4 possible orientations. A specific waveform is output based on the switch combination.
  if((patternSwitch2 == HIGH) && (patternSwitch10 == HIGH)){
    switchSetting = 0; // Sets variable which is applied later on to determine the waveform being output
  }
  else if((patternSwitch2 == LOW) && (patternSwitch10 == HIGH)){
    switchSetting = 1; // Sets variable which is applied later on to determine the waveform being output
  }
  else if((patternSwitch2 == LOW) && (patternSwitch10 == LOW)){
    switchSetting = 2; // Sets variable which is applied later on to determine the waveform being output
  }
  else if((patternSwitch2 == HIGH) && (patternSwitch10 == LOW)){
    switchSetting = 3; // Sets variable which is applied later on to determine the waveform being output
  }
  
  // Print any value to the Serial monitor for debugging purposes
  Serial.begin(9600);
  Serial.print("arpstep = ");
  Serial.println((int)arpstep);
}

// This is the audio which is output from the synthesizer
int updateAudio(){ 
  // Outputs particular waveforms based on the condition of switchSetting variable
  if(switchSetting == 0){
    return ((int)aSin.next()*volume*decimation*arpstep)>>8; // Shift back into range after multiplying by 8 bit value  
  }
  else if(switchSetting == 1){
    return ((int)aTriangle.next()*volume*decimation*arpstep)>>8; // Shift back into range after multiplying by 8 bit value  
  }
  else if(switchSetting == 2){
    return ((int)aSaw.next()*volume*decimation*arpstep)>>8; // Shift back into range after multiplying by 8 bit value  
  }
  else if(switchSetting == 3){
    return ((int)aSquare.next()*volume*decimation*arpstep)>>8; // Shift back into range after multiplying by 8 bit value  
  }    
}

// This loops through updateAudio() automatically so changes to updateAudio() are heard instantly
void loop(){
  audioHook(); // This is required y Mozzi to carry out the automatic update
}
