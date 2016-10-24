/*
 * Simple hack for getting the Dorji DRA818V to transmit our audio.
 */

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

#define TX_PIN 10

void setup_dra() {
  // Wait for the AD818 module to boot.
  delay(100);
  setVHF();
}

void txOn(){
  digitalWrite(TX_PIN, HIGH);  
}

void txOff(){
  digitalWrite(TX_PIN, LOW);
}

// set parameters for DRA818V
void setVHF() {
  Serial.begin(9600);
  Serial.print("AT+DMOSETGROUP=");
  Serial.print(BW_12_5);     // Bandwith
  Serial.print(",");
  Serial.print("145.2250,"); // tx frequency in MHz
  Serial.print("145.2250,"); // rx frequency in MHz
  Serial.print(CTCSS_OFF);   // tx CTCSS
  Serial.print(",3,");       // squelch level  
                             // ( 0 - 8 ); 0 = "open" 
  Serial.println(CTCSS_OFF); // rx CTCSS

  // Although we could read the response here, for
  // we will assume it went well and ignore the
  // response.
  delay(5);
  
  // Set output Volume
  Serial.println("AT+DMOSETVOLUME=8");
  Serial.end();
}
