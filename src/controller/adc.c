/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho and Leon, 2019.
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

static void adc_trigger (void);

void adc_init (void)
{
  uint16_t ui16_counter;
  uint16_t ui16_i;

  //init GPIO for the used ADC pins
  GPIO_Init(GPIOB, (GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_3), GPIO_MODE_IN_FL_NO_IT);

  //init ADC1 peripheral
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
            ADC1_CHANNEL_7,
			ADC1_PRESSEL_FCPU_D3,
            ADC1_EXTTRIG_TIM,
            DISABLE,
            ADC1_ALIGN_LEFT,
            (ADC1_SCHMITTTRIG_CHANNEL3 | ADC1_SCHMITTTRIG_CHANNEL5 | ADC1_SCHMITTTRIG_CHANNEL6 | ADC1_SCHMITTTRIG_CHANNEL7),
            DISABLE);

  ADC1_ScanModeCmd(ENABLE);
  ADC1_Cmd(ENABLE);

  
  #define ADC_CALIBRATION_TIME                    300 // 300 -> around 3.0 seconds
  #define ADC_TORQUE_SENSOR_CALIBRATION_OFFSET    6
  
  for (ui16_i = 0; ui16_i < ADC_CALIBRATION_TIME; ++ui16_i)
  {
    // set counter for delay
    ui16_counter = TIM3_GetCounter() + 10; // delay ~10 ms
    
    // wait for delay
    while (TIM3_GetCounter() < ui16_counter);
    
    // trigger ADC conversion on all channels (scan conversion, buffered)
    adc_trigger();
    
    // wait for end of conversion
    while (!ADC1_GetFlagStatus(ADC1_FLAG_EOC));
    
    // read ADC torque sensor value
    uint16_t ui16_temp = UI16_ADC_10_BIT_TORQUE_SENSOR;
    
    // filter the ADC torque sensor value and set to offset variable
    ui16_adc_pedal_torque_offset = filter(ui16_temp, ui16_adc_pedal_torque_offset, 25);
  }
  
  // add calibration offset as the torque sensor offset can be higher or lower depending on how the pedals are oriented
  ui16_adc_pedal_torque_offset += ADC_TORQUE_SENSOR_CALIBRATION_OFFSET;
}


static void adc_trigger (void)
{
  // trigger ADC conversion on all channels (scan conversion, buffered)
  ADC1->CSR &= 0x07; // clear EOC flag first (select channel 7)
  ADC1->CR1 |= ADC1_CR1_ADON; // Start ADC1 conversion
}

uint16_t ui16_adc_read_battery_voltage_10b (void)
{
  uint16_t temph;
  uint8_t templ;

  templ = *(uint8_t*)(0x53ED);
  temph = *(uint8_t*)(0x53EC);

  return ((uint16_t) temph) << 2 | ((uint16_t) templ);
}


