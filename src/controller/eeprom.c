/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, Leon, MSpider65 2020.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include "stm8s.h"
#include "stm8s_flash.h"

void EEPROM_init(void) {
  volatile uint32_t ui32_delay_counter = 0;
  
  // deinitialize EEPROM
  FLASH_DeInit();
  
  // time delay
    for (ui32_delay_counter = 0; ui32_delay_counter < 160000; ++ui32_delay_counter) {
    }
  
  // select and set programming time mode
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD); // standard programming (erase and write) time mode
  //FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_TPROG); // fast programming (write only) time mode
  
  // time delay
    for (ui32_delay_counter = 0; ui32_delay_counter < 160000; ++ui32_delay_counter) {
}
}

