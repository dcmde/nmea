#include <string.h>
#include <stdio.h>
#include "nmea.h"

volatile static uint8_t nmea_mutex = 1; // mutex is free by default.
volatile static char nmea_buffer_in_array[90] = {0};
volatile static char nmea_buffer_array[90] = {0};
volatile static int8_t nmea_buffer_counter = -1, nmea_buffer_size = 0, nmea_buffer_ready = 0;

void nmea_handle_msg(char in) {
    // Main state machine to handle incoming char.
    switch (in) {
        case '$': // Starting char.
            nmea_buffer_counter = 0; // Index counter for the buffer at 0.
            break;
        case '\n': // Ending char for the message.
            if (nmea_buffer_lock()) {   // Try to lock the memory
                nmea_buffer_ready = 1; // Memory is not available so this flag is set.
            } else { // The memory is not being used so the buffer is copied.
                for (uint8_t i = 0; i < nmea_buffer_counter; ++i) {
                    nmea_buffer_array[i] = nmea_buffer_in_array[i];
                }
                nmea_buffer_size = nmea_buffer_counter; // Store the size of the buffer.
                nmea_buffer_free(); // Free the mutex for the memory.
            }
            nmea_buffer_counter = -1; // The message was completely received from start to end so we wait for a new valid start.
            break;
        default: // Handle incoming char and copy them into the buffer.
            if (nmea_buffer_counter == -1) { // If no valid start was received return.
                return;
            } else { // A valid start was received so a message is being received.
                nmea_buffer_in_array[nmea_buffer_counter++] = in;
            }
            break;
    }
    if (nmea_buffer_ready) {    // If the buffer so not copied before due to mutex it can be copied again here.
        if (!nmea_buffer_lock()) {
            for (uint8_t i = 0; i < nmea_buffer_counter; ++i) {
                nmea_buffer_array[i] = nmea_buffer_in_array[i];
            }
            nmea_buffer_size = nmea_buffer_counter;
            nmea_buffer_ready = 0; // Set the flag to 0 so not to copy all the time.
            nmea_buffer_free();
        }
    }
}

/**
 * @brief Copy the array containing the full message into another array. The minimal buffer size is being used to copy.
 * @param buffer Input buffer.
 * @param size Size of the input buffer.
 * @return The number of byte written in the buffer.
 */
uint8_t nmea_get_buffer(char *buffer, uint8_t size) {
    uint8_t min_size = 0;
    if (!nmea_buffer_lock()) { // If the mutex is free.
        min_size = nmea_buffer_size < size ? nmea_buffer_size : size; // Get the size of the smallest buffer.
        for (uint8_t i = 0; i < min_size; ++i) { // Copy the buffer.
            nmea_buffer_array[i] = nmea_buffer_in_array[i];
        }
        nmea_buffer_free(); // Free the mutex.
    }
    return min_size;
}

/**
 * @brief Lock a mutex to access the buffer containing the nmea message.
 * @return 0 is success, 1 if failed.
 */
uint8_t nmea_buffer_lock() {
    if (nmea_mutex) {
        nmea_mutex = 0;
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Free a mutex to access the buffer containing the nmea message.
 * @return 0 if success, 1 if failed.
 */
uint8_t nmea_buffer_free() {
    if (nmea_mutex) {
        return 1;
    } else {
        nmea_mutex = 1;
        return 0;
    }
}

/**
 * @brief Allows to get the index of the ',' separator in the buffer.
 * @param buffer
 * @param msgSize
 * @param index
 * @param indexSize
 */
void splitIndex(const char buffer[], uint8_t msgSize, uint8_t index[], uint8_t indexSize) {
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

uint8_t nmea_decode_gpgga(gpgga_t *gpgga, char msg[], uint8_t msgSize) {

    return 0;
}

