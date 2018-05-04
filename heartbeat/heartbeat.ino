#include <LiquidCrystal.h>
#include <Wire.h> //easy to use A4 (SDA), A5 (SCL)

LiquidCrystal lcd (8, 9, 4, 5, 6, 7);


//  Variables
int PulseSensorPurplePin = 0;      
int LED13 = 13;   
int Signal;               



// The SetUp Function:
void setup() {
   Serial.begin(115200);  

   setupDisplay();
}

void setupDisplay(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("BPM:");
  
}

void loop() {

  Signal = analogRead(PulseSensorPurplePin);  

  lcd.setCursor(5, 0); 
  lcd.print((Signal/6)-10);

delay(500);

//wanneer er geen hartslag is, krijgen we wel values.
  
}
