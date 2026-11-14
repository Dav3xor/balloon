#include <fcntl.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "bitmap.h"


void compare_bitmaps(uint8_t *b1, uint8_t *b2, size_t len) {
  uint32_t good=0;
  uint32_t bad=0;
  for (int i=0; i<len; i++) {
    if (b1[i] == b2[i]) {
      good += 1;
    } else {
      printf("? %d: %08b - %08b\n",i,b1[i], b2[i]);
      bad += 1;
    }
  }
  printf("compare result:\n");
  printf("good - %d\n", good);
  printf("bad  - %d\n", bad);
}

int main(void) {
  uint8_t bitmap[CAM_OUTBUFSIZE];
  uint8_t bitmap2[CAM_OUTBUFSIZE];

  int f = open("image.bin", O_RDONLY);
  if(f<0){
    printf("failed to open bitmap\n");
    exit(-1);
  }
  
  ssize_t r = read(f, bitmap, CAM_OUTBUFSIZE);
  if(r != CAM_OUTBUFSIZE) {
    printf("failed to read bitmap\n");
    exit(-1);
  }

  memcpy(bitmap2,bitmap,CAM_OUTBUFSIZE);
  
  //for(int i = 0; i<786432; i++) {
  for(int i = 0; i<10; i++) {
    uint8_t x = get_spiral_byte(bitmap,i);
    printf("%u\n",x);
  }
  //print_extents();
  uint16_t val = get_two_bytes(bitmap,100000);
  set_two_bytes(bitmap2,100000,val);


  compare_bitmaps(bitmap,bitmap2, CAM_OUTBUFSIZE);

  return 0;
}
