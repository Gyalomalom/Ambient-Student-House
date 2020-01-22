#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); //create MFRC522 instance
Servo servo; // create servo object




void setup() {
  Serial.begin(9600);
  SPI.begin(); //initiate SPI bus
  mfrc522.PCD_Init(); //Initiate MFRC522
  Serial.println("Swipe your card.");
  Serial.println();
  servo.attach(8); //attach servo to pin
  servo.write(0);
  

}

void loop() {

  //wait for card input
  if( !mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  //select card
  if( !mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for(byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if(content.substring(1) == "04 54 2C AA 94 5E 80") //card tag
  {
    Serial.println("Access granted");
    Serial.println();
    delay(100);
    servo.write(90); //start up servo
    delay(5000);
    servo.write(0);
  }
  else
  {
    Serial.println("Access denied");
    delay(3000);
  }

}
