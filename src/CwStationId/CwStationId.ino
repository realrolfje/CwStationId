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

const char PROGMEM CWTEXT[] = "= FUN FOX =";

void setup() {
  setup_tonegenerator();
  setup_dra();

  txOn();
  cwSendText();
  txOff();
  delay(2000);
}

void loop() {
  byte choice = random(4); // random from 0-3
  txOn();
  switch (choice) {
    case 1: downlow(); break;
    case 2: tatu(); break;
    case 3: beepbop(); break;
    default: cwSendText();
  }
  txOff();

  delay(random(4000, 10000));
}

void tatu(){
  for (int i=0; i<random(5,20); i++) {
    setTargetTone(800);
    chirp(500);
    setTargetTone(500);
    chirp(500);
  }
}

void beepbop(){
  for(int i=0; i<random(50,150); i++) {
    setTargetTone(random(300, 1000));
    chirp(random(50,300));
    delay(random(50,300));
  }
  resetTargetTone();
}

void downlow() {
  setTargetTone(80);
  chirp(2000);
  resetTargetTone();
}

