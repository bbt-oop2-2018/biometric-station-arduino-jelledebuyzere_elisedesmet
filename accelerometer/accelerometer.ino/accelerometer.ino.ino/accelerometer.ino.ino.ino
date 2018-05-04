/******************************************************************************
MMA8452Q_Basic.ino
SFE_MMA8452Q Library Basic Example Sketch
Jim Lindblom @ SparkFun Electronics
Original Creation Date: June 3, 2014
https://github.com/sparkfun/MMA8452_Accelerometer

This sketch uses the SparkFun_MMA8452Q library to initialize the
accelerometer, and stream values from it.

Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL

The MMA8452Q is a 3.3V max sensor, so you'll need to do some 
level-shifting between the Arduino and the breakout. Series
resistors on the SDA and SCL lines should do the trick.

Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Uno
	
	**Updated for Arduino 1.6.4 5/2015**

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/
#include <Wire.h> // Must include Wire library for I2C
#include <LiquidCrystal.h>
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

MMA8452Q accel;

void setup()
{
  Serial.begin(115200);
  accel.init();
  setupDisplay();
  Wire.begin(); 
}

void setupDisplay(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.setCursor(8, 0);
  lcd.print("Y:");
  lcd.setCursor(0, 1);
  lcd.print("Z:");
}

void loop()
{

  if (accel.available())
  {
    // First, use accel.read() to read the new variables:
    accel.read();

    printCalculatedAccels();
    printOrientation();
    printAccels();
   
    Serial.println(); // Print new line every time.
  }
}

void printAccels()
{
  lcd.setCursor(2, 0); 
  lcd.print(accel.cx, 3);
  lcd.setCursor(10, 0); 
  lcd.print(accel.cy, 3);
  lcd.setCursor(2, 1); 
  lcd.print(accel.cz, 3);
  delay(500);
}

void printCalculatedAccels()
{ 

  Serial.print("x = ");
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print("y = ");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print("z = ");
  Serial.print(accel.cz, 3);
  Serial.print("\t"); 
  
  delay(100);
}

void printOrientation()
{

  byte pl = accel.readPL();
  switch (pl)
  {
  case PORTRAIT_U:
    Serial.print("Portrait Up");
    break;
  case PORTRAIT_D:
    Serial.print("Portrait Down");
    break;
  case LANDSCAPE_R:
    Serial.print("Landscape Right");
    break;
  case LANDSCAPE_L:
    Serial.print("Landscape Left");
    break;
  case LOCKOUT:
    Serial.print("Flat");
    break;

   
  }
}
