#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("mac: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  delay(10000);
}