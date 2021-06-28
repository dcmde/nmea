#include <iostream>
#include "nmea.h"

int main() {
    char msg[] = ".27,M,08,AAAA*60\n$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60\n$GPGGA,134658.00,5106.97";
    char in[80] = {0};

    for (auto it : msg) {
        nmea_handle_msg(it);
    }

    std::cout << (int) nmea_get_buffer(in, 85) << std::endl;
    std::cout << in << std::endl;

    gpgga_t gpgga = {0};
    nmea_decode_gpgga(&gpgga, in, 79);

    std::cout << (int) gpgga.utcTime.hh << std::endl;
    std::cout << (int) gpgga.utcTime.mm << std::endl;
    std::cout << (int) gpgga.utcTime.ss << std::endl;
    std::cout << gpgga.gps.latitude << std::endl;
    std::cout << (char) gpgga.gps.NS << std::endl;
    std::cout << gpgga.gps.longitude << std::endl;
    std::cout << (char) gpgga.gps.EW << std::endl;
    std::cout << gpgga.quality - 48 << std::endl;
    std::cout << (int) gpgga.numSatView << std::endl;
    std::cout << gpgga.hdop << std::endl;
    std::cout << gpgga.altitudeMSL << std::endl;
    std::cout << gpgga.heightAboveWGS << std::endl;
    std::cout << (int) gpgga.timeSinceLastDGPS << std::endl;
    std::cout << gpgga.DGPSRefID << std::endl;

    return 0;
}
