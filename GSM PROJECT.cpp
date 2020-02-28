#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);
char msg;
const int pulse =7;
float watt=0.0, price=0,unit=0;
int pinState=0;
unsigned int i=0; 
unsigned int j=0;
unsigned long interval =120;
unsigned long previousMillis=0;

void setup() {
  // put your setup code here, to run once:
mySerial.begin(9600);
Serial.begin(9600);
Serial.println("GSM SIM800A BEGIN");
Serial.println("s : to send message");
Serial.println("r : to receive message");
delay(100);
}
void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
pinState = digitalRead(pulse);
if(pinState==HIGH)
{
  i++;
  delay(100);
}
if(currentMillis-previousMillis >= interval)
{
  j=1;
  previousMillis = currentMillis;
}

if(j==1)
{
  watt = (i*0.3125);
  unit = watt/100;
  price = unit*5;
  Serial.begin(9600);
  Serial.print("\r");
  
  delay(800);
  Serial.println("AT+CMGF=1/r");
  delay(800);
   Serial.println("AT+CMGF=\"918072078360\"\r");
   delay(800);
    Serial.println("unit");
    delay(800);
     Serial.println(unit,6);
     delay(800);
      Serial.println("Price");
      delay(100);
       Serial.print(price,6);
       delay(100);
        Serial.print("Rs");
        delay(10);
        Serial.write(0x1A);
        delay(100);
   j=0;
}

if(Serial.available()>0)
switch(Serial.read())
{
  case 's':
  SendMessage();
  break;
   case 'r':
  ReceiveMessage();
  break; 
}
if(mySerial.available()>0)
Serial.write(mySerial.read());
}
void SendMessage()
{
  Serial.println("AT+CMGF=1");
  delay(1000);
   Serial.println("AT+CMGF=\"918072078360\"\r");
   delay(1000);
   Serial.println("sim800a sms");
   delay(100);
   Serial.println((char)26);
   delay(1000);
}
void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  if(mySerial.available()>0)
  {
    msg=mySerial.read();
    Serial.print(msg);
  }
}
