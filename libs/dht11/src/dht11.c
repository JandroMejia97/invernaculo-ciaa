/* DHT11 Module
 * Copyright YYYY Author Complete Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link 
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */
#include "dht11.h"

const unsigned char *DHTxx_StatusToString(DHTxx_Status_t status) {
    switch(status) {
        case DHTxx_OK:
            return "OK";
        case DHTxx_NO_PULLUP:
            return "NO_PULLUP";
        case DHTxx_NO_ACK_0:
            return "NO_ACK_0";
        case DHTxx_NO_ACK_1:
            return "NO_ACK_1";
        case DHTxx_NO_DATA_0:
            return "NO_DATA_0";
        case DHTxx_NO_DATA_1:
            return "NO_DATA_1";
        case DHTxx_ERROR_CHECKSUM:
            return "ERROR_CHECKSUM";
        default:
            return "UNKNOWN";
    }
}

DHTxx_Status_t DHTxx_ReadData(uint16_t *temperature, uint16_t *humidity) {
    uint8_t counter = 0, loopBits = 40, i = 0;
    uint8_t buffer[5];
    uint16_t data;

    // Initialize buffer
    for (i = 0; i < sizeof(buffer); i++) {
        buffer[i] = 0;
    }
}