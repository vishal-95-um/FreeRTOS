#include <WiFi.h>

#define sensorBit (1 << 0)
#define wifiBit (1 << 1)

EventGroupHandle_t myEventGroup;

void sensorTask(void *pvParameters) {

  Serial.println("Sensor Initializing...");

  vTaskDelay(pdMS_TO_TICKS(3000));

  Serial.println("Sensor Task Ready");

  xEventGroupSetBits(myEventGroup, sensorBit);

  vTaskDelete(NULL);

}

void wifiTask(void *pvParameters) {

  Serial.println("Wifi Initializing...");

  vTaskDelay(pdMS_TO_TICKS(4000));

  Serial.println("Wifi Task Ready");

  xEventGroupSetBits(myEventGroup, wifiBit);

  vTaskDelete(NULL);

}

void mainTask(void *pvParameters) {

  Serial.println("Waiting for Sensor and WiFi");

  xEventGroupWaitBits(
    myEventGroup,  // event group name
    sensorBit | wifiBit, // waiting on these bits
    pdFALSE, // dont clear bits
    pdTRUE, // wait for all bits (use pdFALSE if want only any of bit)
    portMAX_DELAY // wait forever
  );

  Serial.println("Both Sensor and Wifi Task Ready");

  vTaskDelete(NULL);

}

void setup() {
  Serial.begin(115200);

  delay(2000);

  myEventGroup = xEventGroupCreate();

  xTaskCreate(sensorTask, "Sensor Task", 2048, NULL, 1, NULL);
  xTaskCreate(wifiTask, "WiFi Task", 2048, NULL, 1, NULL);
  xTaskCreate(mainTask, "Main Task", 2048, NULL, 1, NULL);

}

void loop() {

}


