/* DHT11
 * Copyright YYYY Author Compelte Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link 
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */

/*=====[Avoid multiple inclusion - begin]====================================*/
#include "sapi_datatypes.h"

#ifndef _DHT_11_H_
#define _DHT_11_H_

#define DHTxx_PIN (GPIO01)
#define DHTxx_SENSOR_TYPE
#define DHTxx_SENSOR_TYPE_DHT11 (1)
#define DHTxx_SENSOR_TYPE_DHT22 (2)

#if DHTxx_SENSOR_TYPE_DHT11
    #define DHTxx_SENSOR_PERIOD_MS (1000)
#elif DHTxx_SENSOR_TYPE_DHT22
    #define DHTxx_SENSOR_PERIOD_MS (2000)
#else
    #error "DHTxx_SENSOR_TYPE not defined"
#endif

typedef enum {
    // OK
    DHTxx_OK,
    // No pull-up resistor
    DHTxx_NO_PULLUP, 
    // No 0 from acknowledge detected
    DHTxx_NO_ACK_0,
    // No 1 from acknowledge detected
    DHTxx_NO_ACK_1,
    // No LOW level detected
    DHTxx_NO_DATA_0,
    // No HIGH level detected
    DHTxx_NO_DATA_1,
    // Checksum error
    DHTxx_ERROR_CHECKSUM,
} DHTxx_Status_t;

typedef struct {
    DHTxx_Status_t status;
    uint8_t humidity;
    uint8_t temperature;
} DHTxx_Data_t;

const unsigned char *DHTxx_StatusToString(DHTxx_Status_t status);

DHTxx_Status_t DHTxx_ReadData(uint16_t *temperature, uint16_t *humidity);

#endif /* _DHT_11_H_ */