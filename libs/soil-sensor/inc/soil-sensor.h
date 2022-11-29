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

#ifndef _SOIL_SENSOR_H_

#define _SOIL_SENSOR_H_

uint16_t getCapacitiveSensorValue(void);
uint8_t getMapedCapacitiveSensorValue(void);

void capacitiveSensorInit(void);
uint16_t capacitiveSensorRead(void);

#endif /* _DHT_11_H_ */