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

  isbd.attachConsole(Serial);
  isbd.setPowerProfile(1);
  isbd.begin();

  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
   Serial.print("SignalQuality failed: error ");
   Serial.println(err);
    return;
  }

    Serial.print("Signal quality is ");
    Serial.println(signalQuality);

  //err = isbd.sendSBDText("But sir it is wafer thin - test1");
  if (err != 0)
  {
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    return;
  }


  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
  digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);

}

void loop()
{
   digitalWrite(ledPin, HIGH);
}

bool ISBDCallback()
{
   digitalWrite(ledPin, (millis() / 1000) % 2 == 1 ? HIGH : LOW);
   return true;
}
