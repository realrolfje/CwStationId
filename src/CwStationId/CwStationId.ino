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

const char PROGMEM CWTEXT[] = "TEST";

void setup() {
  Serial.begin(9600);
  txOff();
  setup_tonegenerator();
  pinMode(LED_BUILTIN, OUTPUT);
  setup_dra();
}

void loop() {
  
  byte choice = random(5); // random from 0-4
  
//  choice = 10; // always default
  
  txOn();

  switch (choice) {
    case 1: downlow(); break;
    case 2: tatu(); break;
    case 3: beepbop(); break;
    case 4: diewdiewdiew(); break;
    default: cwSendText();
  }
  txOff();
  drasleep();

  delay(random(4000, 10000));
}

void tatu(){
  Serial.println("tatu");
  for (int i=0; i<random(5,20); i++) {
    setTargetTone(800);
    chirp(500);
    setTargetTone(500);
    chirp(500);
  }
}

void beepbop(){
  Serial.println("beepbop");
  for(int i=0; i<random(50,150); i++) {
    setTargetTone(random(300, 1000));
    chirp(random(50,300));
    delay(random(50,300));
  }
  resetTargetTone();
}

void downlow() {
  Serial.println("downlow");
  setTargetTone(80);
  chirp(2000);
  resetTargetTone();
}

const int diewtime = 130;
void diewdiewdiew(){
    Serial.println("diewdiewdiew");

    // P
    diewdit(); diewdah(); diewdah(); diewdit();
    delay(6*diewtime);

    // I
    diewdit(); diewdit();
    delay(6*diewtime);
    
    // 4
    diewdit(); diewdah(); diewdah(); diewdah(); diewdah(); 
    delay(6*diewtime);

   // etcetera
}

void diewdit(){
    chirp(diewtime); delay(diewtime);
    delay(3*diewtime);
}

void diewdah(){
    chirp(diewtime); delay(diewtime);
    chirp(diewtime); delay(diewtime);
    chirp(diewtime); delay(diewtime);
    delay(3*diewtime);
}

