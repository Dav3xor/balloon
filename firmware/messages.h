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

inline QueueHandle_t LocationQueue = NULL;

#endif
