#include <SparkFun_MMA8452Q.h>
#include <LiquidCrystal.h>
#include <Wire.h>

//heartbeatVar
int PulseSensorPurplePin = 0;       

//accelerometerVar
MMA8452Q accel;


//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin


// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

byte heart[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000 
};



void setup() {
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);  
  
  Serial.begin(115200);
  //Serial.println("Hello world!"); test
  Wire.begin();  //temp
  accel.init(); //acc
  interruptSetup();   
  setupDisplay();
}

void setupDisplay(){
  lcd.begin(16,2);

  lcd.setCursor(1, 0);
  lcd.write("Welcome to our");
  //delay(2000);
  lcd.setCursor(0, 1);
  lcd.write("BiometricStation");
  delay(2500);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.write("Enjoy!");
  delay(3000);
  lcd.clear();  

  
  lcd.createChar(0, heart);
  lcd.begin(16, 2);  
  lcd.write(byte(0));

  lcd.setCursor(1,0);
  lcd.print(":"); 

  lcd.setCursor(5,0);
  lcd.print("BPM");
  
  lcd.setCursor(14,0);
  lcd.print("\337C");

  lcd.setCursor(0,1);
  lcd.print("x");
  lcd.setCursor(6,1);
  lcd.print("y");
  lcd.setCursor(11,1);
  lcd.print("z");
}

void loop() {
  double temperatureData = temperature();
  int heartbeatData = heartbeat();
  float accelerometerDataX = accelerometerX();
  float accelerometerDataY = accelerometerY();
  float accelerometerDataZ = accelerometerZ();
  ledFadeToBeat();

  Serial.println(temperatureData + String(";") 
                  + heartbeatData + String(";") 
                  + accelerometerDataX + String(";") 
                  + accelerometerDataY + String(";") 
                  + accelerometerDataZ);

dataLcdDisplay(temperatureData, heartbeatData, accelerometerDataX, accelerometerDataY, accelerometerDataZ);
  
  delay(1000);
}

void dataLcdDisplay(double temperatureData, int heartbeatData, float accelerometerDataX, float accelerometerDataY, float accelerometerDataZ){
  lcd.setCursor(9,0);
  lcd.print(temperatureData);

  lcd.setCursor(2,0);
  lcd.print(heartbeatData);

  lcd.setCursor(1,1); 
  lcd.print(accelerometerDataX);
  
  lcd.setCursor(7,1);
  lcd.print(accelerometerDataY);
  
  lcd.setCursor(12,1);
  lcd.print(accelerometerDataZ);
  
}

/* Accelerometer Section */
double accelerometerX(void) {
  accel.read();
  return accel.cx;
}

double accelerometerY(void) {
  accel.read();
  return accel.cy;
}

double accelerometerZ(void) {
  accel.read();
  return accel.cz;
}
/* ---- */

/* Heartbeat Section */
void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }

int heartbeat(void) {
  int heartbeat;
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
        fadeRate = 255;                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
        heartbeat =BPM;                  // send heart rate with a 'B' prefix
        QS = false;                      // reset the Quantified Self flag for next time    
     }
  return heartbeat; 
}

/* ---- */

/* Temperature Section */
 double temperature(void) {
    uint8_t temp[2]; // values of pins will come in this array
    //signed integer of exactly 16 bits
    int16_t tempS;
    byte address = 0x48; //address of slave device (sensor)
    byte val = 0x00;
    int quantity = 2; //number of bytes to request
    int MAGIC_NUMBER = 4;
    double convertValueForCelsius = 0.0625;
  
    Wire.beginTransmission(address); //hexidecimal address, begins transmission I2C slave device with given address (see datasheet)
    Wire.write(val); //Wire.write(value) -> a value to send as a single byte
    Wire.endTransmission(); //end transmission
    //delay(150);
  
    Wire.requestFrom(address, quantity);
  
    if (quantity <= Wire.available()) { //.available() = number of bytes available for reading.
      //reading out data
      temp[0] = Wire.read();
      temp[1] = Wire.read();
  
      //dumb the lower 4 bits of byte 2a
      temp[1] = temp[1] >> MAGIC_NUMBER;
      //combine to make 12 bit binary number
      tempS = ((temp[0] << MAGIC_NUMBER) | temp[1]);
  
      //convert to celsius
      return tempS * convertValueForCelsius;
    }
    return 0.0;
} // in case of not triggering the 'if'
/* ---- */












