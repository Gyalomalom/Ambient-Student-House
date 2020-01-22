/*Studentname: Mitchell van 't Kruys
  StudentNumber: 4058151
  Project: Advanced Project
  Date: 1/17/2020

  Description:  This application is for the kitchen subsystem. The smoke detector detects
                if the area around it surpases the threshold of smoke or gas. if it does surpass
                the threshold, the system will send a signal to the buzzer to activate it for a
                period of time. the system will also send this message to the administrator system.
*/

// including libraries needed for this code to run:
#include <MQ2.h>

//color sensor
#define S1 2
#define S0 3
#define S3 4
#define S2 5
#define sensorOut 6

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

//pins
int smokePin = A0;  // pin for the smoke detector.
int buzzerPin = 8;  // pin for the active buzzer actuator.
int buttonPin = 9;
int ledPinR = 10;

float smoke;        // float variable for the smoke calculation .
MQ2 mq2(smokePin);  // Attaching the library to local variable mq2.
int smokeThreshold = 1000;     // threshold to reach before sounding the alarm.

//alarm and led
int ledState = LOW;
long previousMillisAlarm = 0;
long intervalAlarm = 1000;

//Variables in order to save the state of the buttons
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the mode button

//delays for debouncing
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounce = 50;       // the debounce time; increase if the output


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // beginning/setting pinmode for the sensors and actuators.
  mq2.begin();

  //
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPinR, OUTPUT);

  digitalWrite(ledPinR, HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:

  int resetButton = digitalRead(buttonPin);
  unsigned long currentMillisAlarm = millis();
  int x = 0;

  if (resetButton != lastButtonState)
  {
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounce)
  {
    // if the button state has changed:
    if (resetButton != buttonState)
    {
      buttonState = resetButton;

      if (buttonState == HIGH)
      {
        
        for (int x = 0; x < 5; x++) {
          digitalWrite(ledPinR, LOW);
          noTone(buzzerPin);
          delay(1000);
        }
      }
    }
  }
  if (resetButton == LOW) {
    float* values = mq2.read(false); //set it false if you don't want to print the values in the Serial
    smoke = mq2.readSmoke();       // reading Smoke values.
    if (smoke > smokeThreshold) {

      if (int i = 0 < 100) {
        tone(buzzerPin, 311, 500); // set buzzer tone to 500.
        digitalWrite(ledPinR, HIGH);
       
        i++;
      }
      
    }
  }
  lastButtonState = resetButton;

  Color();
}

void Color() {

  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);

  //remapping
  redFrequency = map(redFrequency, 25 , 80, 255, 0);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);

  //remapping
  greenFrequency = map(greenFrequency, 25, 60 , 255, 0);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);

  //remapping
  blueFrequency = map( blueFrequency, 20, 95, 255, 0);
  delay(100);

  //sensor
  if (redFrequency > 250 && greenFrequency > 175 && greenFrequency < 200 && blueFrequency > 140) {
    Serial.println("banana");
  } else if (redFrequency > 200 && greenFrequency < 0 && blueFrequency < 75) {
    Serial.println("orange");
  } else if (redFrequency > 190 && greenFrequency < 0 && blueFrequency < 170 && blueFrequency > 130) {
    Serial.println("meat");
  } else if (redFrequency > 100 && greenFrequency < 150 && greenFrequency > 50 && blueFrequency > 110) {
    Serial.println("vegetable");
  }else if(redFrequency < 10 && greenFrequency < 50 && blueFrequency < 170){
      Serial.println("water");
      }
}
