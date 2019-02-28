#include <stdio.h>

#define PCAP_MAGIC_BIG_ENDIAN 0xA1B2C3D4    /*!< Big-Endian */
#define PCAP_MAGIC_LITTLE_ENDIAN 0xD4C3B2A1 /*!< Little-Endian */

#define PCAP_VERSION_MAJOR 0x02 /*!< Major Version */
#define PCAP_VERSION_MINOR 0x04 /*!< Minor Version */

#define PCAP_TIME_ZONE_GMT 0x00 /*!< Time Zone */

#define PCAP_FILE_NAME_MAX_LEN 32 /*!< Max Name Length of Pcap File */

typedef enum {
    PCAP_LINK_TYPE_LOOPBACK = 0,       /*!< Loopback devices, except for later OpenBSD */
    PCAP_LINK_TYPE_ETHERNET = 1,       /*!< Ethernet, and Linux loopback devices */
    PCAP_LINK_TYPE_TOKEN_RING = 6,     /*!< 802.5 Token Ring */
    PCAP_LINK_TYPE_ARCNET = 7,         /*!< ARCnet */
    PCAP_LINK_TYPE_SLIP = 8,           /*!< SLIP */
    PCAP_LINK_TYPE_PPP = 9,            /*!< PPP */
    PCAP_LINK_TYPE_FDDI = 10,          /*!< FDDI */
    PCAP_LINK_TYPE_ATM = 100,          /*!< LLC/SNAP encapsulated ATM */
    PCAP_LINK_TYPE_RAW_IP = 101,       /*!< Raw IP, without link */
    PCAP_LINK_TYPE_BSD_SLIP = 102,     /*!< BSD/OS SLIP */
    PCAP_LINK_TYPE_BSD_PPP = 103,      /*!< BSD/OS PPP */
    PCAP_LINK_TYPE_CISCO_HDLC = 104,   /*!< Cisco HDLC */
    PCAP_LINK_TYPE_802_11 = 105,       /*!< 802.11 */
    PCAP_LINK_TYPE_BSD_LOOPBACK = 108, /*!< OpenBSD loopback devices(with AF_value in network byte order) */
    PCAP_LINK_TYPE_LOCAL_TALK = 114    /*!< LocalTalk */
} pcap_link_type_t;

void write16(uint16_t num,uint8_t* buf);
void write32(uint32_t num,uint8_t* buf);
File openPCAP(char* file);
bool closePCAP(File file);