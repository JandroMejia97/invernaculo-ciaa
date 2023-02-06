#include <string.h> 
#include<stdio.h>
#include <math.h>
#include "sapi.h"
#include "soil-sensor.h"
#include "utils.h"

void sendToUart(char variableType, int data);

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar UART_GPIO a 115200 baudios */
   uartConfig(UART_GPIO, 115200);
   uartConfig(UART_USB, 115200);

   /* Inicializar AnalogIO */
   /* Posibles configuraciones:
    *    ADC_ENABLE,  ADC_DISABLE,
    *    ADC_ENABLE,  ADC_DISABLE,
    */
   adcConfig(ADC_ENABLE); /* ADC */
   dht11Init(GPIO0); // Inicializo el sensor DHT11

   /* ConfiguraciÃ³n de estado inicial del Led */
   bool_t ledState1 = OFF;

   /* Contador */
   uint32_t i = 0;

   /* Buffer */
   static char uartBuff[10];

   /* Variable para almacenar el valor leido del ADC CH1 */
   uint16_t muestraSOIL = 0;
   uint16_t muestraLDR = 0;
   float muestraDHT_TEMP = 0;
   float muestraDHT_HUM = 0;
   uint16_t temp = 0;
   uint16_t hum = 0;
   uint16_t tick = 1;
   

   /* Variables de delays no bloqueantes */
   delay_t delay1;

   /* Inicializar Retardo no bloqueante con tiempo en ms */
   delayConfig(&delay1, 30000); // 5 Minutos


   /* ------------- REPETIR POR SIEMPRE ------------- 
      El código funciona de la siguiente manera, realizara una lectura cada determinado tiempo (para uso real serían los minutos especificados en el informe)
      Para nuestras pruebas es 1 segundo. 
      Caracteres para identificar datos: 0 - Temperatura del Aire / 1 - Humedad del Aire / 2 - Humedad de la Tierra / 3 - Cantidad de Luz
      Se lee el sensor, se envía a la UART un caracter para indicar cual será el dato a enviar. Por ejemplo, si la uart envía un 0, estará esperando que el dato que
      lea a continuación sea de temperatura. Proximamente se envia a la UART su correspondiente dato y se pasa al próximo sensor.
   */
   while(1) {
      char temp[10];

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if (delayRead(&delay1 ) ){
         // Seccion para el sensor DHT11
         dht11Read(&muestraDHT_HUM, &muestraDHT_TEMP);
         // Envio el 0 para avisarle a la uart que el dato proximo corresponde a la temperatura
         int temp = round(muestraDHT_TEMP);
         sendToUart('0', temp);
         // Ahora envio un 1 correspondiente a la humedad del aire
         temp = round(muestraDHT_HUM);
         sendToUart('1', temp);

         // Seccion para el sensor de luz
         if (tick % 3 == 0){
            muestraLDR = 100 - (adcRead(CH1) * 100 / 1023);
            // Envio un 3 para avisar que voy a enviar informacion acerca de la cantidad de luz
            sendToUart('2', muestraLDR);
         }

         // Seccion para el sensor de humedad de la tierra
         if (tick % 6 == 0){
            muestraSOIL = (1023 - adcRead(CH3)) * 100 / 613;
            // Envio un 3 correspondiente a la humedad de la tierra
            sendToUart('3', muestraSOIL);
         }

         if (tick == 600) {
            tick = 0;
         } else {
            tick++;
         }
      }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

void sendToUart(char variableType, int data) {
   char dataString[10];
   char uartBuff[10];

   dataString[0] = variableType;
   dataString[1] = '\0';

   itoa(data, uartBuff, 10);

   strcat(dataString, uartBuff);

   /* Enviar muestra y Enter */
   strcat(dataString, "\r\n");
   uartWriteString(UART_GPIO, dataString);
   uartWriteString(UART_USB, dataString);
}