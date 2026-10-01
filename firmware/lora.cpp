#include <RadioLib.h>
void LoraTask(void * parameter) {
  Serial.print("GPS Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on

  // Setup pins based on your ESP32 wiring (NSS, DIO1, NRST, BUSY)
  SX1262 radio = new Module(5, 14, 12, 13); 

  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("SX1262 initialized successfully!");
  }

  for(;;) {
    //Serial.println("Hello from the GPS task!");

    vTaskDelay(1000/ portTICK_PERIOD_MS); 
  }
}