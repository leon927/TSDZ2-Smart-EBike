/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, Leon, MSpider65 2020.
 *
 * Released under the GPL License, Version 3
 */

#ifndef _MAIN_H_
#define _MAIN_H_


//#define DEBUG_UART
//#define PWM_TIME_DEBUG
//#define MAIN_TIME_DEBUG
#define PWM_20K

#define FW_VERSION 6

// PWM related values
#ifdef PWM_20K
// motor 
    #define PWM_CYCLES_SECOND                                       20000U // 1 / 50us(PWM period)
    #define PWM_CYCLES_COUNTER_MAX                                  4000U  // 5 erps minimum speed -> 1/5 = 200 ms; 200 ms / 50 us = 4000 (3125 at 15.625KHz)
    // ramp up/down PWM cycles count
    #define PWM_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_DEFAULT             204    // 160 -> 160 * 64 us for every duty cycle increment at 15.625KHz
    #define PWM_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_MIN                 25     // 20 -> 20 * 64 us for every duty cycle increment at 15.625KHz
    #define PWM_DUTY_CYCLE_RAMP_DOWN_INVERSE_STEP_DEFAULT           51     // 40 -> 40 * 64 us for every duty cycle decrement at 15.625KHz
    #define PWM_DUTY_CYCLE_RAMP_DOWN_INVERSE_STEP_MIN               10     // 8 -> 8 * 64 us for every duty cycle decrement at 15.625KHz
    #define MOTOR_OVER_SPEED_ERPS                                   650    // motor max speed | 30 points for the sinewave at max speed (less than PWM_CYCLES_SECOND/30)
    #define CRUISE_DUTY_CYCLE_RAMP_UP_INVERSE_STEP                  102    // 80 at 15.625KHz
    #define WALK_ASSIST_DUTY_CYCLE_RAMP_UP_INVERSE_STEP             255    // 200 at 15.625KHz
    #define THROTTLE_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_DEFAULT        102    // 80 at 15.625KHz
    #define THROTTLE_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_MIN            51     // 40 at 15.625KHz
// cadence
    #define CADENCE_SENSOR_CALC_COUNTER_MIN                         4480  // 3500 at 15.625KHz
    #define CADENCE_TICKS_STARTUP                                   8000  // ui16_cadence_sensor_ticks value for startup. About 7-8 RPM (6250 at 15.625KHz)
    #define CADENCE_SENSOR_STANDARD_MODE_SCHMITT_TRIGGER_THRESHOLD  448   // software based Schmitt trigger to stop motor jitter when at resolution limits (350 at 15.625KHz)
    // Wheel speed sensor
    #define WHEEL_SPEED_SENSOR_TICKS_COUNTER_MAX                    173   // (135 at 15,625KHz) something like 200 m/h with a 6'' wheel
    #define WHEEL_SPEED_SENSOR_TICKS_COUNTER_MIN                    41943 // could be a bigger number but will make for a slow detection of stopped wheel speed
#else
    // motor
    #define PWM_CYCLES_SECOND                                       18000U // 1 / 55.5us(PWM period)
    #define PWM_CYCLES_COUNTER_MAX                                  3600U  // 5 erps minimum speed -> 1/5 = 200 ms; 200 ms / 55.5 us = 3600 (3125 at 15.625KHz)
    // ramp up/down PWM cycles count
#define PWM_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_DEFAULT               184     // 160 -> 160 * 64 us for every duty cycle increment
#define PWM_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_MIN                   23      // 20 -> 20 * 64 us for every duty cycle increment

#define PWM_DUTY_CYCLE_RAMP_DOWN_INVERSE_STEP_DEFAULT             46      // 40 -> 40 * 64 us for every duty cycle decrement
#define PWM_DUTY_CYCLE_RAMP_DOWN_INVERSE_STEP_MIN                 9       // 8 -> 8 * 64 us for every duty cycle decrement
    #define MOTOR_OVER_SPEED_ERPS                                   600    // motor max speed | 30 points for the sinewave at max speed (<PWM_CYCLES_SECOND/30)
    #define CRUISE_DUTY_CYCLE_RAMP_UP_INVERSE_STEP                  92     // 80
    #define WALK_ASSIST_DUTY_CYCLE_RAMP_UP_INVERSE_STEP             230    // 200
    #define THROTTLE_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_DEFAULT        92     // 80
    #define THROTTLE_DUTY_CYCLE_RAMP_UP_INVERSE_STEP_MIN            46     // 40
    // cadence
    #define CADENCE_SENSOR_CALC_COUNTER_MIN                         4032  // 3500 at 15.625KHz
    #define CADENCE_TICKS_STARTUP                                   7200  // ui16_cadence_sensor_ticks value for startup. About 7-8 RPM (6250 at 15.625KHz)
    #define CADENCE_SENSOR_STANDARD_MODE_SCHMITT_TRIGGER_THRESHOLD  403   // software based Schmitt trigger to stop motor jitter when at resolution limits (350 at 15.625KHz)
    // Wheel speed sensor
    #define WHEEL_SPEED_SENSOR_TICKS_COUNTER_MAX                    155   // (135 at 15,625KHz) something like 200 m/h with a 6'' wheel
    #define WHEEL_SPEED_SENSOR_TICKS_COUNTER_MIN                    37747 // could be a bigger number but will make for a slow detection of stopped wheel speed
