/****************************************************************************************
* output.h
* author: milan Lingner
* bündelt alle Funktionen des Outputs um das nicht so nervig in der main zu haben
*
**************************************************************************************** */
#ifndef OUTPUT_H
#define OUTPUT_H

#include "phase.h"

/**************************************
* initialisiert den Output (hauptsächlich durch ausgebe der Konstanten char*)
*************************************** */
void init_output(void);

/********************************************************************
* updatet den Output (ohne direkt die Ausgabe zu verändern, bündelt den Aufruf)
* @param current_count der aktuelle Zählwert
*
********************************************************************** */
void update_output(int current_count, Phase now);

void update_led(int current_count);

void update_val(double geschwindigkeit, double winkel);

void inc_update_lcd(void);

#endif