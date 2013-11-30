// RFID reader for Arduino 
// Wiring version by BARRAGAN <http://people.interaction-ivrea.it/h.barragan> 
// Modified for Arudino by djmatic
// Re-Modified for Arduino and 125Khz JsxzLz RFID Kit from Ebay by Biohazard

// RFID reader comes with 11 pins: D3 D2 D1 Rest Mcst Gnd L1 L2 PC TX VCC
// We need these to be connected:
// Rest to Arduino pin 2
// Gnd to Arduino GND
// L1 and L2 to the antenna
// TX to Arduino RX0
// VCC To Arduino 5V


int  val = 0; 
char code[14];
// 2 digits manufacture code
// 10 digits card code
// 2 digits parity bits

int bytesread = 0; 

void setup() { 

  Serial.begin(9600);     // RFID reader TX pin, Baud rate: 9600, Data bits: 8, stop bit: 1.
  pinMode(2,OUTPUT);      // Set digital pin 2 as OUTPUT to connect it to the RFID RESET pin 
  digitalWrite(2, HIGH);  // Activate the RFID reader
}  


void loop() { 

  if(Serial.available() > 0) {            // if data available from reader 
    if((val = Serial.read()) == 10) {     // check for header 
      bytesread = 0; 
      while(bytesread < 14) {             // read 14 digit code 
        if( Serial.available() > 0) { 
          val = Serial.read(); 
          if((val == 10)||(val == 13)) {  // if header or stop bytes before the 10 digit reading 
            break;                        // stop reading 
          } 
          code[bytesread] = val;          // add the digit           
          bytesread++;                    // ready to read next digit  
        } 
      } 
      if(bytesread == 14) {               // if 14 digit read is complete 
        Serial.print("TAG code is: ");    // possibly a good TAG 
        Serial.println(code);             // print the TAG code 
      } 
      bytesread = 0; 
      digitalWrite(2, LOW);               // deactivate the RFID reader for a moment so it will not flood
      delay(1500);                        // wait for a bit 
      digitalWrite(2, HIGH);              // Activate the RFID reader
    } 
  } 
} 
