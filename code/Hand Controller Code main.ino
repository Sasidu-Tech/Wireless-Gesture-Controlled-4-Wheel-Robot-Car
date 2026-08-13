#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// =====================================================
// PUT YOUR CAR ESP32 MAC ADDRESS HERE: CAR MAC: 68:09:47:5E:D6:C8
// =====================================================

uint8_t carMAC[] = {
  0x68, 0x09, 0x47,
  0x5E, 0xD6, 0xC8
};


// =====================================================
// DATA STRUCTURE
// =====================================================

typedef struct {
  char command;
} ControlData;

ControlData data;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);
  delay(1000);

  // ===================================================
  // MPU6050
  // ===================================================

  Wire.begin(21, 22);

  Serial.println();
  Serial.println("Starting MPU6050...");

  mpu.initialize();

  Serial.println("MPU6050 Initialized");


  // ===================================================
  // WIFI
  // ===================================================

  WiFi.mode(WIFI_STA);

  Serial.println();
  Serial.print("CONTROLLER MAC: ");
  Serial.println(WiFi.macAddress());


  // ===================================================
  // ESP-NOW
  // ===================================================

  if (esp_now_init() != ESP_OK) {

    Serial.println("ESP-NOW INIT FAILED!");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("ESP-NOW Initialized");


  // ===================================================
  // ADD CAR ESP32 AS PEER
  // ===================================================

  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr, carMAC, 6);

  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  if (esp_now_add_peer(&peerInfo) != ESP_OK) {

    Serial.println("FAILED TO ADD CAR PEER!");

    while (true) {
      delay(1000);
    }
  }

  Serial.println();
  Serial.println("==============================");
  Serial.println(" CONTROLLER READY");
  Serial.println("==============================");
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;


  // ===================================================
  // READ MPU6050
  // ===================================================

  mpu.getMotion6(
    &ax,
    &ay,
    &az,
    &gx,
    &gy,
    &gz
  );


  // ===================================================
  // CONVERT ACCELEROMETER
  // ±2G = 16384 LSB/G
  // ===================================================

  float X = ax / 16384.0;
  float Y = ay / 16384.0;


  // ===================================================
  // DEFAULT = STOP
  // ===================================================

  char command = 'S';


  // ===================================================
  // FORWARD
  // ===================================================

  if (Y > 0.35) {

    command = 'F';
  }


  // ===================================================
  // BACKWARD
  // ===================================================

  else if (Y < -0.35) {

    command = 'B';
  }


  // ===================================================
  // RIGHT
  // ===================================================

  else if (X > 0.35) {

    command = 'R';
  }


  // ===================================================
  // LEFT
  // ===================================================

  else if (X < -0.35) {

    command = 'L';
  }


  // ===================================================
  // STOP
  // ===================================================

  else {

    command = 'S';
  }


  // ===================================================
  // SAVE COMMAND
  // ===================================================

  data.command = command;


  // ===================================================
  // SEND COMMAND
  // ===================================================

  esp_err_t result = esp_now_send(
    carMAC,
    (uint8_t *)&data,
    sizeof(data)
  );


  // ===================================================
  // SERIAL MONITOR
  // ===================================================

  Serial.print("X: ");
  Serial.print(X, 2);

  Serial.print(" | Y: ");
  Serial.print(Y, 2);

  Serial.print(" | COMMAND: ");
  Serial.print(command);

  if (result == ESP_OK) {
    Serial.println(" | SENT");
  }
  else {
    Serial.println(" | SEND ERROR");
  }


  delay(100);
}


