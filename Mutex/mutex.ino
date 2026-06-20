#include "DHT11.h"

#define sensor_pin 34

DHT11 dht11(4);

SemaphoreHandle_t serialMutex;

int sensorValue = 0;
float baseline = 0;
float pulseSignal = 0;
float threshold = 100;      

bool beatDetected = false;
unsigned long lastBeatTime = 0;
int BPM = 0;

void getBPM();
void getTemp();


void bpmSensorTask(void *pvParameters) {

  while(1) {

    getBPM();

    vTaskDelay(pdMS_TO_TICKS(1000));

  }

}

void tempSensorTask(void *pvParameters) {

  while(1) {
    
    getTemp();

    vTaskDelay(pdMS_TO_TICKS(1000));


  }
}



void setup() {
  Serial.begin(115200);

  serialMutex = xSemaphoreCreateMutex();

  xTaskCreate(bpmSensorTask, "BPM Task", 2048, NULL, 1, NULL);
  xTaskCreate(tempSensorTask, "Temperature Task", 2048, NULL, 1, NULL);

}

void loop() {
  

}

void getBPM()
{
    // Read sensor
    sensorValue = analogRead(sensor_pin);

    // DC removal filter
    baseline = (baseline * 0.95) + (sensorValue * 0.05);

    // AC component
    pulseSignal = sensorValue - baseline;

    if (pulseSignal > threshold && !beatDetected)
    {
        beatDetected = true;

        unsigned long currentTime = millis();

        if (lastBeatTime > 0)
        {
            int interval = currentTime - lastBeatTime;
            BPM = 60000 / interval;
        }

        lastBeatTime = currentTime;

        // Protect Serial only
        xSemaphoreTake(serialMutex, portMAX_DELAY);

        Serial.print("BPM: ");
        Serial.println(BPM);

        xSemaphoreGive(serialMutex);
    }

    if (pulseSignal < threshold)
    {
        beatDetected = false;
    }
}

void getTemp()
{
    float temp = dht11.readTemperature();

    xSemaphoreTake(serialMutex, portMAX_DELAY);

    if (temp != DHT11::ERROR_CHECKSUM &&
        temp != DHT11::ERROR_TIMEOUT)
    {
        Serial.print("Temperature: ");
        Serial.println(temp);
    }
    else
    {
        Serial.println("Temperature Sensor Error");
    }

    xSemaphoreGive(serialMutex);
}