#include <SPI.h>
#include "RF24.h"


const byte LED = 6;
const uint64_t pipe = 0xE8E8F0F0E1LL; // địa chỉ để phát
RF24 radio(4, 5);
byte msg[1];
int value = 0;

 
void setup(){ 
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
  //============================================================Module NRF24
  radio.begin();                     
  radio.setAutoAck(1);               
  radio.setRetries(1,1);       
  radio.setPALevel(RF24_PA_MAX);      // Dung lượng tối đa
  radio.setChannel(10);               // Đặt kênh
  radio.openWritingPipe(pipe);        // mở kênh

  
}
 
void loop(){
  while (!Serial1.available())
    digitalWrite(LED, LOW);
  msg[0] = Serial1.read();
  radio.write(&msg, sizeof(msg));
  digitalWrite(LED, HIGH);
}
