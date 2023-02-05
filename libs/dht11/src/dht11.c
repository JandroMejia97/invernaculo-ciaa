#include "dht11.h"

bool_t dht11CustomRead( uint16_t *phum, uint16_t *ptemp ) {
   if(TRUE == dht11_StartRead()) {
      if(TRUE == dht11_ProcessData()) {
         *phum 	= (dht11_byte[0]);
         *ptemp 	= (dht11_byte[2]);
         return TRUE;
      }
   }
   return FALSE;
}
