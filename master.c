#include <SoftwarwSerial.h>   
#define RxD 6
#define TxD 7
 

String retSymb = "+RTINQ="; 
String slaveName = ";SeeedBTSlave";
int nameIndex = 0;
int addrIndex = 0;

String recvBuf;
String slaveAddr;

String connectCmd = "\r\n+CONN=";

SoftwareSerial blueToothSerial(RxD,TxD);
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  
  delay(1000);
  Serial.flush();
  blueToothSerial.flush();
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
  blueToothSerial.print("\r\n+STWMOD=1\r\n");
  blueToothSerial.print("\r\n+STNA=SeeedBTMaster\r\n");
  blueToothSerial.print("\r\n+STAUTO=0\r\n");
  delay(2000); 
  blueToothSerial.flush();
  blueToothSerial.print("\r\n+INQ=1\r\n");
  Serial.println("inquiring");
  delay(2000); 
  
  char recvChar;
 /* while(1){                                       //this part is for auto detecting and connecting to a slave but something is wrong with the parsing of the address, use this to print out the address and then put it in manulely 								below
    if(blueToothSerial.available()){
     recvChar = blueToothSerial.read();
      recvBuf += recvChar;
      nameIndex = recvBuf.indexOf(slaveName);
  
      if ( nameIndex != -1 ){
        
 	addrIndex = (recvBuf.indexOf(retSymb,(nameIndex - retSymb.length()- 18) ) + retSymb.length());	 		
 	slaveAddr = recvBuf.substring(addrIndex, nameIndex);			
 	break;
      }
   }
 }*/
  
  connectCmd += slaveAddr;
  connectCmd += "\r\n";
  int connectOK = 0;
  Serial.print("Connecting to slave:");
  Serial.print(slaveAddr);
  Serial.println(slaveName);

  do{
    blueToothSerial.print("/*put slave address here*/");
    recvBuf = "";
    while(1){
      if(blueToothSerial.available()){
        recvChar = blueToothSerial.read();
 	recvBuf += recvChar;
 	if(recvBuf.indexOf("CONNECT:OK") != -1){
          connectOK = 1;
 	  Serial.println("Connected!");
 	  blueToothSerial.print("Connected!");
 	  break;
 	}else if(recvBuf.indexOf("CONNECT:FAIL") != -1){
 	  Serial.println("Connect again!");
 	  break;
 	}
      }
    }
  }while(0 == connectOK);
}
 

