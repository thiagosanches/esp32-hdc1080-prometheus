#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include "ClosedCube_HDC1080.h"

#define LED 2

ClosedCube_HDC1080 hdc1080;
WiFiServer espServer(80);

const char* ssid = "";
const char* password = "";

void setup() {
  Serial.begin(9600);
  hdc1080.begin(0x40);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  String myLocalIP = WiFi.localIP().toString();
  Serial.println("CONNECTED");
  Serial.print("IP=");
  Serial.println(myLocalIP);

  espServer.begin();

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  handleRequest();
}

void handleRequest()
{
  WiFiClient client = espServer.available();
  if (!client) {
    return;
  }

  while (client.connected())
  {
    String response = "# HELP iot_temperature Temperature in celsius\n# TYPE iot_temperature gauge\niot_temperature ";
    response += hdc1080.readTemperature();
    response += "\n# HELP iot_humidity Humidity in percentage\n# TYPE iot_humidity gauge\niot_humidity ";
    response += hdc1080.readHumidity();
    response += "\n";

    client.printf("HTTP/1.1 200 OK\nContent-Type: text/plain; version=0.0.4\nContent-Length: %u\n\n%s", response.length(), response.c_str());
    client.flush();
    break;
  }
  client.stop();
}
