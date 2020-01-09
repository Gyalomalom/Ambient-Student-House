#include <stdlib.h>
const int FAN = 9;

int fan_speed;

String readString;

void setup()
{
  Serial.begin(9600);
  pinMode(FAN, OUTPUT);
}

void loop()
{
  //SERIAL
  while (Serial.available())
  {
    char c = Serial.read();
    readString += c;
    delay(2);
  }

  if (readString.length()>0)
  {
    Serial.println(readString);
    int n = readString.toInt();

    if ((n>100) && (n<0))
    {
      Serial.println("please select a number in between 0 - 100");
    }
    else
    {
      fan_speed = (n*255) / 100;
      analogWrite(FAN, fan_speed);
    }

    readString="";
  }
}
