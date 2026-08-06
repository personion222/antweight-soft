#include <esp_now.h>
#include <ESP32Servo.h>
#include <WiFi.h>

typedef struct message_struct {
	uint8_t lmotor;
	uint8_t rmotor;
	uint8_t servo;
} message_struct;

message_struct recv_data;

const int SERVO_PIN = D8;
const int MIN_PULSE = 1000;
const int MAX_PULSE = 2000;

const int L_DIR_PIN = D0;
const int L_PWM_PIN = D1;
const int R_PWM_PIN = D2;
const int R_DIR_PIN = D3;

const bool REV_L = false;
const bool REV_R = false;

Servo flipper;

void on_recv(const esp_now_recv_info *info, const uint8_t *data_in, int len) {
	memcpy(&recv_data, data_in, sizeof(recv_data));
	Serial.println("\nreceived data");
	Serial.print("lmotor: ");
	Serial.println(recv_data.lmotor);
	Serial.print("rmotor: ");
	Serial.println(recv_data.rmotor);
	Serial.print("servo: ");
	Serial.println(recv_data.servo);

	flipper.writeMicroseconds(map(recv_data.servo, 0, 255, MIN_PULSE, MAX_PULSE));

	digitalWrite(L_DIR_PIN, REV_L ? recv_data.lmotor >= 127 : recv_data.lmotor < 127);
	digitalWrite(R_DIR_PIN, REV_R ? recv_data.rmotor >= 127 : recv_data.rmotor < 127);

	analogWrite(L_PWM_PIN, recv_data.lmotor <= 127 ? map(recv_data.lmotor, 0, 127, 255, 0) : map(recv_data.lmotor, 128, 255, 0, 255));
	analogWrite(R_PWM_PIN, recv_data.rmotor <= 127 ? map(recv_data.rmotor, 0, 127, 255, 0) : map(recv_data.rmotor, 128, 255, 0, 255));
}

void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	if (esp_now_init() != ESP_OK) {
		Serial.println("espnow init error");
		return;
	}
	esp_now_register_recv_cb(on_recv);

	flipper.attach(SERVO_PIN, MIN_PULSE, MAX_PULSE);
	pinMode(L_DIR_PIN, OUTPUT);
	pinMode(L_PWM_PIN, OUTPUT);
	pinMode(R_PWM_PIN, OUTPUT);
	pinMode(R_DIR_PIN, OUTPUT);
}

void loop() {}