#endif
#define PWM_DUTY_CYCLE_MAX                                        254
#define MIDDLE_PWM_DUTY_CYCLE_MAX                                 (PWM_DUTY_CYCLE_MAX / 2)
#define MOTOR_ERPS_FIELD_WEAKEANING_MIN                           480  // field weakening is active only above 480 ERPS
#define FIELD_WEAKEANING_ANGLE_MAX                                6    // max field weakening angle is 360/256*6 = 8.4 degrees

/*---------------------------------------------------------
  NOTE: regarding duty cycle (PWM) ramping
  
  Do not change these values if not sure of the effects!
  
  A lower value of the duty cycle inverse step will mean
  a faster acceleration. Be careful not to choose too
  low values for acceleration.
---------------------------------------------------------*/



#define MOTOR_ROTOR_OFFSET_ANGLE                                  10
#define MOTOR_ROTOR_ANGLE_90                                      (63  + MOTOR_ROTOR_OFFSET_ANGLE)
#define MOTOR_ROTOR_ANGLE_150                                     (106 + MOTOR_ROTOR_OFFSET_ANGLE)
#define MOTOR_ROTOR_ANGLE_210                                     (148 + MOTOR_ROTOR_OFFSET_ANGLE)
#define MOTOR_ROTOR_ANGLE_270                                     (191 + MOTOR_ROTOR_OFFSET_ANGLE)
#define MOTOR_ROTOR_ANGLE_330                                     (233 + MOTOR_ROTOR_OFFSET_ANGLE)
#define MOTOR_ROTOR_ANGLE_30                                      (20  + MOTOR_ROTOR_OFFSET_ANGLE)

/*---------------------------------------------------------
  NOTE: regarding motor rotor offset 
  
  The motor rotor offset should be as close to 0 as 
  possible. You can try to tune with the wheel in the air,
  full throttle and look at the batttery current. Adjust 
  for the lowest battery current possible.
---------------------------------------------------------*/

#define MOTOR_ROTOR_ERPS_START_INTERPOLATION_60_DEGREES           10

/*---------------------------------------------------------
  NOTE: regarding motor start interpolation
  
  This value is the ERPS speed after which a transition 
  happens from sinewave and no interpolation to 
  interpolation 60 degrees. Must be found experimentally 
  but a value of 25 may be good.
---------------------------------------------------------*/

#define ADC_10_BIT_BATTERY_CURRENT_MAX                            106     // 17 amps
#define ADC_10_BIT_MOTOR_PHASE_CURRENT_MAX                        177     // 28 amps

/*---------------------------------------------------------
  NOTE: regarding ADC battery current max
  
  This is the maximum current in ADC steps that the motor 
  will be able to draw from the battery. A higher value 
  will give higher torque figures but the limit of the 
  controller is 16 A and it should not be exceeded.
---------------------------------------------------------*/



// throttle ADC values
#define ADC_THROTTLE_MIN_VALUE                                    47
#define ADC_THROTTLE_MAX_VALUE                                    176

/*---------------------------------------------------------
  NOTE: regarding throttle ADC values

  Max voltage value for throttle, in ADC 8 bits step, 
  each ADC 8 bits step = (5 V / 256) = 0.0195

---------------------------------------------------------*/



// cadence sensor
#define CADENCE_SENSOR_NUMBER_MAGNETS                           20U

/*-------------------------------------------------------------------------------
  NOTE: regarding the cadence sensor
  
  CADENCE_SENSOR_NUMBER_MAGNETS = 20, this is the number of magnets used for
  the cadence sensor. Was validated on August 2018 by Casainho and jbalat
  
  Cadence is calculated by counting how much time passes between two 
  transitions. Depending on if all transitions are measured or simply 
  transitions of the same kind it is important to adjust the calculation of 
  pedal cadence.
-------------------------------------------------------------------------------*/


// default values
#define DEFAULT_VALUE_BATTERY_CURRENT_MAX                         10  // 10 amps

/*---------------------------------------------------------

  NOTE: regarding the torque sensor output values

  Torque (force) value needs to be found experimentaly.
  
  One torque sensor ADC 10 bit step is equal to 0.38 kg
  
  Force (Nm) = 1 Kg * 9.81 * 0.17 (0.17 = arm cranks size)
---------------------------------------------------------*/



// ADC battery voltage measurement
#define BATTERY_VOLTAGE_PER_10_BIT_ADC_STEP_X512                  44
#define BATTERY_VOLTAGE_PER_10_BIT_ADC_STEP_X1000                 87  // conversion value verified with a cheap power meter

/*---------------------------------------------------------
  NOTE: regarding ADC battery voltage measurement

  0.344 per ADC 8 bit step:
  
  17.9 V -->  ADC 8 bits value  = 52; 
  40 V   -->  ADC 8 bits value  = 116; 
  
  This signal is atenuated by the opamp 358.
---------------------------------------------------------*/



// ADC battery current measurement
#define BATTERY_CURRENT_PER_10_BIT_ADC_STEP_X512                  80
#define BATTERY_CURRENT_PER_10_BIT_ADC_STEP_X100                  16  // 0.16A x 10 bit ADC step

#endif // _MAIN_H_
