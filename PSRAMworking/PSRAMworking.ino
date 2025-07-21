#include "esp_heap_caps.h"
#include "esp_system.h"

void setup() {
  Serial.begin(115200);

  if (psramInit()) {
    Serial.println("PSRAM is working ✅");
    Serial.print("PSRAM Size: ");

    //Serial.println(esp_psram_get_size() / (1024 * 1024));
    //Serial.println("MB");
  } else {
    Serial.println("PSRAM is NOT working ❌");
  }
}

void loop() {}
