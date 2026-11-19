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
#include "mathe.h"
#include "timer.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "output.h"

//eingang GPraw_moder0/PF_0 GPraw_moder1/PF_1
#define MODER_MASK_6 64
#define MODER_MASK_PH 3
#define FLIP_MASK 0xFF

#define RESET_SHIFT 6
#define PHASE_ERROR 4
#define HALF_HZ 1

static Phase old;

//init ausgelagert um das ganze System bei reset neuzustarten.
void init(){
   reset_counter(); // counter resetten
   uint8_t raw_moder = GPIOF->IDR; //einlesen neuer Phase um von Fehlerzustand wegzukommen
   initTimer(); //Zusatz hier: TImer wird neu initialisiert
   TIM2->PSC = HALF_HZ;
   uint32_t time = TIM2->CNT;
   old = get_phase(((raw_moder ^ FLIP_MASK) & MODER_MASK_PH), time);
}


int main(void) {
   initITSboard();
   init();
   while (1) {
      //relevante Daten einlesen: GPIOF register + Zeit
      uint8_t raw_moder = GPIOF->IDR;
      uint32_t time = TIM2->CNT;
      //Phase ermitteln
      uint8_t flip_moder = raw_moder ^ FLIP_MASK;
      Phase now = get_phase((flip_moder & MODER_MASK_PH), time);
      //phasenwechsel ermitteln
      int raw_phase_shift = phase_switch(now, old);
      if(!raw_phase_shift){
         //bei Fehler:
         now.val = PHASE_ERROR;
      } else {
         //Counter updaten
         int counter = update_counter(raw_phase_shift);
         //ausgabe updaten
         update_output(counter);
      }
      //aktuelle Phase wird zur vergangenen für nächste iteration des Loops
      old = now;
      //Verarbeitung mit S6 abfragen
      if((flip_moder & MODER_MASK_6) >> RESET_SHIFT){
         init();
      }
   }
}

// EOF
