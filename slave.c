#include <SoftwareSerial.h>   

 
SoftwareSerial blueToothSerial(6,7);
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  setupBlueToothConnection();
 
} 
 
void loop() 
{ 
  char recvChar;
  while(1){
    if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
    }
    if(Serial.available()){
      recvChar  = Serial.read();
      blueToothSerial.print(recvChar);
    }
  }
} 
 
void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); 
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); 
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); 
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); 
  blueToothSerial.print("\r\n+STAUTO=0\r\n");
  delay(2000); 
  blueToothSerial.print("\r\n+INQ=1\r\n");  
  Serial.println("inquirable");
  delay(2000); 
  blueToothSerial.flush();
}




