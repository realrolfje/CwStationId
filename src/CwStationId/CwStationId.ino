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

// Duration in mS of a dot.
const int dotTime = 90;

void setup() {
  setup_tonegenerator();
}

void loop() {
  // Sorry, no lookuptables here. Being lazy.
  
  dot();  dash(); dash(); dot();          dashRest();
  dot();  dash();                         dashRest();
  dash(); dash(); dash(); dash(); dash(); dashRest();
  dash(); dash(); dot(); dash();          dashRest();
  dash(); dash(); dot();                  dashRest();
  dash(); dash(); dot(); dot();           dashRest();

  delay(4000);
}

void dot() {
  chirp(dotTime);
  delay(dotTime);
}

void dash(){
  chirp(3* dotTime);
  delay(dotTime);
}

void dotRest(){
  delay(dotTime);
}

void dashRest(){
  delay(3 * dotTime);
}

 
