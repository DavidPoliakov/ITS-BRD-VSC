/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "init.h"
#include "lcd.h"
#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"
#include "phase.h"

//eingang GPIO_IN0/PF_0 GPIO_IN1/PF_1
#define MODER_MASK 67
#define RESET_SHIFT 6
#define PHASE_ERROR 2

static Phase old;

void init(){
   initITSboard(); // Initialisierung des ITS Boards
   //TO DO: weitere später benötigte inits
   int io_in = GPIOF->IDR & MODER_MASK;
   int time = HAL_GetTick();
   Phase old = get_Phase(io_in, time);
}

int main(void) {
   init();
   while (1) {
      int io_in = GPIOF->IDR & MODER_MASK;
      uint32_t time = HAL_GetTick();
      if(io_in >> RESET_SHIFT){
         reset_counter();
         init();
      }
      Phase now = get_Phase(io_in, time);
      int raw_p_shift = phase_shift(now, old);
      if(raw_p_shift){
         update_counter(raw_p_shift);
         update_output();
      } else {
         now.val = PHASE_ERROR;
      }
      old = now;
   }
}

// EOF
