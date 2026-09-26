#include <Arduino.h>
#include "messages.h"

// 1. Define the task function
void GPSTask(void * parameter) {
  Serial.print("GPS Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on


  float lat_speed = 0;

  for(;;) {
    Serial.println("Hello from the GPS task!");
    Position cur_position = {123.0+lat_speed,45.0};
    lat_speed += .01;

    xQueueSend(LocationQueue,
               ( void * ) &cur_position, 
               ( TickType_t ) 0 );
    // Always use vTaskDelay instead of delay() inside FreeRTOS tasks
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}

