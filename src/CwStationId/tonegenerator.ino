#include <TimerOne.h>   

const byte tone_output_pin = 8;
const long standardTone = 600;

long targetTone = 600;
 
// The target tones of the "oscillators" when muted
const long c1TargetTone = 800;
const long c2TargetTone = 425;

// Speed of attack/decay of both oscillators (lower is faster)
const int c1Speed = 2;
const int c2Speed = 50;

// The current tones of both "oscillators"
volatile unsigned int c1Tone = c1TargetTone;
volatile unsigned int c2Tone = c2TargetTone;

// The actual output tone of the oscillators combined
volatile unsigned int currentTone = 0;
volatile boolean soundOn = false;

void setup_tonegenerator() {
  Timer1.initialize(12000);                // microseconds between interrupts
  Timer1.attachInterrupt( calculateTone ); // routine called on interrupt
}

void resetTargetTone() {
  setTargetTone(standardTone);
}

void setTargetTone(long newTone) {
  targetTone = newTone;
  c1Tone = c1TargetTone;
  c2Tone = c2TargetTone;
}

void chirp(unsigned int ms) {
  soundOn = true;
  
  unsigned long start = millis();
  unsigned int oldTone = -1;
  
  while (millis() - start <= ms) {
    
    // Doing this here saves an addition and division in the ISR
    currentTone = (c1Tone + c2Tone) / 2;

    // Only change generated tone when needed.
    if (oldTone != currentTone) {
      tone(tone_output_pin, currentTone);      
      unsigned oldTone = currentTone;
    }
  }
  
  noTone(tone_output_pin);
  soundOn = false;
}

void calculateTone() {
  if (soundOn) {
    c1Tone = c1Tone + ((targetTone - c1Tone) / c1Speed);
    c2Tone = c2Tone + ((targetTone - c2Tone) / c2Speed);   
  } else {
    c1Tone = c1Tone + ((c1TargetTone - c1Tone) / c1Speed);
    c2Tone = c2Tone + ((c2TargetTone - c2Tone) / c2Speed);   
  }
}
