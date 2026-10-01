#include <Arduino.h>
#include "messages.h"


void change_position(float lat, float lon){
  // TODO: update target list, etc...

  //Serial.print("New Location: ");
  //Serial.print(cur_message.msg.position.latitude);
  //Serial.print(",");
  //Serial.print(cur_message.msg.position.longitude);
  //Serial.println("");
  
  // for now, just take a picture...
  CameraMessage take_picture = {TAKE_PICTURE_MSG};
  xQueueSend(CameraQueue,
              ( void * ) &take_picture, 
              ( TickType_t ) 0 );

}


// 1. Define the task function
void SchedulerTask(void * parameter) {
  Serial.print("Scheduler Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on


  float lat_speed = 0;



  for(;;) {
    SchedulerMessage cur_message;

        if( xQueueReceive( SchedulerQueue,
                           &( cur_message),
                           portMAX_DELAY))

        {
          switch(cur_message.type) {
            case POSITION_MSG:
              change_position(cur_message.msg.position.latitude, 
                              cur_message.msg.position.longitude);
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
    //vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}