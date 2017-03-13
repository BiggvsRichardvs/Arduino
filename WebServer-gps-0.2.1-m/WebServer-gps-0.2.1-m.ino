/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 */

#include <SPI.h>
#include <Ethernet.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEC, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// GPS setup

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // Start The GPS
  
//  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println(F("Starting GPS Setup"));

}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
 
              
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          client.print("Hi Mikayla, this is an itty bitty little web server that prints the output of the analong pins on an Arduino:<br>");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.print("<br>");
          }
             client.print("<br>");
                  
             client.print("And the output from the GPS module: <br>");
          
            //if (gps.encode(ss.read()))
              client.print(F("Location:  ")); 
            if (gps.location.isValid())
            {
              client.print(gps.location.lat(), 6);
              client.print(F(","));
              client.print(gps.location.lng(), 6);
            }
            else
            {
              client.print(F("INVALID"));
            }
          
            client.print(F("   Date/Time:   "));
            if (gps.date.isValid())
            {
              client.print(gps.date.month());
              client.print(F("/"));
              client.print(gps.date.day());
              client.print(F("/"));
              client.print(gps.date.year());
            }
            else
            {
              client.print(F(" CONNECTING TO SATELLITES "));
            }
          
            client.print(F(" "));
            if (gps.time.isValid())
            {
              if (gps.time.hour() < 10) client.print(F("0"));
              client.print(gps.time.hour());
              client.print(F(":"));
              if (gps.time.minute() < 10) client.print(F("0"));
              client.print(gps.time.minute());
              client.print(F(":"));
              if (gps.time.second() < 10) client.print(F("0"));
              client.print(gps.time.second());
              client.print(F("."));
              if (gps.time.centisecond() < 10) client.print(F("0"));
              client.print(gps.time.centisecond());
            }
            else
            {
              client.print(F("INVALID"));
            }



              // Print Uptime
              long day = 86400000; // 86400000 milliseconds in a day
              long hour = 3600000; // 3600000 milliseconds in an hour
              long minute = 60000; // 60000 milliseconds in a minute
              long second =  1000; // 1000 milliseconds in a second
              
              long currentmillis=millis();
              client.print("  Total milliseconds running: "); 
              client.println(currentmillis);
               int days = currentmillis / day ;                                //number of days
               int hours = (currentmillis % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
               int minutes = ((currentmillis % day) % hour) / minute ;         //and so on...
               int seconds = (((currentmillis % day) % hour) % minute) / second;
               
              client.print(days,DEC);  
              //hours = printDigits(hours)
              client.print(hours);
              client.print(":"); 
              //minutes = printDigits(minutes) 
              client.print(minutes);
              client.print(":");
              //seconds = printDigits(seconds);
              client.print(seconds);
              client.println("<br");  
              
              

              
            client.println();
                      client.println("<br />");
                    
                    
                    client.println("</html>");
                              
                     break;
        }
                while (ss.available() > 0)
                  if (gps.encode(ss.read()))
                    displayInfo();
          
                    if (millis() > 5000 && gps.charsProcessed() < 10)
                      {
                      Serial.println(F("No GPS detected: check wiring."));
                      }   
                  
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printDigits(byte digits){
 // utility function for digital clock display: prints colon and leading 0
 Serial.print(":");
 if(digits < 10)
   Serial.print('0');
 Serial.print(digits,DEC);   
}

void displayInfo()
{
  

} 
  


