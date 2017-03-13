#include <IridiumSBD.h>
#include <SoftwareSerial.h>

SoftwareSerial nss(18, 19);
IridiumSBD isbd(nss, 10);
static const int ledPin = 13;


void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

}

bool ltest()
{
  return false;
  
}
 

void loop()
{
   //digitalWrite(ledPin, LOW);

   digitalWrite(ledPin, (millis() / 2000) % 2 == 1 ? HIGH : LOW);
   if (ltest() == true)
   {
    for (int i=1;i<20;i++){
      digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
      return;
      }

    return;
   }

}

//bool ISBDCallback()
//{
  // digitalWrite(ledPin, (millis() / 1000) % 2 == 1 ? HIGH : LOW);
  // return true;
//}
