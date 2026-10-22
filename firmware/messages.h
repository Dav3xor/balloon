#pragma once

#ifndef MESSAGES_H
#define MESSAGES_H

#include "navigation.h"

#define POSITION_MSG     1
#define CAMERA_READY_MSG  3

typedef struct SchedulerMessage {
  uint32_t type;
  union {
    struct {
      Point pos;
      float course; 
      float speed;
    } position;
  }msg;  
};


#define TAKE_PICTURE_MSG 1
#define FILE_WRITTEN_MSG 2

typedef struct CameraMessage {
  uint32_t type;
};


#define SPI_WRITE_IMG_MSG  1
#define SPI_LORA_OFF_MSG   2
#define SPI_LORA_ON_MSG    3
#define SPI_LOG_MSG        4
#define SPI_LORA_MODE_MSG  5
#define SPI_LORA_WRITE_MSG 6

typedef struct SPIMessage {
  uint32_t type;
  union {
    struct {
      uint8_t *fb;
      size_t len;
      uint8_t *info;
      uint8_t *info_len;
    } write_img;
    struct {
      char log[256];
    } log;
    struct {
      char msg[256];
    } lora_msg;
    struct {
      float   frequency;
      float   bandwidth;
      uint8_t spreadingFactor;
      uint8_t codingRate;
      uint8_t preambleLength;
      uint8_t syncWord;
    } lora_mode;
  }msg;
};

inline QueueHandle_t SchedulerQueue = NULL;
inline QueueHandle_t CameraQueue    = NULL;
inline QueueHandle_t SPIQueue       = NULL;

#endif
