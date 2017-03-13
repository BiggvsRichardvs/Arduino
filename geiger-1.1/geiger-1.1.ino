#include <SPI.h>
#define LOG_PERIOD 1000 //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 1000 //Maximum logging period
unsigned long counts; //variable for GM Tube events
unsigned long cpm; //variable for CPM
unsigned int multiplier; //variable for calculation CPM in this sketch
unsigned long previousMillis; //variable for time measurement

#define LM_SIZE 60
  static int LM[LM_SIZE];      // LastMeasurements
  static byte index = 0;
  static long sum = 0;
  static byte count = 0;


void tube_impulse(){
//procedure for capturing events from Geiger Kit
counts++;
}

void setup(){
//setup procedure
counts = 0;
cpm = 0;
multiplier = MAX_PERIOD / LOG_PERIOD;
//calculating multiplier, depend on your log period
Serial.begin(9600); // start serial monitor
pinMode(2, INPUT); // set pin INT0 input for capturing GM Tube events
digitalWrite(2, HIGH); // turn on internal pullup resistors, solder C-INT on the PCB
attachInterrupt(0, tube_impulse, FALLING); //define external interrupts
}



void loop(){
//main cycle



  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD){
  previousMillis = currentMillis;
  Serial.print(counts);
  Serial.println(" this cycle "); 

//cpm = vounts * multiplier;
 

  // keep sum updated to improve speed.
  sum -= LM[index];
  LM[index] = counts;
//  Serial.println(LM[index]);
//  Serial.println(counts);
  sum += LM[index];
  index++;
  index = index % LM_SIZE;
  if (count < LM_SIZE) count++;

  Serial.print(sum); // send cpm data to Radiation Logger
  Serial.println(" Counts per minute(ish)");
  Serial.println();
  Serial.write(' ');
  counts = 0;
}
}

