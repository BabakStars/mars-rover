#include <RF24.h>
#include <SPI.h>

RF24 radio(9,10);
const byte rxAddr[6] = "00001";
int DATA[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(rxAddr);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Y:");
  Serial.println(analogRead(A0));
  Serial.print("X:"); 
  Serial.println(analogRead(A1));
  Serial.println("----------------");
  

  int y = map(analogRead(A0), 507, 1023, 0, 255);
  int x = map(analogRead(A1), 0, 1023, 0, 180);
  Serial.println(y);
  Serial.println(x);
  
  DATA[0] = x;
  DATA[1] = y;
  DATA[2] = 0;
  
  radio.write(DATA,sizeof(DATA));
  delay(50);
}
