/*
  Reading and writing to a serial ASCII-encoded string.


  created: 21 May 2018
  author: Paul Tonning 

  This code is in the public domain.
*/

#include <Servo.h>

// pins for the LEDs:
const int BUFFER_LENGTH = 1200;
const int BAUD_RATE = 9600;
const int MAXPINS = 15;
int interval[MAXPINS];
int A[MAXPINS];
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int servo1 = 10;
char serialbuffer[BUFFER_LENGTH];
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
unsigned long previousMillis = 0;
unsigned long previousTempMillis = 0;
float temp;
const int sweep = 250;

void setup() {
  for(int i=0;i<MAXPINS;i++){
    A[i] = i;
  }
  interval[0] = 1000;
  interval[1] = 1000;
  // initialize serial:
  Serial.begin(BAUD_RATE);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(A[0],INPUT);
  myservo.attach(servo1);
  Serial.println("Connect");

}

void loop() {
  unsigned long currentMillis = millis();
  
  if(Serial.available() > 0)
  {
      size_t s_length = Serial.readBytesUntil('\n',serialbuffer,BUFFER_LENGTH);
      if(s_length)
      {
          char* separator = strchr(serialbuffer, ':');
          if(separator != 0)
          {
            *separator = 0;
            int pin = atoi(serialbuffer);
            ++separator;
            int value =  constrain(atoi(separator), 0, 255);
           
            analogWrite(pin, value);
          }
          
          for(int i=0;i<s_length;i++)
            serialbuffer[i] = '\0';
            
      }
  }
  
  if (currentMillis - previousMillis >= interval[0]) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if(pos<=sweep) {
      myservo.write(pos);
      pos++;
    }
    else {
      pos = 0;
      myservo.write(0);
    }
  }
  if (currentMillis - previousTempMillis >= interval[1]) {
    /*
     * We can get value magic number 0.48828125 from following expression:
        (SUPPLY_VOLTAGE x 1000 / 1024) / 10 where SUPPLY_VOLTAGE is 5.0V (the voltage used to power LM35)
        1024 is 2^10, value where the analog value can be represented by ATmega (cmiiw) or the maximum value it can be represented is 1023. The actual voltage obtained by VOLTAGE_GET / 1024.
        1000 is used to change the unit from V to mV
        10 is constant. Each 10 mV is directly proportional to 1 Celsius.
        By doing simple math: (5.0 * 1000 / 1024) / 10 = 0.48828125
     */
    // save the last time you blinked the LED
    previousTempMillis = currentMillis;
    Serial.print("V:");
    Serial.print(analogRead(A[0]));
    Serial.println();
  }
  
  
}
