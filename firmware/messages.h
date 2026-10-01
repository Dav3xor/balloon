#pragma once

#ifndef MESSAGES_H
#define MESSAGES_H

#define POSITION_MSG     1
#define WSPR_DONE_MSG    2
#define CAMERA_DONE_MSG  3

typedef struct SchedulerMessage {
  uint32_t type;
  union {
    struct {
      float latitude;
      float longitude;
    } position;
  }msg;  
};


#define TAKE_PICTURE_MSG 1

typedef struct CameraMessage {
  uint32_t type;
};

inline QueueHandle_t SchedulerQueue = NULL;
inline QueueHandle_t CameraQueue   = NULL;

#endif
