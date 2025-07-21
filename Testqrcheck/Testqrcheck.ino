#include "ESP32QRCodeReader.h"
#include "esp_heap_caps.h"

#ifndef ps_malloc
#define ps_malloc(size) heap_caps_malloc(size, MALLOC_CAP_SPIRAM)
#endif

// GPIO14 as trigger
#define TRIGGER_PIN 14

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  reader.setup();
  Serial.println("QR Code Reader Initialized. Press GPIO14 to GND to scan.");
}

void loop() {
  if (digitalRead(TRIGGER_PIN) == LOW) {
    Serial.println("Trigger Pressed: Capturing and decoding...");

    QRCodeData qrData;

    // Try to receive QR with 3000ms timeout
    bool found = reader.receiveQrCode(&qrData, 3000);

    if (found && qrData.valid) {
      Serial.print("QR Code Detected: ");
      Serial.println((char*)qrData.payload);
    } else {
      Serial.println("No QR code detected or invalid QR.");
    }

    // Wait for button release
    while (digitalRead(TRIGGER_PIN) == LOW) delay(50);
    delay(200); // Debounce
  }
}
