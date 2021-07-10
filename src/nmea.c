#include <stdlib.h>
#include "include/nmea.h"

/**
 * @brief Allows to get the index of the ',' separator in the buffer.
 * @param buffer
 * @param msgSize
 * @param index
 * @param indexSize
 */
void split_index(const char *buffer, uint8_t msgSize, uint8_t *index, uint8_t indexSize) {
    uint8_t indexCpt = 0;
    for (uint8_t i = 0; i < msgSize; ++i) {
        if (buffer[i] != ',') {
            continue;
        } else {
            if (indexCpt < indexSize) {
                index[indexCpt++] = i;
            } else {
                return;
            }
        }
    }
}

/**
 * @brief
 * @param gpgga
 * @param buffer
 * @param size
 * @return
 */
uint8_t nmea_decode_gpgga(gpgga_t *gpgga, char buffer[], uint8_t size) {
    uint8_t index[14] = {0};
    split_index(buffer, size, index, 14); // GPGGA contains 14 comma.
    gpgga->utcTime.hh = (buffer[index[0] + 1] - 48) * 10 + (buffer[index[0] + 2] - 48);
    gpgga->utcTime.mm = (buffer[index[0] + 3] - 48) * 10 + (buffer[index[0] + 4] - 48);
    gpgga->utcTime.ss = (buffer[index[0] + 5] - 48) * 10 + (buffer[index[0] + 6] - 48);
    gpgga->gps.latitude = strtod(&buffer[index[1] + 1], NULL);
    gpgga->gps.NS = (GPS_NS) buffer[index[2] + 1];
    gpgga->gps.longitude = strtod(&buffer[index[3] + 1], NULL);
    gpgga->gps.EW = (GPS_EW) buffer[index[4] + 1];
    gpgga->quality = (GPS_QUALITY_INDICATOR) buffer[index[5] + 1];
    gpgga->numSatView = (buffer[index[6] + 1] - 48) * 10 + (buffer[index[6] + 2] - 48);
    gpgga->hdop = strtod(&buffer[index[7] + 1], NULL);
    gpgga->altitudeMSL = strtod(&buffer[index[8] + 1], NULL);
    gpgga->heightAboveWGS = strtod(&buffer[index[10] + 1], NULL);
    gpgga->timeSinceLastDGPS = (buffer[index[12] + 1] - 48) * 10 + (buffer[index[12] + 2] - 48);
    gpgga->DGPSRefID[0] = buffer[index[13] + 1];
    gpgga->DGPSRefID[1] = buffer[index[13] + 2];
    gpgga->DGPSRefID[2] = buffer[index[13] + 3];
    gpgga->DGPSRefID[3] = buffer[index[13] + 4];
    return 0;
}

/**
 * @brief
 * @param gpggl
 * @param buffer
 * @param size
 * @return
 */
uint8_t nmea_decode_gpggl(gpggl_t *gpggl, char buffer[], uint8_t size) {
    uint8_t index[7] = {0};
    split_index(buffer, size, index, 7);
    gpggl->gps.latitude = strtod(&buffer[index[0] + 1], NULL);
    gpggl->gps.NS = (GPS_NS) buffer[index[1] + 1];
    gpggl->gps.longitude = strtod(&buffer[index[2] + 1], NULL);
    gpggl->gps.EW = (GPS_EW) buffer[index[3] + 1];
    gpggl->utcTime.hh = (buffer[index[4] + 1] - 48) * 10 + (buffer[index[4] + 2] - 48);
    gpggl->utcTime.mm = (buffer[index[4] + 3] - 48) * 10 + (buffer[index[4] + 4] - 48);
    gpggl->utcTime.ss = (buffer[index[4] + 5] - 48) * 10 + (buffer[index[4] + 6] - 48);
    gpggl->gpsDataStatus = (GPS_DATA_STATUS) buffer[index[5] + 1];
    return 0;
}

/**
 * @brief
 * @param gpvtg
 * @param buffer
 * @param size
 * @return
 */
uint8_t nmea_decode_gpvtg(gpvtg_t *gpvtg, char buffer[], uint8_t size) {
    uint8_t index[7] = {0};
    split_index(buffer, size, index, 7);
    gpvtg->trackDegreeTrue = strtod(&buffer[index[0] + 1], NULL);
    gpvtg->trackDegreeMagnetic = strtod(&buffer[index[2] + 1], NULL);
    gpvtg->gndSpeedN = strtod(&buffer[index[4] + 1], NULL);
    gpvtg->gndSpeedK = strtod(&buffer[index[6] + 1], NULL);
    return 0;
}

