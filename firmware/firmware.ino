#include <SD_MMC.h>
#include <sd_defines.h>

#include "tasks.h"
#include "messages.h"
//#include <FS.h>
//#include <SD.h>
#include <SPI.h>
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  while(!Serial);

  Serial.setDebugOutput(true);


  // Build queues
  SchedulerQueue = xQueueCreate(10, sizeof(SchedulerMessage));
  CameraQueue   = xQueueCreate(10, sizeof(CameraMessage));

  // Start our tasks
  xTaskCreatePinnedToCore(
    GPSTask,           // Name of the task function
    "GPSTask",  // Descriptive name for debugging
    10000,             // Stack size in words (allocate enough memory)
    NULL,              // Parameter to pass to the task (NULL if none)
    1,                 // Task priority (higher numbers = higher priority)
    &GPSTaskHandle,     // Task handle to track the task (NULL if not needed)
    0                  // Core ID: Run on Core 0 (Arduino loop runs on Core 1 by default)
  );
  
  xTaskCreatePinnedToCore(
    SchedulerTask,           // Name of the task function
    "SchedulerTask",  // Descriptive name for debugging
    10000,             // Stack size in words (allocate enough memory)
    NULL,              // Parameter to pass to the task (NULL if none)
    1,                 // Task priority (higher numbers = higher priority)
    &SchedulerTaskHandle,     // Task handle to track the task (NULL if not needed)
    0                  // Core ID: Run on Core 0 (Arduino loop runs on Core 1 by default)
  );

   xTaskCreatePinnedToCore(
    LoraTask,           // Name of the task function
    "LoraTask",  // Descriptive name for debugging
    10000,             // Stack size in words (allocate enough memory)
    NULL,              // Parameter to pass to the task (NULL if none)
    1,                 // Task priority (higher numbers = higher priority)
    &LoraTaskHandle,     // Task handle to track the task (NULL if not needed)
    0                  // Core ID: Run on Core 0 (Arduino loop runs on Core 1 by default)
  );

  
  xTaskCreatePinnedToCore(
    CameraTask,           // Name of the task function
    "CameraTask",  // Descriptive name for debugging
    10000,             // Stack size in words (allocate enough memory)
    NULL,              // Parameter to pass to the task (NULL if none)
    1,                 // Task priority (higher numbers = higher priority)
    &SchedulerTaskHandle,     // Task handle to track the task (NULL if not needed)
    1                  // Core ID: Run on Core 0 (Arduino loop runs on Core 1 by default)
  );

}

void loop() {
  //Serial.println("main loop...");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}








