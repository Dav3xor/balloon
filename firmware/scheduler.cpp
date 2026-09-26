#include <Arduino.h>
#include "messages.h"

// 1. Define the task function
void SchedulerTask(void * parameter) {
  Serial.print("Scheduler Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on


  float lat_speed = 0;

  for(;;) {
    Serial.println("Hello from the GPS task!");
    Position cur_position;

        if( xQueueReceive( LocationQueue,
                           &( cur_position),
                           ( TickType_t ) 10 ) == pdPASS )

        {
            Serial.print("New Location: ");
            Serial.print(cur_position.latitude);
            Serial.print(",");
            Serial.print(cur_position.longitude);
            Serial.println("");


        }

    // Always use vTaskDelay instead of delay() inside FreeRTOS tasks
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}