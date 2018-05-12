#include <SparkFun_MMA8452Q.h>
#include <LiquidCrystal.h>
#include <Wire.h>


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

//heartbeatVar
int PulseSensorPurplePin = 0;       
int Signal; 

//accelerometerVar
MMA8452Q accel;


void setup() {
  
  Serial.begin(115200);
  //Serial.println("Hello world!"); test
  Wire.begin(); 
  accel.init();
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

  Serial.println(temperatureData + String(";") 
                  + heartbeatData + String(";") 
                  + accelerometerDataX + String(";") 
                  + accelerometerDataY + String(";") 
                  + accelerometerDataZ);

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
  
  delay(1000);
}

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

int heartbeat(void) {
  Signal = analogRead(PulseSensorPurplePin);  
  int heartbeat = ((Signal/6)-10);
  return heartbeat; 
}

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













