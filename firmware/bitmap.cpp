#include "bitmap.h"
#include <cstdio>


// total bytes: 786432
// bytes per line: 512
// lines high = 1536

// 8 bits per minor_spiral
// 7 bits per mid_spiral
// 4 bits per major_spiral
// 3 major spirals middle,top,bottom
int32_t minx = 100000;
int32_t maxx = -100000;
int32_t miny = 100000;
int32_t maxy = -100000;


uint32_t spiral_index(uint32_t pos) {
  uint8_t minor_spiral = pos         & 0xff;    // 16x16
  uint8_t mid_spiral   = (pos >> 8)  & 0x3f;    // 128x128
  uint8_t major_spiral = (pos >> 14) & 0xf;     // 512x512
  uint8_t section      = (pos >> 18) & 0x3;
  int32_t x = 256                        -73 + (128*spiralx[major_spiral]) + (16*spiralx[mid_spiral]) + spiralx[minor_spiral];
  int32_t y = section_y_centers[section] -73 + (128*spiraly[major_spiral]) + (16*spiraly[mid_spiral]) + spiraly[minor_spiral];   
  
  if(x<minx){
    minx=x;
  }
  if(x>maxx){
    maxx=x;
  }
  if(y<miny){
    miny=y;
  }
  if(y>maxy){
    maxy=y;
  }
  
  return y*512+x;
}

uint8_t get_spiral_byte(uint8_t *bitmap, uint32_t pos) {
  uint32_t index = spiral_index(pos);
  return bitmap[index];
}

void set_spiral_byte(uint8_t *bitmap, uint32_t pos, uint8_t val) {
  uint32_t index = spiral_index(pos);
  bitmap[index] = val;
} 





uint16_t get_two_bytes(uint8_t *bitmap, uint32_t pos) {
  uint8_t b1   = get_spiral_byte(bitmap, pos);
  uint8_t b2   = get_spiral_byte(bitmap, pos+1);
  
  uint8_t low  = 0;
  uint8_t high = 0;

  for (int32_t i = 7; i>0; i -= 2){
    low  = (low  << 1) + ((b1 >> i-1) & 1);
    high = (high << 1) + ((b1 >> i)   & 1);
  }
  for (int32_t i = 7; i>0; i -= 2){
    low  = (low  << 1) + ((b2 >> i-1) & 1);
    high = (high << 1) + ((b2 >> i)   & 1);
  }
  uint16_t retval =  (high << 8) + low;
  printf("b1: %08b b2: %08b low: %08b high: %08b retval: %08b\n", b1, b2, low, high, retval);
  return retval;
}





void set_two_bytes(uint8_t *bitmap, uint32_t pos, uint16_t val) {
  uint8_t b1  = 0;
  uint8_t b2 = 0;
  for (int i=3 ; i>=0; i-=1) {
    printf("%d\n",i);
    b2  = (b2  << 1) + ((val >> i+8)   & 1);
    b2  = (b2  << 1) + ((val >> i)   & 1);
  }
  for (int i=7; i>=4; i-=1) {
    printf("%d\n",i);
    b1  = (b1  << 1) + ((val >> i+8)   & 1);
    b1  = (b1  << 1) + ((val >> i)   & 1);
  }
  set_spiral_byte(bitmap,pos,b1);
  set_spiral_byte(bitmap,pos+1,b2);
  printf("val: %016b b1: %08b b2: %08b\n", val, b1, b2);
}







void print_extents(void){
  printf("minx = %d maxx = %d miny = %d maxy = %d",minx,maxx,miny,maxy);
}
