#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <TimeLib.h>


#define PCAP_VERSION_MAJOR 0x02 /*!< Major Version */
#define PCAP_VERSION_MINOR 0x04 /*!< Minor Version */
#define PCAP_MAGIC_BIG_ENDIAN 0xA1B2C3D4    /*!< Big-Endian */
#define PCAP_MAGIC_LITTLE_ENDIAN 0xD4C3B2A1 /*!< Little-Endian */
#define PCAP_TIME_ZONE_GMT 0x00 /*!< Time Zone */
#define PCAP_SIGFLAG 0x05
#define PCAP_MAX_LENGTH 4294967295
const uint16_t PCAP_LINK_TYPE_802_11 = 105;

void sniffer(uint8_t *buf, uint16_t len){
  uint32_t sec = now();
  uint32_t micro = (unsigned int)(micros()-millis() * 1000); 
  newPacket(sec,micro,len,buf);
}

void write32(uint32_t num)
{
    uint8_t buf[4];
    buf[0]=num;
    buf[1]=num>>8;
    buf[2]=num>>16;
    buf[3]=num>>24;
    Serial.write(buf,4);
}
void write16(uint16_t num)
{
    uint8_t buf[2];
    buf[0]=num;
    buf[1]=num>>8;
    Serial.write(buf,2);
}


void newPacket(uint32_t sec, uint32_t micsec, uint32_t len, uint8_t * buf)
{
    write32(sec);
    write32(micsec);
    write32(len);
    write32(len);
    Serial.write(buf,len);
}

void startSerial()
{
        write32((uint32_t)PCAP_MAGIC_BIG_ENDIAN);
        write16((uint16_t)PCAP_VERSION_MAJOR);
        write16((uint16_t)PCAP_VERSION_MINOR);
        write32((uint32_t)PCAP_TIME_ZONE_GMT);
        write32((uint32_t)PCAP_SIGFLAG);
        write32((uint32_t)PCAP_MAX_LENGTH);
        write32((uint32_t)PCAP_LINK_TYPE_802_11);
}

void setup() {
  Serial.begin(9600);
  
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_set_channel(1);
  wifi_promiscuous_enable(1);
  delay(10000);
  Serial.println("<<<START>>>")
}

void loop() {
  delay(10000);
}
