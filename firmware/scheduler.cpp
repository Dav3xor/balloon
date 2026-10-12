#include <Arduino.h>
#include "messages.h"
#include "wishlist.h"





float distance(double lat1, double lon1, double lat2, double lon2) {
  double result = (acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2)) * 180.0 * 60.0);
  if (result < 20.0) {
    result = (2*asin(sqrt(pow(sin((lat1-lat2)/2),2.0) + 
              cos(lat1)*cos(lat2)*pow((sin((lon1-lon2)/2)),2.0)))) * 180.0 * 60.0; // convert to nautical miles
  }
  return result;
}

void init_targets(void) {
  for (int i=0;i<NUM_TARGETS;i++) {
    sorted_targets[i] = i;
  }
}


// use insertion sort, because once it's sorted, it'll
// only change very slowly.
void sort_targets(void) {
  unsigned long startTime = micros();
  uint32_t num_swaps = 0;
  int index = 0;

  while (index < NUM_TARGETS) {
    if (index == 0)
      index++;                        // targets[sorted_targts[index].distance >]
    if (targets[sorted_targets[index]].distance >= targets[sorted_targets[index - 1]].distance)
      index++;
    else {
      uint32_t temp = sorted_targets[index];
      sorted_targets[index] = sorted_targets[index - 1];
      sorted_targets[index - 1] = temp;
      num_swaps += 1;
      //swap(sorted_targets[index], sorted_targets[index - 1]);
      index--;
    }
  }
  Serial.print("sort elapsed: ");
  Serial.print(micros() - startTime);
  Serial.print(", num_swaps: ");
  Serial.println(num_swaps);
}

void get_distances(float new_lat, float new_lon) {
  Serial.print("cur position: ");
  Serial.print(new_lat);
  Serial.print(", ");
  Serial.println(new_lon);

  new_lat = new_lat*3.14159/180.0;
  new_lon = new_lon*3.14159/180.0;

  for (int i = 0; i < NUM_TARGETS; i++){
    Target *cur_target = &targets[i];
    float cur_distance = distance(new_lat,new_lon, 
                                  cur_target->lat, cur_target->lon);
    Serial.print(cur_target->id);
    Serial.print(": ");
    Serial.print(cur_target->distance);
    Serial.print(" - ");
    Serial.print(cur_distance);
    Serial.println(cur_distance > cur_target->distance ? " decreasing":" increasing");
    // ...
    cur_target->distance = cur_distance;
  }
}
void change_position(float lat, float lon){
  // TODO: update target list, etc...

  //Serial.print("New Location: ");
  //Serial.print(lat);
  //Serial.print(",");
  //Serial.print(lon);
  //Serial.println("");
  
  get_distances(lat,lon);
  sort_targets();
  // for now, just take a picture...
  //CameraMessage take_picture = {TAKE_PICTURE_MSG};
  //xQueueSend(CameraQueue,
  //            ( void * ) &take_picture, 
  //            ( TickType_t ) 0 );

}


// 1. Define the task function
void SchedulerTask(void * parameter) {
  Serial.print("Scheduler Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on


  float lat_speed = 0;

  init_targets();

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