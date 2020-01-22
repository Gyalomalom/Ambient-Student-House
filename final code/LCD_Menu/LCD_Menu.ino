#include <LiquidCrystal.h> // library for the LCD Screen 
int Contrast = 150; // setting a contrast fot the LCD Screen
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // digital pins connected to the LCD


// pins fro the rotary encoder
int inputCLK = 8;
int inputDT = 9;
const int SW_pin = 7; // digital pin connected to switch output


unsigned long previousMillis = 0;

// variable used for using the SW pin
bool confirm = false;

//variables used to modify the fan
bool value = false;
int value_per = 0;

// variable used to read the SW pin from the roatary encoder
int s;

// variable used to browse throught the menu
int state = 0;


//variable used to control the fan 
int fan_state = 0; // auto
// fan_state = 1 // manual

// variables used to help reading the rotary encoder output
int previous_state = state;
int currentStateCLK;
int previousStateCLK;

void setup()
{
  Serial.begin(9600);
  analogWrite(6, Contrast); //LCD
  lcd.begin(16, 2); //LCD

  // rotary switch pin
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  // roatary encoder
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);


  previousStateCLK = digitalRead(inputCLK);
}


void loop()
{
  unsigned long currentMillis = millis();  // assigning the millis value

  s = digitalRead(SW_pin); // reading the SW pin output

  // rotary encoder reading
  currentStateCLK = digitalRead(inputCLK);
  if (currentStateCLK != previousStateCLK) 
  {
    if (digitalRead(inputDT) != currentStateCLK) 
    {
      if (value == true) 
      {
        value_per = value_per + 5;
        if(value_per > 100)
        {
          value_per = 100;
        }
      }
      else 
      {
        state ++;
        
        
      }
      lcd.clear();
      
    }
    else 
    {
      if (value == true) 
      {
        value_per = value_per - 5;
        if(value_per < 0)
        {
          value_per = 0;
        }
        
      }
      else 
      {
        state--;
        
      }
      lcd.clear();
      if (state < 0) 
      {
        state = 0;
      }
      
    }
  }
  
  if (state != previous_state) 
  {

    previous_state = state;
  }
  previousStateCLK = currentStateCLK;

// this algorithm is used to execute a certain command only when the SW pin goes back to the HIGH state
//      if (s == 0) 
//      {
//        confirm = true;
//      }
//      if (s == 1 && confirm == true) 
//      {
//        execute_code();
//        lcd.clear();
//        confirm = false;
//      }

  // states for the LCD menu
  switch (state) 
  {

    case 0:
      lcd.setCursor(0, 0);
      lcd.print("Hello :)");
      lcd.setCursor(0, 1);
      lcd.print("Scroll down");

      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("-Mood lighting");
      lcd.setCursor(0, 1);
      lcd.print("Fan");
      if (s == 0)
      {
        confirm = true;
      }
      if (s == 1 && confirm == true)
      {
        state *= 10;   
        lcd.clear();
        confirm = false;
      }

      break;

    

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Mood lighting");
      lcd.setCursor(0, 1);
      lcd.print("-Fan");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        state *= 10;   
        lcd.clear();
        confirm = false;
      }
      break;

    case 6:
      state = 2;
      break;

    case 18:
      state = 22;
      break;

    case 20:
      lcd.setCursor(0, 0);
      lcd.print("-Change preset");
      lcd.setCursor(0, 1);
      lcd.print("Back");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        state *= 10; 
        lcd.clear();
        confirm = false;
      }
      break;

    case 198:
      state = 210;
      break;
    case 200:
      lcd.setCursor(0, 0);
      lcd.print("-Study");
      lcd.setCursor(0, 1);
      lcd.print("TV");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        Serial.println("11");  
        confirm = false;
      }
      break;

    case 202:
      lcd.setCursor(0, 0);
      lcd.print("-TV");
      lcd.setCursor(0, 1);
      lcd.print("Dinner");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        Serial.println("21");  
        confirm = false;
      }
      break;

    case 204:
      lcd.setCursor(0, 0);
      lcd.print("-Dinner");
      lcd.setCursor(0, 1);
      lcd.print("Relaxation");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        Serial.println("31");  
        confirm = false;
      }
      break;

    case 206:
      lcd.setCursor(0, 0);
      lcd.print("-Relaxation");
      lcd.setCursor(0, 1);
      lcd.print("Auto");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        Serial.println("41");  
        confirm = false;
      }
      break;

    case 208:
      lcd.setCursor(0, 0);
      lcd.print("-Auto");
      lcd.setCursor(0, 1);
      lcd.print("Close");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        Serial.println("51");   
        confirm = false;
      }
      break;

    case 210:
      lcd.setCursor(0, 0);
      lcd.print("-Close");
      lcd.setCursor(0, 1);
      lcd.print("Back");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        Serial.println("1");    
        confirm = false;
      }
      break;

    case 212:
      lcd.setCursor(0, 0);
      lcd.print("-Back");
      lcd.setCursor(0, 1);
      lcd.print("Study");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        state = 20;   
        lcd.clear();
        confirm = false;
      }
      break;

   case 214:
      state = 200;
      break;   

    case 22:
      lcd.setCursor(0, 0);
      lcd.print("Change Preset");
      lcd.setCursor(0, 1);
      lcd.print("-Back");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        state = 2;   
        confirm = false;
      }
      break;

    case 24:
      state = 20;
      break;

    case 39:
      state = 42;
      break;

    case 40:
      lcd.setCursor(0, 0);
      lcd.print("-Switch mode");
      lcd.setCursor(0, 1);
      lcd.print("Back");
      if (s == 0) 
      {
        confirm = true;
      }
      if (s == 1 && confirm == true) 
      {
        if(fan_state == 0)
        {
          state = 4000;  
        }
        else if(fan_state == 1)
        {
          state = 4100;
        }
        
        lcd.clear();
        confirm = false;
      }
      break;

      case 42:
        lcd.setCursor(0, 0);
        lcd.print("Switch mode");
        lcd.setCursor(0, 1);
        lcd.print("-Back");
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          state = 4;
          lcd.clear();
          confirm = false;
        }
      break;

    case 44:
      state = 40;
      break;

      case 3998:
        state = 4004;
        break;

      case 4000:
        lcd.setCursor(0, 0);
        lcd.print("-Current : Auto");
        lcd.setCursor(0, 1);
        lcd.print("Switch to manual");
        break;
        
      case 4002:
        lcd.setCursor(0, 0);
        lcd.print("-Switch to manual");
        lcd.setCursor(0, 1);
        lcd.print("Back");
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          fan_state = 1;
          state = 400;
          value = true; 
          lcd.clear();
          confirm = false;
        }
        break;
        
      case 4004:
        lcd.setCursor(0, 0);
        lcd.print("-Back");
        lcd.setCursor(0, 1);
        lcd.print("Current: Auto");
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          state = 40;
          lcd.clear();
          confirm = false;
        }
        break;
        
      case 4006:
        state = 4000;
        break;
      case 4098:
        state = 4006;
        break;

      case 4100:
        lcd.setCursor(0, 0);
        lcd.print("-Current : Manual");
        lcd.setCursor(0, 1);
        lcd.print("Switch to Auto");
        break;
        
      case 4102:
        lcd.setCursor(0, 0);
        lcd.print("-Switch to auto");
        lcd.setCursor(0, 1);
        lcd.print("Select Fan speed");
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          fan_state = 0;
          Serial.println(2002);
          state = 4000;
          lcd.clear();
          confirm = false;
        }
        break;
        
      case 4104:
        lcd.setCursor(0, 0);
        lcd.print("-Select Fan speed");
        lcd.setCursor(0, 1);
        lcd.print("Back");
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          state = 400;
          value = true;
          lcd.clear();
          confirm = false;
        }
        break;
        
      case 4106:
        lcd.setCursor(0, 0);
        lcd.print("-Back");
        lcd.setCursor(0, 1);
        lcd.print("Current: Manual");
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          state = 40;
          
          lcd.clear();
          confirm = false;
        }
        break;

      case 4108:
        state = 4100;
        break;

      case 400:
        lcd.setCursor(0, 0);
        lcd.print("Select power in %");
        lcd.setCursor(0, 1);
        lcd.print(value_per);
        if (s == 0) 
        {
          confirm = true;
        }
        if (s == 1 && confirm == true) 
        {
          state = 4100;
          
          value_per = value_per * 10 + 2;
          Serial.println(value_per);
          Serial.print("\n");
          value_per = (value_per - 2) / 10;
          value = false;
          lcd.clear();
          confirm = false;
        }
        break;      
  }
 




}
