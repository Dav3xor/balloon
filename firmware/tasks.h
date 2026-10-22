#ifndef TASKS_H
#define TASKS_H

void GPSTask(void *); 
void SchedulerTask(void *);
void CameraTask(void *);
void SPITask(void *);


// Task Handles...
inline TaskHandle_t GPSTaskHandle = NULL;
inline TaskHandle_t SchedulerTaskHandle = NULL;
inline TaskHandle_t CameraTaskHandle = NULL;
inline TaskHandle_t SPITaskHandle = NULL;


#endif