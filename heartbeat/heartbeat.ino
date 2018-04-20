#include <LiquidCrystal.h>
#include <Wire.h> //easy to use A4 (SDA), A5 (SCL)

LiquidCrystal lcd (8, 9, 4, 5, 6, 7);


//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024



// The SetUp Function:
void setup() {
   Serial.begin(115200);         // Set's up Serial Communication at certain speed. 
   
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.
  Serial.print("Heartbeat: ");
  Serial.println((Signal/6)+4);                    // Send the Signal value to Serial Plotter.

delay(500);

//wanneer er geen hartslag is, krijgen we wel values.
  
}
