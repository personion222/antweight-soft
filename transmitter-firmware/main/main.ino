#include <esp_now.h>
#include <WiFi.h>

// receiver mac: 3C:DC:75:AE:79:64
const uint8_t broadcast_address[] = {0x3C, 0xDC, 0x75, 0xAE, 0x79, 0x64};

struct message_struct {
  int8_t lmotor;
  int8_t rmotor;
  int8_t servo;
};

message_struct send_data;

esp_now_peer_info_t peer_info = {};

void on_send(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("\r\npacket status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "delivery success" : "delivery fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("espnow init error");
    return;
  }

  esp_now_register_send_cb(on_send);
  
  memcpy(peer_info.peer_addr, broadcast_address, 6);
  peer_info.channel = 0;  
  peer_info.encrypt = false;
  
  if (esp_now_add_peer(&peer_info) != ESP_OK) {
    Serial.println("failed to add peer");
    return;
  }
}

void loop() {
  if (Serial.available() >= 3) {
    char data[3];
    Serial.readBytes(data, 3);
    send_data.lmotor = data[0];
    send_data.rmotor = data[1];
    send_data.servo = data[2];

    esp_err_t result = esp_now_send(broadcast_address, (uint8_t *) &send_data, sizeof(send_data));
    if (result == ESP_OK) {
      Serial.println("sent successfully");
    }
    else {
      Serial.println("unable to send");
    }
  }

  delay(50);
}
