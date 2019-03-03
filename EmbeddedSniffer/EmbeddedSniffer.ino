#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <TimeLib.h>

#define PCAP_VERSION_MAJOR 0x02 /*!< Major Version */
#define PCAP_VERSION_MINOR 0x04 /*!< Minor Version */
#define PCAP_MAGIC_BIG_ENDIAN 0xA1B2C3D4    /*!< Big-Endian */
#define PCAP_MAGIC_LITTLE_ENDIAN 0xD4C3B2A1 /*!< Little-Endian */
#define PCAP_TIME_ZONE_GMT 0x00 /*!< Time Zone */
#define PCAP_SIGFLAG 0x00
#define PCAP_MAX_LENGTH sizeof(int)
const uint16_t PCAP_LINK_TYPE_802_11 = 105;

const int chip_select = D8;
File PCAP_File;

void closePCAP (File file)
{
  file.close();
}

void sniffer(uint8_t *buf, uint16_t len){
  uint32_t sec = now();
  uint32_t micro = (unsigned int)(micros()-millis() * 1000); 
  newPacket(sec,micro,len,buf,PCAP_File);
}

void write32(uint32_t num, File file)
{
    uint8_t buf[4];
    buf[0]=num;
    buf[1]=num>>8;
    buf[2]=num>>16;
    buf[3]=num>>24;
    file.write(buf,4);
}
void write16(uint16_t num, File file)
{
    uint8_t buf[2];
    buf[0]=num;
    buf[1]=num>>8;
    file.write(buf,2);
}


void newPacket(uint32_t sec, uint32_t micsec, uint32_t len, uint8_t * buf, File file)
{
    write32(sec,file);
    write32(micsec,file);
    write32(len, file);
    write32(len,file);
    file.write(buf,len);
}

File openPCAP(char * file)
{
  if(SD.exists(file))
  {
    SD.remove(file);
    Serial.println("[*]Previous File Removed") ;
    }
    File pcap = SD.open(file, FILE_WRITE);
    if(pcap){
        Serial.println("[S] File Opened Successfully");
        write32((uint32_t)PCAP_MAGIC_BIG_ENDIAN,pcap);
        write16((uint16_t)PCAP_VERSION_MAJOR,pcap);
        write16((uint16_t)PCAP_VERSION_MINOR,pcap);
        write32((uint32_t)PCAP_TIME_ZONE_GMT,pcap);
        write32((uint32_t)PCAP_SIGFLAG, pcap);
        write32((uint32_t)PCAP_MAX_LENGTH, pcap);
        write32((uint32_t)PCAP_LINK_TYPE_802_11,pcap);
        return pcap;
    }
    Serial.println("[!] File Could Not Be Opened");
    return pcap;
}

void setup() {
  Serial.begin(9600);
  
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_set_channel(1);
  wifi_promiscuous_enable(1);
  if(!SD.begin(chip_select)){
    Serial.println("SD Card Not Found");
    return;
  }
  Serial.println("Initializing Complete.");
  Serial.println("[*] Sniffer Started");
  PCAP_File = openPCAP("pcap");
}
int i = 1;
void loop() {
  if(i){
  delay(10000);
  closePCAP(PCAP_File);
  Serial.println("[*] Sniffer Closed");
  i--;
  }
  exit(0);
}
