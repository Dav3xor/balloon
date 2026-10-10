#include <Arduino.h>
#include "messages.h"
#include "compression/lz.h"
#include "esp_camera.h"
#include "FS.h"
#include "SD.h"



#define	CAM_XMCLK	10
#define	CAM_DVP_Y8 11
#define	CAM_DVP_Y7 12
#define	CAM_DVP_PCLK 13

#define	CAM_DVP_Y6 14
#define	CAM_DVP_Y2 15
#define	CAM_DVP_Y5 16
#define	CAM_DVP_Y3 17
#define	CAM_DVP_Y4 18
#define	CAM_DVP_VSYNC 38
#define	CAM_CAM_SCL	39
#define	CAM_CAM_SDA 40
#define	CAM_DVP_HREF 47	
#define	CAM_DVP_Y9 48

// define what width/height we're using
#define CAM_WIDTH       160
#define CAM_HEIGHT      120
#define CAM_FRAMESIZE     FRAMESIZE_QQVGA
//#define CAM_FRAMESIZE   FRAMESIZE_SXGA
//#define CAM_FRAMESIZE   FRAMESIZE_QXGA
#define CAM_OUTBUFSIZE  (CAM_WIDTH*CAM_HEIGHT)/4

#define CAM_PIN_PWDN -1
/*
void writeFile(fs::FS &fs, const char *path, uint8_t *data, size_t len){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }

  size_t num_chunks = len/512;
  for (int i=0; i<num_chunks; i++) {
    size_t num_write = 512;
    if (i*512 + 512 > len) {
      num_write = len-(i*512);
    }
    int result=file.write(&data[i*512],num_write);
    if (result < num_write) {
        Serial.printf("Write failed! Expected %d bytes, wrote %d\n", num_write, result);
        break;
        // Check standard error codes
    }
    yield();
  }
  file.close();
  Serial.println("- file written");
}
*/

static camera_config_t camera_config = {
    .pin_pwdn  = CAM_PIN_PWDN,
    .pin_reset = -1,
    .pin_xclk = CAM_XMCLK,
    .pin_sccb_sda = CAM_CAM_SDA,
    .pin_sccb_scl = CAM_CAM_SCL,

    .pin_d7 = CAM_DVP_Y9,
    .pin_d6 = CAM_DVP_Y8,
    .pin_d5 = CAM_DVP_Y7,
    .pin_d4 = CAM_DVP_Y6,
    .pin_d3 = CAM_DVP_Y5,
    .pin_d2 = CAM_DVP_Y4,
    .pin_d1 = CAM_DVP_Y3,
    .pin_d0 = CAM_DVP_Y2,
    .pin_vsync = CAM_DVP_VSYNC,
    .pin_href = CAM_DVP_HREF,
    .pin_pclk = CAM_DVP_PCLK,

    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_GRAYSCALE,//YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = CAM_FRAMESIZE,//QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.

    .jpeg_quality = 12, //0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 1, //When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .fb_location = CAMERA_FB_IN_PSRAM,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY//CAMERA_GRAB_LATEST. Sets when buffers should be filled
};

uint8_t *outbuf = NULL;

const char *grays = " .~*&%@#";
//const char *grays2 = " ~+#";
const char *grays2 = "#+~ ";
const int16_t midpoints[4] = { 32, 96, 160, 224 };

int8_t clamp(int16_t val, int16_t error){
  if (val+error > 255) {
    return 255;
  } else if (val+error < 0) {
    return 0;
  } else {
    return val+error;
  }
}



// do a line of floyd-steinberg
void floyd_steinberg(size_t width, uint8_t *inbuf, uint8_t *outbuf){  
  for (int i = 1; i < width-1; i++){
    // first, determine the current pixel's error from the ideal
    int16_t error           = inbuf[i]-midpoints[inbuf[i]>>6];

    // then add it into the floyd-steinberg buffer...
    inbuf[i+1]       = clamp(inbuf[i+1],       (error*7) >> 4);
    inbuf[i+width-1] = clamp(inbuf[i+width-1], (error*3) >> 4);
    inbuf[i+width]   = clamp(inbuf[i+width],   (error*5) >> 4);
    inbuf[i+width+1] = clamp(inbuf[i+width+1], error >> 4);
  }
}



