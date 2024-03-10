#include <LiquidCrystal.h>
// initialize lcd object
LiquidCrystal lcd(9, 8, 2, 3, 4, 5);
// pin constants
const int sensorPin = A0;
const int potiPin = A1;
const int motorPin = 11;
// temperature constants
const float maxTemp = 40.0;
const float tempFactor = maxTemp/1024; 

void setup() {
  // serial connection to console for printouts 
  Serial.begin(9600);
  
  // motor starts off
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);

  // start LCD screen and set dimensions on screen
  lcd.begin(16,2);
}

void loop() {

   // read sensor and poti values from analog input
   int sensorVal = analogRead(sensorPin);
   int potiVal = analogRead(potiPin);

   // calculate voltage, temperature and thresholdTemp
   float voltage = (sensorVal/1024.0) * 5.0;
   float temperature = (voltage -.5)*100;
   float thresholdTemp = potiVal * tempFactor;

   // print to console
   Serial.print("Sensor Value: ");
   Serial.print(sensorVal);   
   Serial.print(", Volts: ");
   Serial.print(voltage);
   Serial.print(", Degrees C: ");
   Serial.print(temperature); 
   Serial.print(", potiVal: ");
   Serial.print(potiVal);
   Serial.print(", thresholdTemp: ");
   Serial.println(thresholdTemp);

   // print to lcd display
   lcd.setCursor(0,0);
   lcd.print("Max Temp: ");
   lcd.print(thresholdTemp);
   
   lcd.setCursor(0,1);
   lcd.print("Now Temp: ");
   lcd.print(temperature);

   // activating the motor based on temp and threshold temp
   if(temperature < thresholdTemp){
    digitalWrite(motorPin, LOW);
    
   } else if (temperature >= thresholdTemp){ 
    digitalWrite(motorPin, HIGH);
   }
   
   delay(500);
}
