#include <Arduino.h>
#include "messages.h"
#include "navigation.h"

// 1. Define the task function
void GPSTask(void* parameter) {
  Serial.print("GPS Task is running on Core: ");
  Serial.println(xPortGetCoreID());  // Prints which core it is running on


  float lat_speed = 0;

  for (;;) {
    //Serial.println("Hello from the GPS task!");
    Point point(deg_to_rad(45.01),deg_to_rad(-123.5+lat_speed));

    SchedulerMessage cur_position = { .type = POSITION_MSG, 
                                      .msg = { .position = { .pos = point, 
                                                             .course = 0, 
                                                             .speed = 0 } } };
    lat_speed += .005;

    xQueueSend(SchedulerQueue,
               (void*)&cur_position,
               (TickType_t)0);
    // Always use vTaskDelay instead of delay() inside FreeRTOS tasks
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
