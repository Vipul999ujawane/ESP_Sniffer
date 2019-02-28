#include <string.h>
#include <PCAP.h>
#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <esp_types.h>
#include <esp_err.h>
#include <esp_log.h>

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
File openPCAP(char * file)
{
    File pcap = SD.open(file, FILE_WRITE);
    if(pcap){
        Serial.println("[S] File Opened Successfully");
        write32((uint32_t)PCAP_MAGIC_BIG_ENDIAN);
        write16((uint16_t)PCAP_VERSION_MAJOR);
        write16((uint16_t)PCAP_VERSION_MINOR);
        write16((uint16_t)PCAP_TIME_ZONE_GMT);
        write16((uint16_t)pcap_link_type_t PCAP_LINK_TYPE_802_11);
        return pcap;
    }
    Serial.println("[!] File Could Not Be Opened");
    return pcap
}
bool closePCAP(File file)
{
    file.close();
}