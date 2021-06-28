#include <iostream>
#include "nmea.h"

int main() {
    char msg[] = ".27,M,08,AAAA*60\n$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60\n$GPGGA,134658.00,5106.97";
    char in[80] = {0};

    for (auto it : msg) {
        nmea_handle_msg(it);
    }

    std::cout << (int) nmea_get_buffer(in, 85) << std::endl;

    return 0;
}
