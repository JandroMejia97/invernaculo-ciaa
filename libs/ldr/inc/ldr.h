/* LDR
 * Copyright YYYY Author Compelte Name <author@mail.com>
 * All rights reserved.
 * License: license text or at least name and link 
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Creation Date: YYYY/MM/DD
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _LDR_H_

#define _LDR_H_

uint16_t getLDRValue(void);
uint8_t getMapedLDRValue(void);

void LDRInit(void);
uint16_t LDRRead(void);

#endif /* _DHT_11_H_ */