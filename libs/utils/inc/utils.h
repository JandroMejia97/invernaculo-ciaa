/* Utils
 * Copyright YYYY Author Compelte Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link 
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include "sapi_datatypes.h"

char* itoa(int value, char* result, int base);
uint8_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint8_t out_min, uint8_t out_max);
#endif /* _UTILS_H_ */