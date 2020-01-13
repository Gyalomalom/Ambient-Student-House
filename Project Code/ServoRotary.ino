#include <Servo.h>

//rotary encoder inputs
#define inputCLK 4
#define inputDT 5

//servo object
Servo servoCurtain;

int counter = 0;
int currentStateCLK;
int previousStateCLK;

void setup() 
{
  pinMode(inputCLK,INPUT);
  pinMode(inputDT,INPUT);

  Serial.begin(9600);
  
  servoCurtain.attach(9);

  previousStateCLK = digitalRead(inputCLK);
  
}

void loop() 
{
  currentStateCLK = digitalRead(inputCLK);

  if (currentStateCLK != previousStateCLK)
  {
    //the rotary encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK)
    {
      counter = counter - 5;
      if (counter < 0)
      {
        counter = 0;
      }
    }
    //the rotary encoder is rotating clockwise
    else
    {
      counter = counter + 5;
      if (counter > 90)
      {
        counter = 90;
      }
    }
    //move the servo to the value of the counter
    servoCurtain.write(counter);
    Serial.print("Position: ");
    Serial.println(counter);
  }
  previousStateCLK = currentStateCLK;
}
