#include "nmea.h"

uint8_t nmea_decode_gpgga(gpgga_t *gpgga, char in) {
    switch (gpgga->gpggaState) {
        case NONE:
            break;
        case UTC:
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
                        gpgga->gpggaState = LAT;
                        gpgga->stateCpt = 0;
                        return 0;
                    }
            }
            gpgga->stateCpt++;
            break;
        case LAT:
            if (in != ',') {
                if (in != '.') {
                    gpgga->gps.latitude *= 10;
                    gpgga->gps.latitude += (in - 48);
                }
            } else {
                gpgga->gps.latitude /= 1e4f;
                gpgga->gpggaState = NOS;
            }
            break;
        case NOS:
            if (in != ',') {
                gpgga->gps.NS = in == N ? N : S;
            } else {
                gpgga->gpggaState = LON;
            }
            break;
        case LON:
            if (in != ',') {
                if (in != '.') {
                    gpgga->gps.longitude *= 10;
                    gpgga->gps.longitude += (in - 48);
                }
            } else {
                gpgga->gps.longitude /= 1e4f;
                gpgga->gpggaState = EOW;
            }
            break;
        case EOW:
            if (in != ',') {
                gpgga->gps.EW = in == E ? E : W;
            } else {
                gpgga->gpggaState = QUALITY_ID;
            }
            break;
        case QUALITY_ID:
            if (in != ',') {
                gpgga->quality = (GPS_QUALITY_INDICATOR) in;
            } else {
                gpgga->gpggaState = NUM_SAT;
            }
            break;
        case NUM_SAT:
            if (in != ',') {
                gpgga->numSatView *= 10;
                gpgga->numSatView += (in - 48);
            } else {
                gpgga->gpggaState = HOR_DOP;
            }
            break;
        case HOR_DOP:
            if (in != ',') {
                if (in != '.') {
                    gpgga->hdop *= 10;
                    gpgga->hdop += (in - 48);
                }
            } else {
                gpgga->gpggaState = ALT;
                gpgga->hdop /= 10.f;
            }
            break;
        case ALT:
            if (in != ',') {
                if (in != '.' && in != 'M') {
                    gpgga->altitudeMSL *= 10;
                    gpgga->altitudeMSL += (in - 48);
                }
            } else if (gpgga->stateCpt != 1) {
                gpgga->stateCpt++;
            } else {
                gpgga->gpggaState = HEIGHT_WGS;
                gpgga->altitudeMSL /= 100.f;
                gpgga->stateCpt = 0;
            }
            break;
        case HEIGHT_WGS:
            if (in != ',') {
                if (in != '.' && in != 'M') {
                    gpgga->heightAboveWGS *= 10;
                    gpgga->heightAboveWGS += (in - 48);
                }
            } else if (gpgga->stateCpt != 1) {
                gpgga->stateCpt++;
            } else {
                gpgga->gpggaState = TIME_SIMCE_LAST_UPDATE;
                gpgga->heightAboveWGS /= 100.f;
                gpgga->stateCpt = 0;
            }
            break;
        case TIME_SIMCE_LAST_UPDATE:
            if (in != ',') {
                gpgga->timeSinceLastDGPS *= 10;
                gpgga->timeSinceLastDGPS += (in - 48);
            } else {
                gpgga->gpggaState = DGPS;
            }
            break;
        case DGPS:
            if (in != '*') {
                gpgga->DGPSRefID[gpgga->stateCpt] = in;
                gpgga->stateCpt++;
            } else {
                gpgga->gpggaState = CHECKSUM;
                gpgga->stateCpt = 0;
            }
            break;
        case CHECKSUM:
            gpgga->checksum *= 10;
            gpgga->checksum += (in - 48);
            gpgga->stateCpt++;
            if (gpgga->stateCpt == 2) {
                gpgga->gpggaState = NONE;
                gpgga->stateCpt = 0;
            }
            break;
    }
    return 0;
}

