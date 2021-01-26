/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho and EndlessCadence and Leon, 2019.
 *
 * Released under the GPL License, Version 3
 */

#ifndef _EBIKE_APP_H_
#define _EBIKE_APP_H_

#include <stdint.h>
#include "main.h"

// cadence sensor
extern volatile uint8_t ui8_cadence_sensor_mode;
extern volatile uint16_t ui16_cadence_sensor_ticks_counter_min_speed_adjusted;

typedef struct _configuration_variables
{
  uint8_t ui8_motor_power_x10;
  uint16_t ui16_battery_low_voltage_cut_off_x10;
  uint16_t ui16_wheel_perimeter;
  uint8_t ui8_wheel_speed_max;
  uint8_t ui8_motor_type;
  uint8_t ui8_pedal_torque_per_10_bit_ADC_step_x100;
  uint8_t ui8_target_battery_max_power_div25;
  uint8_t configuration_variables;
  uint8_t ui8_optional_ADC_function;
} struct_configuration_variables;


void ebike_app_controller (void);
struct_configuration_variables* get_configuration_variables (void);

#endif /* _EBIKE_APP_H_ */
