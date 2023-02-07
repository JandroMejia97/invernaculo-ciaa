#ifndef __MAIN_H__
#define __MAIN_H__
  #define TIME_INTERVAL_IN_MINUTES  5
  #define TIME_INTERVAL_IN_SECONDS  TIME_INTERVAL_IN_MINUTES * 60
  #define TIME_INTERVAL_IN_MILLIS   TIME_INTERVAL_IN_SECONDS * 1000
  #define TICKS_TO_CLEAR            600
  #define TICKS_TO_SENSE_LIGHT      1
  #define TICKS_TO_SENSE_TEMP       2
  #define TICKS_TO_SENSE_SOIL       6


  #define ONE_HUNDRED_PERCENT       100
  #define DHT11_SENSOR_PIN          GPIO0
  #define LIGHT_SENSOR_PIN          CH1
  #define SOIL_SENSOR_PIN           CH3
  /*
   * For the measures that we did, the soil sensor was giving us values
   * between 410 and 750 for dry and wet soil respectively.
   * We are going to use this range to map the values
   */
  #define SOIL_ADC_UPPER_LIMIT      613

  #define ADC_TOP_VALUE             1023
  #define ADC_REFERENCE_VOLTAGE     5.0

  #define UART_BAUD_RATE            115200
  #define DATA_BUFFER_SIZE          10
#endif
