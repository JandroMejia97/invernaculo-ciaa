/* Capacitive 
 * Copyright YYYY Author Complete Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link 
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */

#include "sapi.h"

#include "soil-sensor.h"

#ifndef CAPACITIVE_SENSOR_PIN

#warning "CAPACITIVE_SENSOR_PIN is not defined, using T_FIL1 as default value"
#define CAPACITIVE_SENSOR_PIN T_FIL1

#endif

static uint16_t capacitiveSensorValue = 0;

uint16_t getCapacitiveSensorValue(void) {
  return capacitiveSensorValue;
}

void capacitiveSensorInit(void) {
  adcConfig(ADC_ENABLE);
}

uint16_t capacitiveSensorRead(void) {
  capacitiveSensorValue = adcRead(CAPACITIVE_SENSOR_PIN);
  return capacitiveSensorValue;
}
