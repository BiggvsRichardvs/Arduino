#include <IridiumSBD.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


SoftwareSerial nss(7, 8);
IridiumSBD isbd(nss, 12);
static const int ledPin = 13;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  int signalQuality = -1;

  pinMode(ledPin, OUTPUT);

  Serial.begin(19200);
  Serial.println(F("Starting"));
  nss.begin(19200);
  ss.begin(GPSBaud);
  
  

}

bool checkGPS()

{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      Serial.println(F("Got GPS"));
      return true;
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    return false;
    Serial.println(F("No GPS"));
  }
}

bool sendtoSatellite()
{
  
 {
  int signalQuality = -1;
  nss.begin(19200);
  isbd.attachConsole(Serial);
  
  isbd.setPowerProfile(1);
  isbd.begin();
  
  int err = isbd.getSignalQuality(signalQuality);
    if (err != 0)
    {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    Serial.println(signalQuality);
    return false;
    }
  
  else
  {
// Check for location

     char latitude = int(gps.location.lat(), 7);
     char longitude = int(gps.location.lng(), 7);
     char coords[28] = {latitude, ",", longitude};

  if (gps.location.isValid())
  {
    Serial.println(coords);
    err = isbd.sendSBDText(coords);
//    err = isbd.sendSBDText((coords));
      if (err != 0) {
        Serial.println(err);
      return false;
      }
     
//    Serial.print(gps.location.lat(), 6);
//    Serial.print(F(","));
//    Serial.print(gps.location.lng(), 6);
  }
  
  else
  {
    for (int i=1; i <= 20; i++){
      digitalWrite(ledPin, (millis() / 500) % 2 == 1 ? HIGH : LOW);
      delay(10);
      } 
    return true;
   }
  }
 }

}

void loop()
{
  // digitalWrite(ledPin, HIGH);
   checkGPS();
   if (checkGPS() == true)
  {
    sendtoSatellite();
    if (sendtoSatellite() == true)
     {
    for (int i=1;i<25;i++){
          digitalWrite(ledPin, (millis() / 100) % 2 == 1 ? HIGH : LOW);
    }
    digitalWrite(ledPin, HIGH);
    while(true);
     }
  //   else 
    // {
    //  ISBDCallback();
    // }
  }
}

//bool ISBDCallback()
//{
//   digitalWrite(ledPin, (millis() / 1000) % 2 == 1 ? HIGH : LOW);
//   return true;
//}
