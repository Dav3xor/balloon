#include "esp_camera.h"
#include "FS.h"
#include <LittleFS.h>

//WROVER-KIT PIN Map
#define CAM_PIN_PWDN    32 //power down is not used
#define CAM_PIN_RESET   -1 //software reset will be performed
#define CAM_PIN_XCLK    0
#define CAM_PIN_SIOD    26
#define CAM_PIN_SIOC    27

#define CAM_PIN_D7      35
#define CAM_PIN_D6      34
#define CAM_PIN_D5      39
#define CAM_PIN_D4      36
#define CAM_PIN_D3      21
#define CAM_PIN_D2      19
#define CAM_PIN_D1      18
#define CAM_PIN_D0       5
#define CAM_PIN_VSYNC   25
#define CAM_PIN_HREF    23
#define CAM_PIN_PCLK    22


// define what width/height we're using
#define CAM_WIDTH       1600
#define CAM_HEIGHT      1200
#define CAM_FRAMESIZE   FRAMESIZE_UXGA
#define CAM_OUTBUFSIZE  (CAM_WIDTH*CAM_HEIGHT)/4
static camera_config_t camera_config = {
    .pin_pwdn  = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

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
int8_t *fs_buf = NULL;
const char *grays = " .~*&%@#";
//const char *grays2 = " ~+#";
const char *grays2 = "#+~ ";
const uint8_t midpoints[4] = { 32, 96, 160, 124 };
uint32_t counter = 0;

int8_t clamp(int16_t val, int16_t error){
  if (val+error > 127) {
    return 127;
  } else if (val+error < -128) {
    return -128;
  } else {
    return val+error;
  }
}

uint8_t clamp2(int16_t a, int16_t b){
  if(a+b > 255) {
    return 255;
  } else if (a+b < 0) {
    return 0;
  } else {
    return a+b;
  }
}

// do a line of floyd-steinberg
void floyd_steinberg(size_t width, uint8_t *inbuf, uint8_t *outbuf){
  // move the floyd steinberg buffer forward a line
  memcpy((void *)fs_buf, 
         (void *)&fs_buf[width], 
         width);
  memset((void *)&fs_buf[width], 0, width);
  
  uint8_t cur_byte = 0;

  for (int i = 1; i < width-1; i++){
    // first, determine the current pixel's error from the ideal
    int16_t error           = inbuf[i]-midpoints[inbuf[i]>>6];

    // then add it into the floyd-steinberg buffer...
    fs_buf[i+1]       = clamp(fs_buf[i+1],       (error*7) / 4);
    fs_buf[i+width-1] = clamp(fs_buf[i+width-1], (error*3) / 4);
    fs_buf[i+width]   = clamp(fs_buf[i+width],   (error*5) / 4);
    fs_buf[i+width+1] = clamp(fs_buf[i+width+1], error / 4);


    int32_t cur_out_data    = inbuf[i] >> 6;
    uint32_t cur_byte_pos   = i % 4;
    uint8_t val             = clamp2(inbuf[i], fs_buf[i]) >> 6;



    // stuff the resulting 2 bits into the current byte of outbuf
    cur_byte                = (cur_byte << 2) + val;
    if (cur_byte_pos == 3) {
        outbuf[i>>2] = cur_byte;
    }   
  }

}




void process_image(size_t width, size_t height, pixformat_t format, uint8_t *buf, size_t len) {
    if (counter == 10){
        uint8_t  cur_byte = 0;
        for(uint32_t i = 0; i < height; i++) {
            floyd_steinberg(width,&buf[i*width],&outbuf[(i*width)>>2]);            
        }

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
        writeFile(LittleFS, "/image.bin", outbuf, CAM_OUTBUFSIZE);  
    }
    counter += 1;
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
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }
    //replace this with your own function
    process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
  
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
    return ESP_OK;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("allocating buffer");
  outbuf = (uint8_t *)malloc(CAM_OUTBUFSIZE);
  fs_buf = (int8_t *)malloc(CAM_WIDTH*2);
  if (outbuf != NULL && fs_buf != NULL) {
    memset(fs_buf,0,CAM_WIDTH*2);
  } else {
    Serial.println("buffer allocation failed");
  }
  Serial.println("camera init");
  Serial.println(camera_init());
  Serial.println("camera init done");
  
  if(!LittleFS.begin(true)){
  Serial.println("LittleFS Mount Failed");
  return;
}
}

void loop() {
  // put your main code here, to run repeatedly:
  camera_capture();
}





void writeFile(fs::FS &fs, const char *path, uint8_t *data, size_t len){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.write(data,len)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}


