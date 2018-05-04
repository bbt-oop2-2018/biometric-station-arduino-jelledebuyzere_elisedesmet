#include <LiquidCrystal.h>
#include <Wire.h> //easy to use A4 (SDA), A5 (SCL)
#

LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

void setup() {  // put your setup code here, to run once:
  // runs one time when starting
  Serial.begin(115200);
  
  //initialize wire library I2C Communication
  Wire.begin(); //temperature

  setupDisplay(); //werkt

  Serial.println("Hello world!");
}

void setupDisplay() {
  //lcd display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("Welcome to our");
  //delay(2000);
  lcd.setCursor(0, 1);
  lcd.write("biometric statio");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("n! Enjoy!");
  delay(2000);
  lcd.clear();
  lcd.print("TEMP(C): ");
}

void loop() {
  // put your main code here, to run repeatedly:
  // logica van het systeem

  int pubg = 1324;
  double level = 12.3;
  String output = "";

  // retrieve temp
  double temperature = infoSensor(); //temperatuur eerst
    // TODO: 2e accelerometer , 3e puls

  //print temp

  lcd.setCursor(9, 0); //start writing at 9
  lcd.print(temperature);
  Serial.println(String("Data of 3 different components: ") + String("[") + temperature + String("C |")); // we need to make string larger for accelerometer and pulse

  //lcd.println(String("[") + level + String("|") + pubg + String("]"));
  //Serial.println(String("[") + level + String("|") + pubg + String("]"));
  delay(500); //update every 1/2 second
}

//temperatuurmeter !!!!
double infoSensor(void) {


  //unsigned bit value
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





