#include <iostream>
#include <cstring>
#include "nmea.h"

int main() {
//    char msg[] = ".27,M,08,AAAA*60\n$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60\n$GPGGA,134658.00,5106.97";
//    char msg[] = "$GPGGA,142056.00,,,,,0,00,99.99,,,,,,*62\n";
//    char msg[] = "$GPGLL,5107.0013414,N,11402.3279144,W,205412.00,A,A*73\n";
//    char msg[] = "$GPGLL,,,,,142036.00,V,N*48\n";
//    char msg[] = "$GPVTG,,T,,M,0.016,N,0.029,K,A*2F\n";
    char msg[] = "$GPVTG,,T,,M,0.016,N,0.029,K,A*2F\n";

//    for (auto it : msg) {
//        char in[80] = {0};
//        nmea_handle_msg(it);
//    }
//    int temp = nmea_get_buffer(in, 85);
//    std::cout << temp << std::endl;
//    std::cout << in << std::endl;

    gpvtg_t gpvtg = {0};
    nmea_decode_gpvtg(&gpvtg, msg, strlen(msg));
    std::cout << gpvtg.trackDegreeTrue << std::endl;
    std::cout << gpvtg.trackDegreeMagnetic << std::endl;
    std::cout << gpvtg.gndSpeedN << std::endl;
    std::cout << gpvtg.gndSpeedK << std::endl;

//    gpggl_t gpggl = {0};
//    nmea_decode_gpggl(&gpggl, in, 53);
//    std::cout << gpggl.gps.latitude << std::endl;
//    std::cout << (char) gpggl.gps.NS << std::endl;
//    std::cout << gpggl.gps.longitude << std::endl;
//    std::cout << (char) gpggl.gps.EW << std::endl;
//    std::cout << (int) gpggl.utcTime.hh << std::endl;
//    std::cout << (int) gpggl.utcTime.mm << std::endl;
//    std::cout << (int) gpggl.utcTime.ss << std::endl;
//    std::cout << (char) gpggl.gpsDataStatus << std::endl;

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
