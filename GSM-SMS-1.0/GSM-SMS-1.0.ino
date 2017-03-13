//#include "SIM900.h"
#include <SoftwareSerial.h>
//#include <GSM.h>

//GSM_SMS sms;

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("AT");
  


}

void loop() {
  // put your main code here, to run repeatedly:

//if (mySerial.available()) {
  //  Serial.write(mySerial.read());
  //}
  //if (Serial.available()) {
  //  mySerial.write(Serial.read());
  //}

 Serial.print("Enter a mobile number: ");
  char remoteNum[20];  // telephone number to send sms
  readSerial(remoteNum);
  Serial.println(remoteNum);

 Serial.print("Now, enter SMS content: ");
  char txtMsg[200];
  readSerial(txtMsg);
  Serial.println("SENDING");
  Serial.println();
  mySerial.println("AT+CMGF=1");
  mySerial.print("AT+CMGS=\"");
  mySerial.print(remoteNum);
  mySerial.println("\"");
  mySerial.print(txtMsg);
  mySerial.write(0x1A);
  mySerial.println();
  if (mySerial.available()) {
   Serial.write(mySerial.read());
   }
   
  Serial.println("Message:");
  Serial.println(txtMsg);
}

int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
