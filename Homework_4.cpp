#include <cstdint>
#include <cstring>
typedef uint8_t MAC_address[6];
#pragma pack(push, 1)
struct EthernetFrame {
    MAC_address dest_addr;
    MAC_address src_addr;   
    uint16_t type;        
};
#pragma pack(pop)
MAC_address this_mac_address = {0x00, 0x50, 0x56, 0xC0, 0x00, 0x01};
int mac_address_match(const EthernetFrame *frame) {
    static const MAC_address broadcast = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    if (memcmp(frame->dest_addr, broadcast, 6) == 0) {
        return 1;
    }
    if ((frame->dest_addr[0] & 0x01) == 0x01) {
        return 1;
    }
    if (memcmp(frame->dest_addr, this_mac_address, 6) == 0) {
        return 1;
    }
    return 0;
}
