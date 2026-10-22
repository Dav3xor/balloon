#include <Arduino.h>
#include "messages.h"
#include "wishlist.h"
#include "navigation.h"




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

  //Serial.print("sort elapsed: ");
  //Serial.print(micros() - startTime);
  //Serial.print(", num_swaps: ");
  //Serial.println(num_swaps);
}

void get_distances(Point &newp) {
  //Serial.print("cur position: ");
  //Serial.print(newp.lat);
  //Serial.print(", ");
  //Serial.println(newp.lon);

  //float new_lat = newp.lat*3.14159/180.0;
  //float new_lon = newp.lon*3.14159/180.0;

  for (int i = 0; i < NUM_TARGETS; i++){
    Target *cur_target = &targets[i];
    Point curp(cur_target->lat, cur_target->lon);
    float cur_distance = distance(newp, curp);
    //Serial.print(cur_target->id);
    //Serial.print(": ");
    //Serial.print(cur_target->distance);
    //Serial.print(" - ");
    //Serial.print(cur_distance);
    //Serial.println(cur_distance > cur_target->distance ? " decreasing":" increasing");
    // ...
    cur_target->distance = cur_distance;
  }
}
void change_position(Point &point){
  static uint32_t counter = 0;
  // TODO: update target list, etc...

  //Serial.print("New Location: ");
  //Serial.print(lat);
  //Serial.print(",");
  //Serial.print(lon);
  //Serial.println("");
  
  get_distances(point);
  sort_targets();

  Point target = { .lat = targets[sorted_targets[0]].lat, .lon = targets[sorted_targets[0]].lon};
  Fix fix = build_fix(point,target,3.14159,.005);
  //print_point(point);
  //print_point(target);
  //print_point(fix.closest);
  print_fix(fix);
  // for now, just take a picture...
  CameraMessage take_picture = {TAKE_PICTURE_MSG};
  if (!counter) {
    xQueueSend(CameraQueue,
                ( void * ) &take_picture, 
                ( TickType_t ) 0 );
    counter += 1;
  }

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
            case POSITION_MSG: {
              Point newp(cur_message.msg.position.pos.lat, cur_message.msg.position.pos.lon);
              change_position(newp);
              break;
            }
            case CAMERA_READY_MSG:
              //Serial.println("Camera Finished!");
              break;
          }

        }

    // Always use vTaskDelay instead of delay() inside FreeRTOS tasks
    //vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}
