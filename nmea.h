#ifndef NMEA_NMEA_H
#define NMEA_NMEA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef enum {
    GPGGA,
    GPGLL,
    GPGSA,
    GPGSV,
    GPHDT,
    GPVTG,
    GPZDA
} NMEA_MSG;

typedef enum {
    GPS_N = 'N',
    GPS_S = 'S'
} GPS_NS;

typedef enum {
    GPS_E = 'E',
    GPS_W = 'W'
} GPS_EW;

typedef struct {
    NMEA_MSG nmeaMsg;
} nmea_t;

typedef struct {
    uint8_t hh;
    uint8_t mm;
    uint8_t ss;
} utc_time_t;

typedef struct {
    double latitude;
    GPS_NS NS;
    double longitude;
    GPS_NS EW;
} gps_t;

typedef enum {
    GPGGA_NONE,
    GPGGA_UTC,
    GPGGA_LAT,
    GPGGA_NOS,
    GPGGA_LON,
    GPGGA_EOW,
    GPGGA_QUALITY_ID,
    GPGGA_NUM_SAT,
    GPGGA_HOR_DOP,
    GPGGA_ALT,
    GPGGA_HEIGHT_WGS,
    GPGGA_TIME_SIMCE_LAST_UPDATE,
    GPGGA_DGPS,
    GPGGA_CHECKSUM
} GPGGA_STATE;

typedef enum {
    NO_FIX = '0',
    GPS_FIX = '1',
    DIF_GPS_FIX = '2'
} GPS_QUALITY_INDICATOR;

/**
 * @brief Struct for GPGGA messages http://aprs.gids.nl/nmea/#gga
 */
typedef struct {
    utc_time_t utcTime;
    gps_t gps;
    GPGGA_STATE gpggaState;
    uint8_t stateCpt;
    GPS_QUALITY_INDICATOR quality;
    uint8_t numSatView;
    double hdop;
    uint8_t hdop_f;
    double altitudeMSL;
    double heightAboveWGS;
    uint8_t timeSinceLastDGPS;
    char DGPSRefID[4];
    uint8_t checksum;
} gpgga_t;

void nmea_handle_msg(char in);

uint8_t nmea_get_buffer(char *buffer, uint8_t size);

uint8_t nmea_buffer_lock();

uint8_t nmea_buffer_free();

void splitIndex(const char buffer[], uint8_t msgSize, uint8_t index[], uint8_t indexSize);

uint8_t nmea_decode_gpgga(gpgga_t *gpgga, char msg[], uint8_t msgSize);

#ifdef __cplusplus
}
#endif

#endif //NMEA_NMEA_H
