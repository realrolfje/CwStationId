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

const char PROGMEM CWTEXT[] = "THIS IS YOUR CALL";

void setup() {
  setup_tonegenerator();
}

void loop() {
  cwSendText();
  delay(4000);
}

 
