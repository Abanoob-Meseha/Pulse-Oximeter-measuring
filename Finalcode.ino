#include <LiquidCrystal.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int bazzer =7;
int heart;
int spo;
int flag=0;
PulseOximeter pox;
int tempPin=A0;
float temp;
float reading;
uint32_t tsLastReport = 0;
int swich=1;
int swich_flag=0;

void onBeatDetected()
{
    Serial.println("Beat!");
    if(heart <60){
          digitalWrite(bazzer,1);
          delay(50);
          digitalWrite(bazzer,0);
          }
    if(heart==0){
      digitalWrite(bazzer,1);
      }
}

void setup()
{
  pinMode(bazzer,OUTPUT);
 pinMode(tempPin,INPUT);
  lcd.begin(16, 2);
  lcd.print("Hi..Lets do it");
    Serial.begin(115200);

    Serial.print("Initializing pulse oximeter..");

    
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    
    pox.setOnBeatDetectedCallback(onBeatDetected);
    
}

void loop()
{
 
  
  
  digitalWrite(bazzer,0);
  
        
    
        
    pox.update();

    
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
         lcd.clear();
      reading=analogRead(tempPin);
      temp=(reading/1024)*500;
      Serial.println(temp);
         lcd.setCursor(7, 0);
        lcd.print(" T:");
        lcd.print(temp);
        lcd.print("C");
    lcd.setCursor(1, 1);
    lcd.print("rate:");
        lcd.print(heart);
        lcd.print(" BPM");
        heart= pox.getHeartRate();
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
         lcd.setCursor(1, 0);
    lcd.print("O2:");
        lcd.print(spo);
        lcd.print("%");
        spo= pox.getSpO2();
        Serial.print(pox.getSpO2());
        Serial.println("%");
        
        tsLastReport = millis();
    }
    
       
    
        
   
   
        
        
        
    
}
