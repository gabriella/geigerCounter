//
//  Geiger Counter Firmware
//  
//  by gabriella levine
//  Based on the work of Aaron Weiss
//


//Yup. You just set your arduino's input pin to read a pin state change and count that. In parallel, have a timer running and after 6
//seconds, display the count variable.



#include <Metro.h> //Include Metro library

#include <TimerOne.h>

int CPM = 0;
long Baud      = 9600;
int  LEDPin    = 5;      // Status LED blinks for each count
long CountTime = 1000000; // 1 second, in microseconds
long interval = 10000;//1 minute long change this from 1 second
long prevTime = 0;
unsigned long currentTime;
Metro CPMMetro = Metro(60000);

int countState = 0;
int prevCountState = 0;
int counter = 0;

volatile long counts = 0;

void incrementCount(void) {
  counts++;
  digitalWrite(LEDPin, HIGH);
}

void printCount(void) {
  noInterrupts();
 //Serial.println();
//  Serial.print("millis:");
//  Serial.print(millis());
//  Serial.print(";");
//  Serial.print("counts:");
//  Serial.print(counts);
 
//if(counts != prevCountState){
// Serial.println();
// Serial.println("different");
 if(counts != 0){
   counter++;
   //Serial.println();
  Serial.print("millis:");
  Serial.print(millis());
  Serial.print("; counts:");
  Serial.print(counts);
  Serial.print("; counter number = ");
  Serial.print(counter);
 Serial.println();
 } 

//Serial.println();
prevCountState = counts;

  
  
  counts = 0;
  
  
  
  
  
  
  interrupts();
}

void setup() {
  Serial.begin(Baud);
  noInterrupts();
  attachInterrupt(INT0, incrementCount, FALLING);
  Timer1.initialize(CountTime);
  Timer1.attachInterrupt(printCount);

  pinMode(LEDPin, OUTPUT);
  interrupts();
  delay(6000);


}

void loop() {



  digitalWrite(LEDPin, LOW);
  if(CPMMetro.check()==1){
    Serial.println();
    Serial.print("total counts = ");
    Serial.println(counter);
    //Serial.println("Startover");
    counter = 0;
    
   // Serial.print("millis");
    //Serial.println(millis());
    Serial.print("minute: ");
    
    unsigned long minutes = millis()/60000;
    Serial.println(minutes);
  }

  delay(30);
}


