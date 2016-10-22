/*
 * Funky piece of code to transmit CW (morse code) with a twist.
 * 
 * Instead of going beep beep, this code makes "chirps", as heard
 * in old radios, like this replica: https://youtu.be/V5Qkk2c4m9E
 * 
 * Another, different, chirp: https://www.youtube.com/watch?v=Ls_Y_USteQQ
 * 
 * It's just for laughs. Enjoy.
 */

// Size of a dot
const int dotLoop = 6;

// Target tone
const int targetTone = 800;

// c1 target when no tone
const unsigned long c1TargetTone = 1300;

// c2 target when no tone
const unsigned long c2TargetTone = 400;

// The tone "after" C1 of the oscillator
unsigned long c1Tone = c1TargetTone;

// The tone "after" C2 of the oscillator
unsigned long c2Tone = c2TargetTone;

void setup() {
  // Where we're going we don't need no setup.
}

void loop() {
  // Sorry, no lookuptables here. Being lazy.
  
  dot();  dash(); dash(); dot();          dashRest();
  dot();  dash();                         dashRest();
  dash(); dash(); dash(); dash(); dash(); dashRest();
  dash(); dash(); dot(); dash();          dashRest();
  dash(); dash(); dot();                  dashRest();
  dash(); dash(); dot(); dot();           dashRest();

  // Wait 4 minutes
  long again = millis() + 1000*60*4;
  while (millis() < again){
    dotRest();
  }
}

void dot(){
  for(int i=0; i<dotLoop; i++){
    int currentTone = calculateTone(targetTone);
    tone(8, currentTone);
    delay(10);
  }
  dotRest();
}

void dash(){
  for(int i=0; i<3*dotLoop; i++){
    int currentTone = calculateTone(targetTone);
    tone(8, currentTone);
    delay(10);
  }
  dotRest();
}

void dotRest(){
  for(int i=0; i<dotLoop; i++){
    int currentTone = calculateTone(0);
    noTone(8);
    delay(10);
  }
}

void dashRest(){
  for(int i=0; i<3*dotLoop; i++){
    int currentTone = calculateTone(0);
    noTone(8);
    delay(10);
  }
}

unsigned int calculateTone(unsigned int targetTone) {
   const int c1Speed = 2;
   const int c2Speed = 300;
  
   if (targetTone == 0) {
     // No sound, deplete the condensers.
     c1Tone = (c1Tone* (c1Speed -1) + c1TargetTone) /  c1Speed;  // Fast filter
     c2Tone = (c2Tone* (c2Speed -1) + c2TargetTone) /  c2Speed;  // Slow filter
     
   } else {
     // Sound, charge the condensers.
     c1Tone = (c1Tone* (c1Speed -1) + targetTone) /  c1Speed;  // Fast filter
     c2Tone = (c2Tone* (c2Speed -1) + targetTone) /  c2Speed;  // Slow filter
   }
  
   return (c1Tone + c2Tone) / 2;
}
 
