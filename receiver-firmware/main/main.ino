#include <esp_now.h>
#include <WiFi.h>

typedef struct message_struct {
  int8_t lmotor;
  int8_t rmotor;
  int8_t servo;
} message_struct;

message_struct recv_data;

void on_recv(const esp_now_recv_info *info, const uint8_t *data_in, int len) {
  memcpy(&recv_data, data_in, sizeof(recv_data));
  Serial.println("\nreceived data");
  Serial.print("lmotor: ");
  Serial.println(recv_data.lmotor);
  Serial.print("rmotor: ");
  Serial.println(recv_data.rmotor);
  Serial.print("servo: ");
  Serial.println(recv_data.servo);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("espnow init error");
    return;
  }

  esp_now_register_recv_cb(on_recv);
}
 
void loop() {

}
