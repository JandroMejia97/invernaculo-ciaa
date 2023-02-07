#include <string.h> 
#include<stdio.h>
#include <math.h>
#include "sapi.h"
#include "soil-sensor.h"
#include "utils.h"
#include "main.h"

void sendToUart(char variableType, int data);

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar UART_GPIO a 115200 baudios */
   uartConfig(UART_GPIO, UART_BAUD_RATE);
   uartConfig(UART_USB, UART_BAUD_RATE);

   /* Inicializar AnalogIO */
   /* Posibles configuraciones:
    *    ADC_ENABLE,  ADC_DISABLE,
    *    ADC_ENABLE,  ADC_DISABLE,
    */
   adcConfig(ADC_ENABLE); /* ADC */
   dht11Init(DHT11_SENSOR_PIN); // Inicializo el sensor DHT11

   /* ConfiguraciÃ³n de estado inicial del Led */
   bool_t ledState1 = OFF;

   /* Contador */
   uint32_t i = 0;

   /* Buffer */
   static char uartBuff[DATA_BUFFER_SIZE];

   /* Variable para almacenar el valor leido del ADC CH1 */
   uint16_t muestraSOIL = 0;
   uint16_t muestraLDR = 0;
   float muestraDHT_TEMP = 0;
   float muestraDHT_HUM = 0;
   uint16_t temp = 0;
   uint16_t hum = 0;
   uint8_t tick = 0;
   

   /* Variables de delays no bloqueantes */
   delay_t delay1;

   /* Inicializar Retardo no bloqueante con tiempo en ms por 5m */
   delayConfig(&delay1, TIME_INTERVAL_IN_MILLIS); // For testing purposes, use 1 second


   /* ------------- REPETIR POR SIEMPRE ------------- 
      El código funciona de la siguiente manera, realizara una lectura cada determinado tiempo (para uso real serían los minutos especificados en el informe)
      Para nuestras pruebas es 1 segundo. 
      Caracteres para identificar datos: 0 - Temperatura del Aire / 1 - Humedad del Aire / 2 - Humedad de la Tierra / 3 - Cantidad de Luz
      Se lee el sensor, se envía a la UART un caracter para indicar cual será el dato a enviar. Por ejemplo, si la uart envía un 0, estará esperando que el dato que
      lea a continuación sea de temperatura. Proximamente se envia a la UART su correspondiente dato y se pasa al próximo sensor.
   */
   while(1) {
      char temp[DATA_BUFFER_SIZE];

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if (delayRead(&delay1 )){
         if (tick == TICKS_TO_CLEAR) {
            tick = 0;
         } else {
            tick++;
         }

         // Seccion para el sensor DHT11
         if (tick % TICKS_TO_SENSE_TEMP == 0) {
            dht11Read(&muestraDHT_HUM, &muestraDHT_TEMP);
            // Envio el 0 para avisarle a la uart que el dato proximo corresponde a la temperatura
            int temp = round(muestraDHT_TEMP);
            sendToUart('0', temp);
            // Ahora envio un 1 correspondiente a la humedad del aire
            temp = round(muestraDHT_HUM);
            sendToUart('1', temp);
         }

         // Seccion para el sensor de luz
         if (tick % TICKS_TO_SENSE_LIGHT == 0) {
            muestraLDR = ONE_HUNDRED_PERCENT - (adcRead(LIGHT_SENSOR_PIN) * ONE_HUNDRED_PERCENT / ADC_TOP_VALUE);
            // Envio un 2 para avisar que voy a enviar informacion acerca de la cantidad de luz
            sendToUart('2', muestraLDR);
         }

         // Seccion para el sensor de humedad de la tierra
         if (tick % TICKS_TO_SENSE_SOIL == 0){
            muestraSOIL = (ADC_TOP_VALUE - adcRead(SOIL_SENSOR_PIN)) * ONE_HUNDRED_PERCENT / SOIL_ADC_UPPER_LIMIT;
            // Envio un 3 correspondiente a la humedad de la tierra
            sendToUart('3', muestraSOIL);
         }
      }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

void sendToUart(char variableType, int data) {
   char dataString[DATA_BUFFER_SIZE];
   char uartBuff[DATA_BUFFER_SIZE];

   dataString[0] = variableType;
   dataString[1] = '\0';

   itoa(data, uartBuff, 10);

   strcat(dataString, uartBuff);

   /* Enviar muestra y Enter */
   strcat(dataString, "\r\n");
   uartWriteString(UART_GPIO, dataString);
   uartWriteString(UART_USB, dataString);
}