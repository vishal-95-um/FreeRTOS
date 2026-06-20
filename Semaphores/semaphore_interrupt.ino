#define led 22
#define button 21

SemaphoreHandle_t buttonSemaphore; // Declaring Semaphore Variable

void ledTask(void *pvParameters) {

  while(1) {

    xSemaphoreTake(buttonSemaphore, portMAX_DELAY);

    Serial.println("LED Task : Event Received");

    digitalWrite(led, !digitalRead(led));
  }

}

void IRAM_ATTR buttonISR()
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR(buttonSemaphore, &higherPriorityTaskWoken);

    portYIELD_FROM_ISR(higherPriorityTaskWoken); // if variable is true -> Context Switching
}

void setup() {

  Serial.begin(115200);

  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  buttonSemaphore = xSemaphoreCreateBinary(); // Initializing Semaphore 

  attachInterrupt(digitalPinToInterrupt(button), buttonISR, FALLING); // FALLING because, button goes LOW when pressed

  xTaskCreate(ledTask, "LED Task", 2048, NULL, 1, NULL);

}


void loop() {

}