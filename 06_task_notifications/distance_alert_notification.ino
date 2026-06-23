const int trigPin = 5;
const int echoPin = 18;

TaskHandle_t receiverTask = NULL; // define as we need access to later it later


void sensorTask(void *pvParameters) {

  while(1) {

   float distance = getDistance();

   Serial.print("Distance: ");
   Serial.println(distance);

   if(distance < 20 && distance > 0) xTaskNotifyGive(receiverTask);

   vTaskDelay(pdMS_TO_TICKS(3000));

  }

}

void alertTask(void *pvParameters) {

  while(1) {

  uint32_t count = ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait & Block forever so execution cant reach next line until next line

  Serial.print("Notifications received: ");
  Serial.println(count);

  Serial.println("Distance is less than threshold...");

  }

}

void setup() {

 Serial.begin(115200);

 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 delay(2000);

 xTaskCreate(sensorTask, "Sensor Task", 2048, NULL, 1, NULL);
 xTaskCreate(alertTask, "Alert Task", 2048, NULL, 1, &receiverTask);

}

void loop() {
  

}


float getDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  // timeout set to 30000 µs (~5 meters max range) to prevent blocking
  long duration = pulseIn(echoPin, HIGH, 30000); 
  
  if (duration == 0) {
    return -1.0; // Return -1.0 if out of range or read failed
  }
  
  float distance = (duration * 0.0343) / 2.0;
  
  return distance;
}