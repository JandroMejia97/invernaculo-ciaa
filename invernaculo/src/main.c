#include "sapi.h"
#include "soil-sensor.h"
#include "utils.h"

int main() {
   boardConfig();

   // UART for debug messages
   uartConfig(UART_USB, 115200);

   // Initialize the capacitive sensor
   capacitiveSensorInit();

   // Buffer for the capacitive sensor value
   static char buffer[10];

   // Delay for the main loop in milliseconds
   delay_t delay;
   delayConfig(&delay, 1000);

   while (1) {
      // Read the capacitive sensor value
      capacitiveSensorRead();

      // Convert the capacitive sensor value to string
      itoa(getCapacitiveSensorValue(), buffer, 10);

      // Print the capacitive sensor value
      uartWriteString(UART_USB, "Capacitive sensor value: ");
      uartWriteString(UART_USB, buffer);
      uartWriteString(UART_USB, "\r\n");

      // Wait for the delay
      if (delayRead(&delay)) {
         delayWrite(&delay, 1000);
      }
   }
   return 0;
}