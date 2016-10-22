
// Modeled after transmitters like this one:
// https://youtu.be/V5Qkk2c4m9E

void setup() {
  // put your setup code here, to run once:

}

// Size of a dot
int dotLoop = 6;

// Target tone
int targetTone = 800;

// c1 target when no tone
unsigned long c1TargetTone = 1300;

// c2 target when no tone
unsigned long c2TargetTone = 400;

// The tone "after" C1 of the oscillator
unsigned long c1Tone= c1TargetTone;

// The tone "after" C2 of the oscillator
unsigned long c2Tone= c2TargetTone;

void loop() {
  dot();  dash(); dash(); dot();          dashRest();
  dot();  dash();                         dashRest();
  dash(); dash(); dash(); dash(); dash(); dashRest();
  dash(); dash(); dot(); dash();          dashRest();
  dash(); dash(); dot();                  dashRest();
  dash(); dash(); dot(); dot();           dashRest();

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

int calculateTone(int targetTone) {
   int c1Speed = 2;
   int c2Speed = 300;
  
   if (targetTone == 0) {
     c1Tone = (c1Tone* (c1Speed -1) + c1TargetTone) /  c1Speed;  // Fast filter
     c2Tone = (c2Tone* (c2Speed -1) + c2TargetTone) / c2Speed;  // Slow filter
     
   } else {
     c1Tone = (c1Tone* (c1Speed -1) + targetTone) /  c1Speed;  // Fast filter
     c2Tone = (c2Tone* (c2Speed -1) + targetTone) / c2Speed;  // Slow filter
   }
  
   unsigned int combined = c1Tone + c2Tone;
   return combined / 2;
}

