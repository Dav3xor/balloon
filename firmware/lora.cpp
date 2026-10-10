#include <RadioLib.h>
#include "radio.h"



void print_meshtastic_msg(byte *msg, size_t len){
  MeshtasticHeader *header = (MeshtasticHeader *)&msg[0];
  Serial.print("SRC: 0x");
  Serial.print(header->sender, HEX);
  Serial.print(" DST: 0x");
  Serial.print(header->destination, HEX);
  Serial.print(" PID: 0x");
  Serial.print(header->packet_id, HEX);
  Serial.print(" Flags: ");
  Serial.print(header->flags, BIN);
  Serial.print(" Channel: ");
  Serial.print(header->channel_hash, HEX);
  Serial.print(" Next Hop: ");
  Serial.print(header->next_hop, HEX);
  Serial.print(" Relay Node:");
  Serial.print(header->relay_node, HEX);
  Serial.println("");
}

// flag to indicate that a packet was received
volatile bool receivedFlag = false;

// this function is called when a complete packet
// is received by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  // we got a packet, set the flag
  receivedFlag = true;
}





void LoraTask(void * parameter) {
  Serial.print("LORA Task is running on Core: ");
  Serial.println(xPortGetCoreID()); // Prints which core it is running on

  // Setup pins based on your ESP32 wiring (NSS, DIO1, NRST, BUSY)
  SX1262 radio = new Module(3, 4, 2, 5); 
  //radio.tcxoVoltage = 0;



  // initialize SX1262 at 434 MHz
  Serial.print(F("[SX1262] Initializing ... "));
  ConfigLoRa_t config;
  config.frequency       = 906.875;
  config.bandwidth       = 250.0;
  config.spreadingFactor = 11;
  config.codingRate      = 5;
  config.preambleLength  = 16;
  config.syncWord        = 0x2b;



  int state = radio.begin(config);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("SX1262 initialized successfully!");
  } else {
    Serial.print("SX 1262 init failed: ");
    Serial.println(state);
    while(true) { delay(10);}
  }

  // set the function that will be called
  // when new packet is received
  radio.setPacketReceivedAction(setFlag);

  // start listening for LoRa packets
  Serial.print(F("[SX1262] Starting to listen ... "));
  state = radio.startReceive();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }





  for(;;) {
    //Serial.println("Hello from the GPS task!");
    if(receivedFlag) {
      // reset flag
      receivedFlag = false;

      // you can read received data as an Arduino String
      String str;
      //int state = radio.readData(str);

      // you can also read received data as byte array
      
        byte bytes[512];
        int numBytes = radio.getPacketLength() % 512;
        int state    = radio.readData(bytes, numBytes);
      

      if (state == RADIOLIB_ERR_NONE) {
        // packet was successfully received
        Serial.println(F("[SX1262] Received packet!"));

        // print data of the packet
        print_meshtastic_msg(bytes,numBytes);
        //Serial.print(F("[SX1262] Data:\t\t"));
        //Serial.println(str);

        // print RSSI (Received Signal Strength Indicator)
        Serial.print(F("[SX1262] RSSI:\t\t"));
        Serial.print(radio.getRSSI());
        Serial.println(F(" dBm"));

        // print SNR (Signal-to-Noise Ratio)
        Serial.print(F("[SX1262] SNR:\t\t"));
        Serial.print(radio.getSNR());
        Serial.println(F(" dB"));

        // print frequency error
        Serial.print(F("[SX1262] Frequency error:\t"));
        Serial.print(radio.getFrequencyError());
        Serial.println(F(" Hz"));

      } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
        // packet was received, but is malformed
        Serial.println(F("CRC error!"));

      } else {
        // some other error occurred
        Serial.print(F("failed, code "));
        Serial.println(state);

      }







    }
    vTaskDelay(1000/ portTICK_PERIOD_MS); 
    
  }
}