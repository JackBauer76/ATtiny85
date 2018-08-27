
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,7);
long bounce_duration = 20;
volatile unsigned long bounceTime = 0;

enum displayBrightness{
  off = 0,
  low = 64,
  medium = 128,
  high = 255
};

volatile displayBrightness brightness = low;
const int brightnessTogglePin = 2;
const int brightnessPin = 9;

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(switchPin,INPUT);
  pinMode(brightnessPin,OUTPUT);
  lcd.print("Ask the");
  lcd.setCursor(0,1);
  lcd.print("Crystal ball");
  attachInterrupt(brightnessTogglePin,toggleBrightness,LOW );
  analogWrite(brightnessPin,brightness);
}

void loop(){
  Serial.println(brightness);
  switchState = digitalRead(switchPin);
  analogWrite(brightnessPin,brightness);
  if(switchState != prevSwitchState){
    if(switchState == LOW){
      reply = random(8);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The ball says:");
      lcd.setCursor(0,1);
     
      switch(reply){
        case 0:
          lcd.print("Yes");
          break;
        case 1:
          lcd.print("Most Likely");
          break;
        case 2:
          lcd.print("Certainly");
          break;
        case 3:
          lcd.print("Outlook Good");
          break;
        case 4:
          lcd.print("Unsure");
          break;
        case 5:
          lcd.print("Ask Again");
          break;
        case 6:
          lcd.print("Doubtful");
          break;
        case 7:
          lcd.print("No");
          break;
      }
    }
  }
   prevSwitchState = switchState; 
   
   
}

void toggleBrightness(){
if(millis() > bounceTime){
   
   if(brightness == off){
     brightness = low;
   }
   else if(brightness == low){
     brightness = medium;
   }
   else if(brightness == medium){
     brightness = high;
   }
   else{
     brightness = off;
   }
  bounceTime = millis() + bounce_duration; 
}
}
