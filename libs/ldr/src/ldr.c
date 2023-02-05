/* LDR 
 * Copyright YYYY Author Complete Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link 
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */

#include "sapi.h"

#include "ldr.h"

#ifndef LDR_PIN

#warning "LDR_PIN is not defined, using CH1 as default value"
#define LDR_PIN CH1

#endif

static uint16_t LDRValue = 0;

uint16_t getLDRValue(void) {
  return LDRValue;
}

uint8_t getMapedLDRValue(void) {
  return map(LDRValue, 0, 1023, 0, 100);
}

void LDRInit(void) {
  adcConfig(ADC_ENABLE);
}

uint16_t LDRRead(void) {
  LDRValue = adcRead(LDR_PIN);
  return LDRValue;
}
