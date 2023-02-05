#include "sapi.h"
#include "dht11.h"
#include "soil-sensor.h"
#include "utils.h"

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar UART_USB a 115200 baudios */
   uartConfig( UART_USB, 115200 );

   /* Inicializar AnalogIO */
   /* Posibles configuraciones:
    *    ADC_ENABLE,  ADC_DISABLE,
    *    ADC_ENABLE,  ADC_DISABLE,
    */
   adcConfig( ADC_ENABLE ); /* ADC */
   dacConfig( DAC_ENABLE ); /* DAC */

   /* ConfiguraciÃ³n de estado inicial del Led */
   bool_t ledState1 = OFF;

   /* Contador */
   uint32_t i = 0;

   /* Buffer */
   static char uartBuff[10];

   /* Variable para almacenar el valor leido del ADC CH1 */
   uint16_t muestraSOIL = 0;
   uint16_t muestraLDR = 0;
   uint16_t muestraDHT_TEMP = 0;
   uint16_t muestraDHT_HUM = 0;

   /* Variables de delays no bloqueantes */
   delay_t delay1;
   delay_t delay2;
   delay_t lecturas;

   /* Inicializar Retardo no bloqueante con tiempo en ms */
   delayConfig( &delay1, 1000 );
   delayConfig( &delay2, 200 );


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay1 ) ){
         // Sección para el sensor de humedad de la tierra
         /* Leo la Entrada Analogica AI0 - ADC0 CH1 */
         muestraSOIL = (1023 - adcRead ( CH3 )) * 100 / 613;

         /* EnvÃ­o la primer parte del mnesaje a la Uart */
         uartWriteString( UART_USB, "Humedad de la tierra: " );

         /* ConversiÃ³n de muestra entera a ascii con base decimal */
         itoa( muestraSOIL, uartBuff, 10 ); /* 10 significa decimal */

         /* Enviar muestra y Enter */
         uartWriteString( UART_USB, uartBuff );
         uartWriteString( UART_USB, "\% \r\n" );

         /* Escribo la muestra en la Salida AnalogicaAO - DAC */
         dacWrite( DAC, muestraSOIL );

         // Sección para el sensor de luz
         delayRead( &delay1 );
         muestraLDR = 100 - (adcRead( CH1 ) * 100 / 1023);
         uartWriteString( UART_USB, "Cantidad de luz: " );
         itoa( muestraLDR, uartBuff, 10 );
         uartWriteString( UART_USB, uartBuff );
         uartWriteString( UART_USB, "\% \r\n" );
         dacWrite( DAC, muestraLDR );

         // Sección para el sensor DHT11
         delayRead( &delay1 );
         uartWriteString( UART_USB, "Temperatura: " );
         dht11CustomRead(&muestraDHT_TEMP, &muestraDHT_HUM);
         itoa( muestraDHT_TEMP, uartBuff, 10);
         uartWriteString( UART_USB, uartBuff );
         uartWriteString( UART_USB, "° \r\n" );
         dacWrite( DAC, muestraDHT_TEMP );

      }

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay2 ) ){
         ledState1 = !ledState1;
         gpioWrite( LED1, ledState1 );

         /* Si pasaron 20 delays le aumento el tiempo */
         i++;
         if( i == 20 )
            delayWrite( &delay2, 1000 );
      }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}