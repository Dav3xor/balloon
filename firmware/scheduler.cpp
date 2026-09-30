#include <Arduino.h>
#include "messages.h"

// 1. Define the task function
void SchedulerTask(void * parameter) {
  Serial.print("Scheduler Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on


  float lat_speed = 0;

  for(;;) {
    SchedulerMessage cur_message;

        if( xQueueReceive( LocationQueue,
                           &( cur_message),
                           ( TickType_t ) 10 ) == pdPASS )

        {
          switch(cur_message.type) {
            case POSITION_MSG:
              //Serial.print("New Location: ");
              //Serial.print(cur_message.msg.position.latitude);
              //Serial.print(",");
              //Serial.print(cur_message.msg.position.longitude);
              //Serial.println("");
              break;
            case CAMERA_DONE_MSG:
              //Serial.println("Camera Finished!");
              break;
            case WSPR_DONE_MSG:
              //Serial.println("WSPR Done Transmitting");
              break;
          }

        }

    // Always use vTaskDelay instead of delay() inside FreeRTOS tasks
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}