void make_2bit(size_t width, size_t height, uint8_t *inbuf, uint8_t *outbuf) {
    uint8_t cur_byte = 0;
    for(int i = 0; i < width*height; i++){

      uint32_t cur_byte_pos   = i % 4;
      uint8_t val             = inbuf[i] >> 6;



      // stuff the resulting 2 bits into the current byte of outbuf
      cur_byte                = (cur_byte << 2) + val;
      if (cur_byte_pos == 3) {
          outbuf[i>>2] = cur_byte;
      }   
  }

}




void process_image(size_t width, size_t height, pixformat_t format, uint8_t *buf, size_t len) {

  uint8_t  cur_byte = 0;
  for(uint32_t i = 0; i < height; i++) {
      floyd_steinberg(width,&buf[i*width],&outbuf[(i*width)>>2]);            
  }
  make_2bit(width, height, buf,outbuf);
  Serial.println("capture");
  uint32_t zoom = 20;

  // print the original buffer from the camera
  //for(int i=0; i < height/zoom; i++) {
  //    for(int j=0; j < width/zoom*2; j++){
  //        Serial.print(grays[buf[i*(width*zoom) + j*zoom/2]>>5]);
  //    }
  //    Serial.println("");
  //}

  // print the 2 bits per pixel result.
  for(int i=0; i < height/zoom; i++) {
      for(int j=0; j < width/zoom*2; j++){
          Serial.print(grays2[(outbuf[i*((width>>2)*zoom) + ((j*zoom)>>2)/2] >> 6)&3]);
      }
      Serial.println("");
  }
  //writeFile(LittleFS, "/image.bin", outbuf, CAM_OUTBUFSIZE);  

}



















esp_err_t camera_init(){
    //power up the camera if PWDN pin is defined
    if(CAM_PIN_PWDN != -1){
        pinMode(CAM_PIN_PWDN, OUTPUT);
        digitalWrite(CAM_PIN_PWDN, LOW);
    }

    //initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

esp_err_t camera_capture(){
    //acquire a frame
    for(int i=0;i<5;i++){
      camera_fb_t *fb = esp_camera_fb_get();
      esp_camera_fb_return(fb);
    }
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }

    process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
  
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
    return ESP_OK;
}


// 1. Define the task function
void CameraTask(void * parameter) {
  Serial.print("Camera Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on


  Serial.println("camera init...");
  int init_result = camera_init();
  if (init_result == ESP_OK) {
    Serial.println("camera is go");
  } else {
    Serial.print("camera init failed, result code: ");
    Serial.println(init_result);
  }
  
  Serial.println("camera init done");
 
  //Serial.println("allocating buffer");
  outbuf = (uint8_t *)malloc(CAM_OUTBUFSIZE);
  
  if (outbuf == NULL ) {
    Serial.println("buffer allocation failed");
  }
  


  uint32_t num_pictures = 0;

  for(;;) {
    CameraMessage cur_message;
    if( xQueueReceive( CameraQueue,
                        &( cur_message),
                        portMAX_DELAY)) {
      switch(cur_message.type) {
        case TAKE_PICTURE_MSG:
          if(num_pictures % 3 == 0){
            Serial.println("taking picture...");
              camera_capture();
              //Serial.print("New Location: ");
              //Serial.print(cur_message.msg.position.latitude);
              //Serial.print(",");
              //Serial.print(cur_message.msg.position.longitude);
              //Serial.println("");
          }
          num_pictures += 1;
          break;
        case CAMERA_DONE_MSG:
          //Serial.println("Camera Finished!");
          break;
        case WSPR_DONE_MSG:
          //Serial.println("WSPR Done Transmitting");
          break;
        }
      }

    }

}


