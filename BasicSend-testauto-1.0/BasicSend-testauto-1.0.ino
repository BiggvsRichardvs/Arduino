#include <IridiumSBD.h>
#include <SoftwareSerial.h>

SoftwareSerial nss(7, 8);
IridiumSBD isbd(nss, 12);
static const int ledPin = 13;

void setup()
{
  int signalQuality = -1;

  pinMode(ledPin, OUTPUT);

  Serial.begin(19200);
  nss.begin(19200);




  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);

}

bool sendmessage()

{

  int signalQuality = -1;

  //  isbd.attachConsole(Serial);
  isbd.setPowerProfile(1);
  isbd.begin();
  int err = isbd.getSignalQuality(signalQuality);
  
  err = isbd.sendSBDText("But sir it is wafer thin.");
  if (err != 0)
  {

    for (int i=0; i <= 10; i++){
      digitalWrite(ledPin, (millis() / 500) % 2 == 1 ? HIGH : LOW);
      delay(10);
   } 
    
    
    return;
  }

}

void loop()
{
   bool result;
   digitalWrite(ledPin, HIGH);
   sendmessage();
   if (sendmessage != 0)
  {
    digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
    while(true);
  }
  
}

//bool ISBDCallback()
//{
//   digitalWrite(ledPin, (millis() / 1000) % 2 == 1 ? HIGH : LOW);
//   return true;
//}
