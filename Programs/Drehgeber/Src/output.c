/****************************************************************************************
* output.c
* author: milan Lingner
* bündelt alle Funktionen des Outputs um das nicht so nervig in der main zu haben
*
**************************************************************************************** */
#include "phase.h"
#include "output.h"
#include "mathe.h"
#include "lcd.h"
#include <stdio.h>
#include "stm32f429xx.h"
#include <stm32f4xx_hal.h>

#define GPIOD_MASK 0x00FF
#define GPIOD_RES_MASK 0xFF00
#define BUFFER 12
#define OFFSET_R 22

static char speed[BUFFER];
static char angle[BUFFER];
static int angle_len;
static int speed_len;
static int char_to_place;

void init_output(){
    lcdGotoXY(2, 2);
    lcdPrintS("Winkel:                             grad ");
    lcdGotoXY(2, 4);
    lcdPrintS("Winkelgeschwindigkeit:              grad/ms");
}

void update_output(int current_count, Phase now){
   update_led(current_count);
   update_val( berechneGeschwindigkeit(now), get_angle());
}

void update_led(int current_count){
    GPIOD->BSRR = GPIOD_RES_MASK;
    GPIOD->BSRR = (current_count & GPIOD_MASK);
}

void update_val(double geschwindigkeit, double winkel){
    angle_len = snprintf(angle, BUFFER, "%09.3f", winkel);
    speed_len = snprintf(speed, BUFFER, "%09.3f", geschwindigkeit);
    char_to_place = angle_len + speed_len - 1;
}

void inc_update_lcd(){
    if(char_to_place >= 0){
        if(char_to_place < speed_len){
            lcdGotoXY(OFFSET_R + char_to_place, 4);
            lcdPrintC(speed[char_to_place]);
        } else {
            lcdGotoXY(OFFSET_R + char_to_place - speed_len, 2);
            lcdPrintC(angle[char_to_place - speed_len]);
        }
        char_to_place = char_to_place - 1;
    }
}