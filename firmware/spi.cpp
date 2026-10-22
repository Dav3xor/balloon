#include <RadioLib.h>
#include "radio.h"
#include "messages.h"
#include "FS.h"
//#include "SD.h"
#include "LittleFS.h"

#define FORMAT_LITTLEFS_IF_FAILED true

uint32_t picture_taken=0;



#define CHUNK_SIZE 512
void writeFile(fs::FS &fs, const char *path, uint8_t *data, size_t len){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }

  size_t num_chunks = len/CHUNK_SIZE;
  uint32_t i=0;
  for (i=0; i<num_chunks; i++) {
    int result=file.write(&data[i*512],CHUNK_SIZE);
    if (result < CHUNK_SIZE) {
        Serial.printf("Write failed! Expected %d bytes, wrote %d\n", CHUNK_SIZE, result);
        break;
        // Check standard error codes
    }
    yield();
  }
  // write the leftover bytes...
  if(i*CHUNK_SIZE < len){
    file.write(&data[(i+1)*512],len-(i*CHUNK_SIZE));
  }
  file.close();
  Serial.println("- file written");
}



void SPITask(void* parameter) {
  Serial.print("SPI Task is running on Core: ");
  Serial.println(xPortGetCoreID());  // Prints which core it is running on

  // Initialize LittleFS (the filesystem on the internal flash ram)
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("LittleFS Mount Failed");
  }



  for (;;) {
    SPIMessage cur_message;
    if( xQueueReceive( SPIQueue,
                        &( cur_message),
                        portMAX_DELAY)) {
      Serial.println(" ");
      Serial.println(" ");
      Serial.println("spi");
      Serial.println(" ");
      Serial.println(" ");
      Serial.println(" ");
      switch(cur_message.type) {
        case SPI_WRITE_IMG_MSG:
          if(picture_taken == 0){
            Serial.println("saving picture...");
            writeFile(LittleFS, "/image.bin", cur_message.msg.write_img.fb, cur_message.msg.write_img.len);
            Serial.println((uint32_t)cur_message.msg.write_img.fb);
            Serial.println(cur_message.msg.write_img.len);
            CameraMessage file_written = {FILE_WRITTEN_MSG};
            xQueueSend(CameraQueue,
                       ( void * ) &file_written, 
                       ( TickType_t ) 0 );
            picture_taken += 1;
          }
          break;
        }
    }

  }
}


