#pragma once

#ifndef MSGS_H
#define MSGS_H

#include <cstdint>




#define MESHTASTIC_MSG_LEN 200
#define MESHCORE_MSG_LEN 184



struct ImageMsgHeader {
  uint16_t target_id;
  uint8_t  balloon_id;
  uint8_t  minor_pos;
  uint8_t  middle_pos;
  uint8_t  major_pos;
}__attribute__((__packed__));

#define MESHTASTIC_PAYLOAD_LEN (MESHTASTIC_MSG_LEN - sizeof(ImageMsgHeader))
#define MESHCORE_PAYLOAD_LEN   (MESHCORE_MSG_LEN   - sizeof(ImageMsgHeader))

struct MeshtasticImageMsg {
  ImageMsgHeader header;
  uint8_t msg[MESHTASTIC_PAYLOAD_LEN];
}__attribute__((__packed__));

struct MeshcoreImageMsg {
  ImageMsgHeader header;
  uint8_t msg[MESHCORE_PAYLOAD_LEN];
}__attribute__((__packed__));


#endif