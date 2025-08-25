#include "utils/checksum.h"

unsigned short checksum(const void *data, size_t len) {
    register unsigned long sum = 0;
    const unsigned short *ptr = data;
    while (len > 1) {
        sum += (unsigned short) *(ptr++);
        len -= 2;
    }
    if (len > 0)
        sum += *(unsigned char *) ptr;
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);
    return (unsigned short) ~sum;
}
