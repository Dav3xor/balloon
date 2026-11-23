#include "bitmap.h"
#include <cstdio>

#define MAX_REPEAT 254
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
    b1  = (b1  << 1) + ((val >> i+8) & 1);
    b1  = (b1  << 1) + ((val >> i)   & 1);
  }
  set_spiral_byte(bitmap,pos,  b1);
  set_spiral_byte(bitmap,pos+1,b2);
  printf("val: %016b b1: %08b b2: %08b\n", val, b1, b2);
}


//uint32_t duplicate_count(uint8_t *input, size_t inlen) {
//  for (uint32_t i = 1; i < inlen; i++) {
//    if((input[i] != input[0]) || (i > 254) {
//      return i-1;
//    }
//}

uint32_t compress_RLE_huffman_simple(uint8_t *input,  uint32_t startpos,
                                     uint8_t *output, size_t   outlen) {
  uint32_t curpos  = startpos;
  uint32_t consumed = 0;
  uint8_t i        = 1;
  
  uint8_t cur_byte  = get_spiral_byte(input, curpos);
  uint8_t next_byte = 0;
  while (curpos < outlen) {
    for (i = 1; i < MAX_REPEAT; i++) {
      next_byte = get_spiral_byte(input, curpos+i);
      if (next_byte != cur_byte) {
        break;
      }
    }
    output[curpos]     = i-1; 
    output[curpos+1]   = cur_byte;
    consumed          += (i+1);
    cur_byte           = next_byte;
    curpos            += 2;
  }
  return consumed;
}

void print_extents(void){
  printf("minx = %d maxx = %d miny = %d maxy = %d",minx,maxx,miny,maxy);
}
