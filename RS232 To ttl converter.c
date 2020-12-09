#include <SoftwareSerial.h>

#define MAX_LEN 128

#define rxPin 10
#define txPin 11
SoftwareSerial mySerial(rxPin, txPin); 

void setup() 
{
  // hardware serial
  Serial.begin(9600);
  while (!Serial) ;
  
  Serial.println("Hardware Serial: 9600 8N1 (USB)");
  Serial.println("-- Serial Monitor");
  
  // software serial
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  Serial.println("Hardware Serial: 9600 8N1 (RS232)");
  Serial.println("-- Hummingbird Driver Behaviour Monitor");
  Serial.println();
}

void loop() 
{
  uint8_t c;

  // SEND: 
  if (Serial.available())
  {
    char  str[MAX_LEN] = { 0 };
    int   i, len = 0;
    
    Serial.print("send (HEX): ");
    while (Serial.available())
    {
      c = Serial.read();      
      if (c < 0x10) Serial.print("0");
      Serial.print(c, HEX);
      mySerial.write(c);      
      str[len] = c; len++;
      Serial.print(" ");
    }
    
    c = '\r';
    if (c < 0x10) Serial.print("0");
    Serial.print(c, HEX);
    mySerial.write(c);
    Serial.print(" ");

    c = '\n';
    if (c < 0x10) Serial.print("0");
    Serial.print(c, HEX);
    mySerial.write(c);

    Serial.println();
    Serial.print("send (ASC): ");
    for (int i=0; i<len; i++)
    {
      if ((str[i] >= 0x20) && (str[i] < 0x7f)) 
        Serial.write(str[i]); else Serial.write(".");
    }
    Serial.println();
    Serial.println();
  }

  // RECV
  if (mySerial.available())
  {
    char  str[MAX_LEN] = { 0 };
    int   i, len = 0;

    Serial.print("recv (HEX): ");
    while (mySerial.available())
    {
      c = mySerial.read();
  
      if (c < 0x10) Serial.print("0");
      Serial.print(c, HEX);
      str[len] = c; len++;
      Serial.print(" ");
    }

    Serial.println();
    Serial.print("recv (ASC): ");
    for (int i=0; i<len; i++)
    {
      if ((str[i] >= 0x20) && (str[i] < 0x7f)) 
        Serial.write(str[i]); else Serial.write(".");
    }
    Serial.println();
    Serial.println("---");
  }
}
