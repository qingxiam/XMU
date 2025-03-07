#include <stdint.h>
#pragma pack(push, 1)
struct ethernet_frame_header {
    uint8_t  dest_mac[6];
    uint8_t  src_mac[6];
    uint16_t ether_type;
};
#pragma pack(pop)
