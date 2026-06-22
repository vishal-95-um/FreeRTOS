TimerHandle_t tempTimer;
TimerHandle_t mqttTimer;

void tempCallback(TimerHandle_t xTimer) {

  Serial.println("Read Temperature...");

}

void mqttCallback(TimerHandle_t xTimer) {

  Serial.println("Send MQTT Data...");

}

void setup() {
  Serial.begin(115200);

  tempTimer = xTimerCreate("Temp",                           // Timer name
                            pdMS_TO_TICKS(2000),             // Period
                            pdTRUE,                          // Auto reload (Periodic)
                            NULL,                            // Timer Id
                            tempCallback);                   // Callback Function

  mqttTimer = xTimerCreate("MQTT", pdMS_TO_TICKS(5000), pdTRUE, NULL, mqttCallback);

  xTimerStart(tempTimer, 0);
  xTimerStart(mqttTimer, 0);

}

void loop() {
  

}
