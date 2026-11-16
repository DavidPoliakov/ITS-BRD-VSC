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
#define GPIOD_MASK 0x00FF
#define RESET_SHIFT 6
#define PHASE_ERROR 4

static Phase old;

//init ausgelagert um das ganze System bei reset neuzustarten.
void init(){
   initITSboard(); // Initialisierung des ITS Boards
   //TO DO: weitere später benötigte inits
   reset_counter();
   int io_in = GPIOF->IDR & MODER_MASK;
   uint32_t time = HAL_GetTick();
   Phase old = get_Phase(io_in, time);
}
void update_output(int current_count){
   GPIOD->BSRR = (current_count & GPIOD_MASK);
}

int main(void) {
   init();
   while (1) {
      //relevante Daten einlesen: GPIOF register + Zeit
      int io_in = GPIOF->IDR & MODER_MASK;
      uint32_t time = HAL_GetTick();
      //Phase ermitteln
      Phase now = get_Phase(io_in, time);
      //phasenwechsel ermitteln
      int raw_phase_shift = phase_shift(now, old);
      if(!raw_phase_shift){
         //bei Fehler:
         now.val = PHASE_ERROR;
      } else {
         //Counter updaten
         int current_count = update_counter(raw_phase_shift);
         //ausgabe updaten
         update_output(current_count);
      }
      //aktuelle Phase wird zur vergangenen für nächste iteration des Loops
      old = now;
      //Verarbeitung mit S6 abfragen
      if(io_in >> RESET_SHIFT){
         init();
      }
   }
}

// EOF
