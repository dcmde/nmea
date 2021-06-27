#include "nmea.h"

uint8_t nmea_decode_gpgga(gpgga_t *gpgga, char in) {
    switch (gpgga->gpggaState) {
        case GPGGA_NONE:
            break;
        case GPGGA_UTC:
            switch (gpgga->stateCpt) {
                case 0:
                    gpgga->utcTime.hh = (in - 48) * 10;
                    break;
                case 1:
                    gpgga->utcTime.hh += (in - 48);
                    break;
                case 2:
                    gpgga->utcTime.mm = (in - 48) * 10;
                    break;
                case 3:
                    gpgga->utcTime.mm += (in - 48);
                    break;
                case 4:
                    gpgga->utcTime.ss = (in - 48) * 10;
                    break;
                case 5:
                    gpgga->utcTime.ss += (in - 48);
                    break;
                case 6:
                    if (in != '.') {
                        return 1;
                    }
                    break;
                case 9:
                    if (in != ',') {
                        return 1;
                    } else {
                        gpgga->gpggaState = GPGGA_LAT;
                        gpgga->stateCpt = 0;
                        return 0;
                    }
            }
            gpgga->stateCpt++;
            break;
        case GPGGA_LAT:
            if (in != ',') {
                if (in != '.') {
                    gpgga->gps.latitude *= 10;
                    gpgga->gps.latitude += (in - 48);
                }
            } else {
                gpgga->gps.latitude /= 1e4f;
                gpgga->gpggaState = GPGGA_NOS;
            }
            break;
        case GPGGA_NOS:
            if (in != ',') {
                gpgga->gps.NS = in == GPS_N ? GPS_N : GPS_S;
            } else {
                gpgga->gpggaState = GPGGA_LON;
            }
            break;
        case GPGGA_LON:
            if (in != ',') {
                if (in != '.') {
                    gpgga->gps.longitude *= 10;
                    gpgga->gps.longitude += (in - 48);
                }
            } else {
                gpgga->gps.longitude /= 1e4f;
                gpgga->gpggaState = GPGGA_EOW;
            }
            break;
        case GPGGA_EOW:
            if (in != ',') {
                gpgga->gps.EW = in == GPS_E ? GPS_E : GPS_W;
            } else {
                gpgga->gpggaState = GPGGA_QUALITY_ID;
            }
            break;
        case GPGGA_QUALITY_ID:
            if (in != ',') {
                gpgga->quality = (GPS_QUALITY_INDICATOR) in;
            } else {
                gpgga->gpggaState = GPGGA_NUM_SAT;
            }
            break;
        case GPGGA_NUM_SAT:
            if (in != ',') {
                gpgga->numSatView *= 10;
                gpgga->numSatView += (in - 48);
            } else {
                gpgga->gpggaState = GPGGA_HOR_DOP;
            }
            break;
        case GPGGA_HOR_DOP:
            if (in != ',') {
                if (in != '.') {
                    gpgga->hdop *= 10;
                    gpgga->hdop += (in - 48);
                }
            } else {
                gpgga->gpggaState = GPGGA_ALT;
                gpgga->hdop /= 10.f;
            }
            break;
        case GPGGA_ALT:
            if (in != ',') {
                if (in != '.' && in != 'M') {
                    gpgga->altitudeMSL *= 10;
                    gpgga->altitudeMSL += (in - 48);
                }
            } else if (gpgga->stateCpt != 1) {
                gpgga->stateCpt++;
            } else {
                gpgga->gpggaState = GPGGA_HEIGHT_WGS;
                gpgga->altitudeMSL /= 100.f;
                gpgga->stateCpt = 0;
            }
            break;
        case GPGGA_HEIGHT_WGS:
            if (in != ',') {
                if (in != '.' && in != 'M') {
                    gpgga->heightAboveWGS *= 10;
                    gpgga->heightAboveWGS += (in - 48);
                }
            } else if (gpgga->stateCpt != 1) {
                gpgga->stateCpt++;
            } else {
                gpgga->gpggaState = GPGGA_TIME_SIMCE_LAST_UPDATE;
                gpgga->heightAboveWGS /= 100.f;
                gpgga->stateCpt = 0;
            }
            break;
        case GPGGA_TIME_SIMCE_LAST_UPDATE:
            if (in != ',') {
                gpgga->timeSinceLastDGPS *= 10;
                gpgga->timeSinceLastDGPS += (in - 48);
            } else {
                gpgga->gpggaState = GPGGA_DGPS;
            }
            break;
        case GPGGA_DGPS:
            if (in != '*') {
                gpgga->DGPSRefID[gpgga->stateCpt] = in;
                gpgga->stateCpt++;
            } else {
                gpgga->gpggaState = GPGGA_CHECKSUM;
                gpgga->stateCpt = 0;
            }
            break;
        case GPGGA_CHECKSUM:
            gpgga->checksum *= 10;
            gpgga->checksum += (in - 48);
            gpgga->stateCpt++;
            if (gpgga->stateCpt == 2) {
                gpgga->gpggaState = GPGGA_NONE;
                gpgga->stateCpt = 0;
            }
            break;
    }
    return 0;
}

