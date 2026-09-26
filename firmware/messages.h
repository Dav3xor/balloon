#pragma once

#ifndef MESSAGES_H
#define MESSAGES_H


typedef struct Position {
  float latitude;
  float longitude;
};

inline QueueHandle_t LocationQueue = NULL;

#endif
