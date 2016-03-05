#include <SPI.h>
#include "RF24.h"

const unsigned long DELAY_TIME = 50;
const byte LED = 6;

unsigned long timer = 0;
 
const uint64_t pipe = 0xE8E8F0F0E1LL; // địa chỉ phát
RF24 radio(4, 5);

byte msg[1];


 
void setup(){
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(115200); //serial for atmega328p side
  radio.begin();                     
  radio.setAutoAck(1);              
  radio.setChannel(10);               // Đặt kênh
  radio.openReadingPipe(1,pipe);     
  radio.startListening();        
}
 
void loop(){
  if (radio.available()){
    while (radio.available()){
      radio.read(&msg, sizeof(msg));
      Serial1.write(msg[0]);   
      digitalWrite(LED, HIGH);
    }
    timer = millis();
  }
  
  if (millis() - timer > DELAY_TIME) {
    timer = millis();
    Serial1.write(char(0));
    digitalWrite(LED, LOW);
  }
}
