#include "sapi.h"
int main( void )
{
   boardInit();
   while(true){
      gpioToggle(LED);
      delay(200);
   }
}