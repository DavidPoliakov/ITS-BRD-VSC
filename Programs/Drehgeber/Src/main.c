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
#define MODER_MASK_6 64 //selektiert in auf S6
#define MODER_MASK_PH 3 //selektiert in auf 0-1
#define FLIP_MASK 0xFF //flippt das Ergebnis, da Eingänge bei logisch null auf high und andersherum

#define RESET_SHIFT 6 //shift um auf Reset zu prüfen
#define PHASE_ERROR 4 //s. phase.c Zustand 4 = Error

#define TICKS_PER_US 180 //aktuelle Einstellung TIM2 = 180MHZ
#define MSEC_SCALER_10 (100 * TICKS_PER_US) //stellt auf 10 Tick pro ms
#define OUT_TIMER 3000
#define ARR_SCALER (OUT_TIMER -1)

 //update nach 300 ms

static Phase old;
static uint32_t last_out = 0;

//init ausgelagert um das ganze System bei reset neuzustarten.
void init(){
   init_output(); 
   reset_counter(); // counter resetten
   initTimer(); //Zusatz hier: Timer wird neu initialisiert
   TIM2->PSC = MSEC_SCALER_10 - 1; //Timer auf 1 tick pro 10 ms setzen
   TIM2->ARR = ARR_SCALER;
   uint8_t raw_moder = GPIOF->IDR; //einlesen neuer Phase
   uint32_t time = TIM2->CNT; //einlesen neuer Zeit
   old = get_phase(((raw_moder ^ FLIP_MASK) & MODER_MASK_PH), time);
}


int main(void) {
   initITSboard();
   GUI_init(DEFAULT_BRIGHTNESS); 
   init();
   while (1) {
      //relevante Daten einlesen: GPIOF register + Zeit
      uint8_t raw_moder = GPIOF->IDR;
      uint32_t time = TIM2->CNT;
      //Phase ermitteln
      uint8_t flip_moder = raw_moder ^ FLIP_MASK;
      Phase now = get_phase((flip_moder & MODER_MASK_PH), time);
      //phasenwechsel ermitteln
      int raw_phase_switch = phase_switch(now, old);
      if(!raw_phase_switch){
         //bei Fehler:
         now.val = PHASE_ERROR;
         
      } else {
         //Counter updaten
         int counter = update_counter(raw_phase_switch, &now);
         //ausgabe updaten
         if(TIM2->SR & TIM_SR_UIF){
            TIM2->SR = ~TIM_SR_UIF;
            update_output(counter, now);
            last_out = time;
         }
         inc_update_lcd();
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
