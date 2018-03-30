#include <LiquidCrystal.h>

 LiquidCrystal lcd (8, 9,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
// runs one time when starting

lcd.begin(16, 2);
lcd.print("Hello World!");
Serial.begin(115200);
Serial.println("Hello world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  // logica van het systeem
  
  int pubg = 1324;
  double level = 12.3;
  String output = "";
  lcd.println(String("[") + level + String("|") + pubg + String("]"));
  Serial.println(String("[") + level + String("|") + pubg + String("]"));
  delay(1000);
  lcd.clear();
}
