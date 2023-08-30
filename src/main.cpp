#include <Arduino.h>

//Variaveis sensor
const int sensorPin = 32; 
const int wetReading = 1500;
const int dryReading = 4095;
const int wetPertcent = 100;
const int dryPercent = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);  
  int percent = map(sensorValue, dryReading, wetReading, dryPercent, wetPertcent);  
  Serial.print("Umidade do solo: ");
  Serial.print(percent);
  Serial.println("%");

  delay(1000);  
}
