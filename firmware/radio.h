#ifndef __RADIO_H__
#define __RADIO_H__

typedef struct MeshtasticHeader {
  uint32_t destination;
  uint32_t sender;
  uint32_t packet_id;
  uint8_t  flags;
  uint8_t  channel_hash;
  uint8_t  next_hop;
  uint8_t  relay_node;
} __attribute__((__packed__));

#endif