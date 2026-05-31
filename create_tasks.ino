void sensorTask(void *pvParameters) {

  while(1) {
    Serial.println("Sensor Tsk Running");

    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}


void mqttTask(void *pvParameters) {

  while(1) {
    Serial.println("MQTT Running successfully");

    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}

void setup() {

  Serial.begin(115200);

  xTaskCreate(sensorTask, "Sensor Task", 2048, NULL, 1, NULL);
  xTaskCreate(mqttTask, "MQTT Task", 2048, NULL, 1, NULL);

  vTaskStartScheduler();

}

void loop() {
  
}
