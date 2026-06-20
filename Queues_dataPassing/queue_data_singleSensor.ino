#include "DHT11.h"

DHT11 dht11(4);

QueueHandle_t myQueue;

typedef struct {
  float temp;
  float humidity;
} SensorData;

void sensorTask(void *pvParameters) {
  SensorData data;

  while(1) {

     data.temp = getTemp();
     data.humidity = getHumidity();

     xQueueSend(myQueue, &data, portMAX_DELAY); 

     /* Queue Overlflow Prevention techniques
     1. use 0 instead of portMAX_DELAY
     2. flush old data when queue is overlflow 
     if(uxQueueSpacesAvailable(myQueue) == 0) -> xQueueReset(myQueue)
     3. if(uxQueueSpacesAvailable(myQueue) > 0) -> then do xQueueSend
     4. xQueueOverwrite(myQueue, &data) -> only when queue size is 1 -> good when intermediate values are useless noise (temperature, battery level)
     */

     vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void uartTask(void *pvParameters) {

  SensorData receivedData;

  while(1) {

    if(xQueueReceive(myQueue, &receivedData, portMAX_DELAY) == pdTRUE) {

      Serial.print("The Temperature is: ");
      Serial.println(receivedData.temp);

      Serial.print("The Humidity is: ");
      Serial.println(receivedData.humidity);
    }

  }

}

void setup() {
 Serial.begin(115200);

 myQueue = xQueueCreate(10, sizeof(SensorData));
 xTaskCreate(sensorTask, "Sensor Task", 2048, NULL, 1, NULL);
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

float getHumidity()
{
    float humidity = dht11.readHumidity();

    if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
        return humidity;
    } else {
        return -555;
    }
}