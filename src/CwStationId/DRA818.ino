/*
 * Simple hack for getting the Dorji DRA818V to transmit our audio.
 */
#include <SoftwareSerial.h>

// ctcss frequency ( 0000 - 0038 )
// First 16 frequencies are:
#define  CTCSS_OFF  "0000"
#define  CTCSS_71_9 "0002"
#define  CTCSS-74_4 "0003"
#define  CTCSS-77_0 "0004"
#define  CTCSS-79_7 "0005"
#define  CTCSS-82_5 "0006"
#define  CTCSS-85_4 "0007"
#define  CTCSS-88_5 "0008"
#define  CTCSS-91_5 "0009"
#define  CTCSS-94_8 "0010"
#define  CTCSS-97_4 "0011"
#define CTCSS-100_0 "0012"
#define CTCSS-103_5 "0013"
#define CTCSS-107_2 "0014"
#define CTCSS-110_9 "0015"
#define CTCSS-114_8 "0016"

// bandwith in KHz ( 0= 12.5KHz or 1= 25KHz )
#define BW_12_5 "0"
#define BW_25_0 "1"

#define TX_PIN 10    /* Output, Low is transmit */
#define SLEEP_PIN 7  /* Output, High = active, Low = sleep */
#define SQ_PIN 9     /* Input,  Low is signal detect */

SoftwareSerial draSerial(11, 12); // RX, TX

boolean drabooted = false;
boolean drasleeping = true;

void setup_dra() {
  drawake();
  if (!drabooted) {
    // Wait for the AD818 module to boot.
    delay(4000);
  }

  pinMode(TX_PIN, OUTPUT);
  pinMode(SQ_PIN, INPUT);
  setVHF();
}

void drasleep(){
  digitalWrite(SLEEP_PIN, LOW);  
  drasleeping = true;
}

void drawake(){
  digitalWrite(SLEEP_PIN, HIGH);  
  drasleeping = false;
}

void txOn() {
  if (drasleeping){
    // Makes sure that even after power failure we
    // are transmitting on the correct frequency.
    setup_dra();
  }
  
  waitForFreeChannel();
  Serial.println("TX");

  digitalWrite(TX_PIN, LOW);  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(1000); // TX initialization time of DR818
}

void txOff() {
  Serial.println("RX");
  digitalWrite(TX_PIN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);  
}

// set parameters for DRA818V
void setVHF() {
  draSerial.begin(9600);
  
  // Check if module is online
  draSerial.println("AT+DMOCONNECT");
  printDRAResponse();
  
  // Set frequency
  draSerial.print("AT+DMOSETGROUP=");
  draSerial.print(BW_12_5);     // Bandwith
  draSerial.print(",");
  draSerial.print("145.2250,"); // tx frequency in MHz
  draSerial.print("145.2250,"); // rx frequency in MHz
  draSerial.print(CTCSS_OFF);   // tx CTCSS
  draSerial.print(",3,");       // squelch level  
                                // ( 0 - 8 ); 0 = "open" 
  draSerial.println(CTCSS_OFF); // rx CTCSS
  
  printDRAResponse();
  
  // Set output Volume
  draSerial.println("AT+DMOSETVOLUME=8");
  printDRAResponse();
  
  draSerial.end();
  Serial.println("dra setup done");
}

void waitForFreeChannel() {
  Serial.print("Waiting for free channel...");
  // SQ_PIN needs to be high for a second (no signal)
  int i=100;
  while (i > 0) {
    if (digitalRead(SQ_PIN)) {
      i--;
    } else {
      i = 100;
    }
    delay(10);
  }
  Serial.println("channel free.");
  return;
}

void printDRAResponse() {
    delay(100);
    Serial.print(">");
    while (draSerial.available() > 0) {
      // read the incoming byte:
      char incommingByte = draSerial.read();
      Serial.print(incommingByte);
    }
    Serial.println();
}

