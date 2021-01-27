/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, Leon, MSpider65 2020.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "stm8s.h"
#include "pins.h"
#include "stm8s_adc1.h"
#include "adc.h"
#include "ebike_app.h"
#include "motor.h"
#include "common.h"


volatile uint16_t ui16_adc_pedal_torque_offset = 100;

void adc_init (void)
{
  uint16_t ui16_counter;
  uint16_t ui16_i;

  //init GPIO for the used ADC pins
  GPIO_Init(GPIOB, (GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_3), GPIO_MODE_IN_FL_NO_IT);

  //init ADC1 peripheral
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
            ADC1_CHANNEL_7,
            ADC1_PRESSEL_FCPU_D4,
            ADC1_EXTTRIG_TIM,
            DISABLE,
            ADC1_ALIGN_LEFT,
            (ADC1_SCHMITTTRIG_CHANNEL3 | ADC1_SCHMITTTRIG_CHANNEL5 | ADC1_SCHMITTTRIG_CHANNEL6 | ADC1_SCHMITTTRIG_CHANNEL7),
            DISABLE);

  ADC1_ScanModeCmd(ENABLE);		   // enable scan mode
  ADC1_Cmd(ENABLE);
  ADC1_ClearFlag(ADC1_FLAG_EOC);
  ADC1_StartConversion();          // start ADC1 conversion

  #define ADC_DELAY_TIME     200   // 200 -> around 2.0 seconds
  for (ui16_i = 0; ui16_i < ADC_DELAY_TIME; ++ui16_i)
  {
    ui16_counter = TIM3_GetCounter() + 10; // delay ~10 ms
    
    // wait for delay
    while (TIM3_GetCounter() < ui16_counter);
  }
  ADC1_ClearFlag(ADC1_FLAG_EOC);
  ADC1_StartConversion();          // start ADC1 conversion
}

uint16_t ui16_adc_read_battery_voltage_10b (void)
{
  uint16_t temph;
  uint8_t templ;

  templ = *(uint8_t*)(0x53ED);
  temph = *(uint8_t*)(0x53EC);

  return ((uint16_t) temph) << 2 | ((uint16_t) templ);
}


