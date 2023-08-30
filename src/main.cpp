#include <Arduino.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);

//Variaveis sensor
const int sensorPin = 32; 
const int wetReading = 1700;
const int dryReading = 4095;
const int wetPertcent = 100;
const int dryPercent = 0;

const char* ssid = "Fazenda_Flores";
const char* password = "CP29216668";

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.printf("Conectando a rede Wifi %s\n", ssid);
    delay(1000);
  }
  delay(2000);
  Serial.printf("Conectado a rede Wifi %s\n", ssid);
  delay(2000);
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());
  delay(2000);
  
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    int sensorValue = analogRead(sensorPin);
    int percent = map(sensorValue, dryReading, wetReading, dryPercent, wetPertcent);
    String message = String(percent);
    request->send(200, "text/plain", message);
  });

  server.begin();
}

void loop() {
  int sensorValue = analogRead(sensorPin);  
  int percent = map(sensorValue, dryReading, wetReading, dryPercent, wetPertcent);  
  Serial.print("Umidade do solo: ");
  Serial.print(percent);
  Serial.println("%");

  delay(1000); 
}
