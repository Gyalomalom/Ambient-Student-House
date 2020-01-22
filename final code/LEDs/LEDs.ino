int red_light_pin_liv= 11;
int green_light_pin_liv = 10;
int blue_light_pin_liv = 9;

String state = "D";
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
//int calibrationTime = 1;       
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 5000; 
 
boolean lockLow = true;
boolean takeLowTime; 
 
int pirPin = 3;    //the digital pin connected to the PIR sensor's output 

//timings
unsigned long previousMillis = 0;
unsigned long awakeInterval = 10000;
void setup() {
  Serial.begin(9600);
 pinMode(red_light_pin_liv, OUTPUT);
  pinMode(green_light_pin_liv, OUTPUT);
  pinMode(blue_light_pin_liv, OUTPUT);
  pinMode(pirPin, INPUT);
//  Serial.print("calibrating sensor ");
//    for(int i = 0; i < calibrationTime; i++){
//      Serial.print(".");
//      delay(1000);
//      }
//    Serial.println(" done");
//    Serial.println("SENSOR ACTIVE");
//    delay(50);
//  Serial.println("Start");
}

void RGB_color_liv(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin_liv, red_light_value);
  analogWrite(green_light_pin_liv, green_light_value);
  analogWrite(blue_light_pin_liv, blue_light_value);
}
//void RGB_color_bed(int red_light_value, int green_light_value, int blue_light_value)
// {
//  analogWrite(red_pin_bed, red_light_value);
//  analogWrite(green_pin_bed, green_light_value);
//  analogWrite(blue_pin_bed, blue_light_value);
//}
void loop() {
  unsigned long currentMillis = millis();
  int val = Serial.read() - 48;
  if(val == 1){
    RGB_color_liv(255, 0, 0);    
    }
    else if( val == 2){
      RGB_color_liv(0, 255, 0);
      }
      else if( val == 3){
      RGB_color_liv(0, 0, 255);
      }
      else if( val == 4){
      RGB_color_liv(0, 100, 255);
      }
      else if(val == 0)
      {
        RGB_color_liv(0, 0, 0);
        }
      else if( val == 5){
      
      
  if(digitalRead(pirPin) == HIGH){
        
        RGB_color_liv(255, 255, 255);
        
     
          //the led visualizes the sensors output pin state
       if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;           
//         Serial.println("---");
//         Serial.print("motion detected at ");
//         Serial.print(millis()/1000);
//         Serial.println(" sec");
         
         }        
         takeLowTime = true;
       }
 
     if(digitalRead(pirPin) == LOW){  
       
        RGB_color_liv(0, 0, 0);
         
       //the led visualizes the sensors output pin state
 
       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){ 
           //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;                       
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           
           }
       }

      }
//    if(val == 6){
//    RGB_color_bed(255, 0, 0);    
//    }
//    else if( val == 7){
//      RGB_color_bed(0, 255, 0);
//      }
//      else if( val == 8){
//      RGB_color_bed(0, 0, 255);
//      }
//      else if( val == 9){
//      RGB_color_bed(0, 100, 255);
//      }
//      else if(val == 11)
//      {
//        RGB_color_bed(0, 0, 0);
//        }
  

    
  
}
