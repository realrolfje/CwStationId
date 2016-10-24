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
  chirp(100);
  delay(100);
}

void dash(){
  chirp(300);
  delay(100);
}

void dotRest(){
  delay(100);
}

void dashRest(){
  delay(300);
}

 
