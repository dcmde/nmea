#include <iostream>
#include "nmea.h"

int main() {
    gpgga_t gpgga{};

    gpgga.gpggaState = GPGGA_UTC;

    char msg[] = "134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,16.27,M,08,AAAA*60";

    for (char i : msg) {
        std::cout << i << " " << (int) nmea_decode_gpgga(&gpgga, i) << " " << (int) gpgga.stateCpt << std::endl;
    }

    std::cout << "Result : " << std::endl;
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
    std::cout << (int) gpgga.checksum << std::endl;

    return 0;
}
