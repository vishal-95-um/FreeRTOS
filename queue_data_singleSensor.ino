#include "DHT11.h"

DHT11 dht11(4);

QueueHandle_t myQueue;

void dhtTask(void *pvParameters) {

  while(1) {
    float temp = getTemp();
    if(xQueueSend(myQueue, &temp, portMAX_DELAY) == pdTRUE) {
          Serial.print("Sent: ");
          Serial.println(temp);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}


void uartTask(void *pvParameters) {
  float received_item;

  while(1) {
    if(xQueueReceive(myQueue, &received_item, portMAX_DELAY) == pdTRUE) {
      Serial.print("Received: ");
      Serial.println(received_item);
    }
  }

}

void setup() {

 Serial.begin(115200);

 myQueue = xQueueCreate(10, sizeof(float));

 if(myQueue == NULL) {
  Serial.println("Queue Creation Failed");
 }

 xTaskCreate(dhtTask, "DHT Task", 2048, NULL, 1, NULL);
 xTaskCreate(uartTask, "UART Task", 2048, NULL, 1, NULL);

}

void loop() {


}

float getTemp()
{
    float temp = dht11.readTemperature();

    if (temp != DHT11::ERROR_CHECKSUM && temp != DHT11::ERROR_TIMEOUT) {
        return temp;
    } else {
        return -555;
    }
}
