#include <RF24.h>
#include <SPI.h>
#include <Servo.h>

Servo myservo;
RF24 radio(9,10);
const byte rxAddr[6] = "00001";
int DATA[3];

void setup() 
{
 
  radio.begin();
  radio.openReadingPipe(0,rxAddr);
  radio.startListening();

  myservo.attach(3);
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop()
{
  while(radio.available())
  {
    radio.read(DATA,sizeof(DATA));
    if(DATA[1] < 0)
    {
      digitalWrite(2,0);
      digitalWrite(7,1);
      analogWrite(6,DATA[1]*-1);
    }
    else
    {
      digitalWrite(2,1);
      digitalWrite(7,0);
      analogWrite(6,DATA[1]);
    }
    
    myservo.write(DATA[0]);
    delayMicroseconds(5);
  }
}
