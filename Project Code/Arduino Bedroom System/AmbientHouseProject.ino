///DHT11
#include "dht.h"
#define dht_pin 11
dht DHT;

//ROTARY
#define inputCLK 4
#define inputDT 5

int counter = 0;
int currentStateCLK;
int previousStateCLK;

  //ROTARY BUTTON
  const int ROTPIN = 8;
  int modeState = 1;
  int swReadNew = 0;
  int swReadOld = 1;

//FAN
const int FAN = 10;
int fan_speed;

bool automatic = false;

//DELAY AND DEBOUNCE
int tempDelayPeriod = 2000;
unsigned long time_now = 0;
const unsigned long debounce = 100;
unsigned long previousTime = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(FAN, OUTPUT);
  pinMode(inputCLK, INPUT_PULLUP);
  pinMode(inputDT, INPUT_PULLUP);
  pinMode(ROTPIN, INPUT_PULLUP);
  
  previousStateCLK = digitalRead(inputCLK);
  
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(500);//Wait before accessing Sensor
}

void loop()
{
//ROTARY BUTTON
    unsigned long currentTime = millis();
    swReadNew = digitalRead(ROTPIN);
    if (swReadOld == 0 && swReadNew == 1)
    {
      if (modeState == 0)
      {
        Serial.println("Mode 3");
        modeState = 3;
      }
      else
      {
        Serial.println("Mode 1");
        modeState = 0;
      }
    }
    swReadOld = swReadNew;
    if (currentTime - previousTime >= debounce)
    {
      delay(1);
    }

    //ROTARY TURNING
    if (modeState == 0)
    {
      currentStateCLK = digitalRead(inputCLK);

      if (currentStateCLK != previousStateCLK)
      {
        if (digitalRead(inputDT) != currentStateCLK)
        {
          counter = counter - 5;
          if (counter < 0)
          {
            counter = 0;
          }
        }
        else
        {
          counter = counter + 5;
          if (counter > 100)
          {
            counter = 100;
          }
        }
        fan_speed = (counter * 255) / 100;
        analogWrite(FAN, fan_speed);
        Serial.print("Fan Speed: ");
        Serial.println(counter);
      }
      previousStateCLK = currentStateCLK;
    }

//PROTOCOL
  if (Serial.available() > 0)
  {
    String a = Serial.readStringUntil(';');
    int b = Serial.parseInt();

    Serial.print("I received: ");
    Serial.println(a);

    //SERIAL FAN CONTROL
    if (a == "B")
    {
      Serial.println("mode 2");
      fan_speed = (b * 255) / 100;
      analogWrite(FAN, fan_speed);
    }
    
    //AUTOMATIC FAN CONTROL
    else if (a == "C")
    {
      automatic = true;
    }
    if (automatic == true)
    {
      if (millis() >= time_now + tempDelayPeriod)
      {
        DHT.read11(dht_pin);

        Serial.print("Current humidity = ");
        Serial.print(DHT.humidity);
        Serial.print("%  ");
        Serial.print("temperature = ");
        Serial.print(DHT.temperature);
        Serial.println("C  ");

        time_now += tempDelayPeriod;
      }

      if (DHT.temperature < 21.00)
      {
        analogWrite(FAN, 0);
        Serial.println("auto fan speed; 0%");
      }

      if (DHT.temperature >= 22.00)
      {
        analogWrite(FAN, 127);
        Serial.println("auto fan speed: 50%");
      }

      if (DHT.temperature >= 25.00)
      {
        analogWrite(FAN, 191);
        Serial.println("auto fan speed: 75%");
      }

      if (DHT.temperature >= 27.00)
      {
        analogWrite(FAN, 255);
        Serial.println("auto fan speed: 100%");
      }


      if (a == "B")
      {
        automatic = false;
      }
    }
  }
}
