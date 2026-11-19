/****************************************************************************************
* output.c
* author: milan Lingner
* bündelt alle Funktionen des Outputs um das nicht so nervig in der main zu haben
*
**************************************************************************************** */
#include "phase.h"
#include "output.h"
#include "mathe.h"
#include "gui.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include <stdio.h>
#include "stm32f429xx.h"
#include <stm32f4xx_hal.h>

#define GPIOD_MASK 0x00FF
#define GPIOD_RES_MASK 0xFF00
#define BUFFER 12
#define OFFSET_R

static char geschw[BUFFER];
static char winkel[BUFFER];



void update_output(int current_count, Phase alt, Phase neu){
   update_led(current_count);
   int32_t val = update_val(berechneWinkel(counter), berechneGeschwindigkeit(alt, neu))
   if(val )
   update_lcd();
}

void update_led(int current_count){
    GPIOD->BSRR = GPIOD_RES_MASK;
    GPIOD->BSRR = (current_count & GPIOD_MASK);
}

void update_lcd(double winkel, double geschwindigkeit){
    winkel_len = snprintf(char *restrict, __size_t, const char *restrict _Nonnull, ...)
}