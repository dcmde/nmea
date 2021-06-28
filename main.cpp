#include <iostream>
#include "nmea.h"

int main() {
//    char msg[] = ".27,M,08,AAAA*60\n$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60\n$GPGGA,134658.00,5106.97";
    char in[80] = {0};
    char msg[] = "$GPGLL,5107.0013414,N,11402.3279144,W,205412.00,A,A*73\n";

    for (auto it : msg) {
        nmea_handle_msg(it);
    }

    std::cout << (int) nmea_get_buffer(in, 85) << std::endl;
    std::cout << in << std::endl;

    gpggl_t gpggl = {0};

    nmea_decode_gpggl(&gpggl, in, 53);

    std::cout << gpggl.gps.latitude << std::endl;
    std::cout << (char) gpggl.gps.NS << std::endl;
    std::cout << gpggl.gps.longitude << std::endl;
    std::cout << (char) gpggl.gps.EW << std::endl;
    std::cout << (int) gpggl.utcTime.hh << std::endl;
    std::cout << (int) gpggl.utcTime.mm << std::endl;
    std::cout << (int) gpggl.utcTime.ss << std::endl;
    std::cout << (char) gpggl.gpsDataStatus << std::endl;

//    gpgga_t gpgga = {0};
//    nmea_decode_gpgga(&gpgga, in, 79);
//
//    std::cout << (int) gpgga.utcTime.hh << std::endl;
//    std::cout << (int) gpgga.utcTime.mm << std::endl;
//    std::cout << (int) gpgga.utcTime.ss << std::endl;
//    std::cout << gpgga.gps.latitude << std::endl;
//    std::cout << (char) gpgga.gps.NS << std::endl;
//    std::cout << gpgga.gps.longitude << std::endl;
//    std::cout << (char) gpgga.gps.EW << std::endl;
//    std::cout << gpgga.quality - 48 << std::endl;
//    std::cout << (int) gpgga.numSatView << std::endl;
//    std::cout << gpgga.hdop << std::endl;
//    std::cout << gpgga.altitudeMSL << std::endl;
//    std::cout << gpgga.heightAboveWGS << std::endl;
//    std::cout << (int) gpgga.timeSinceLastDGPS << std::endl;
//    std::cout << gpgga.DGPSRefID << std::endl;

    return 0;
}
