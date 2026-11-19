/****************************************************************************************
* output.h
* author: milan Lingner
* bündelt alle Funktionen des Outputs um das nicht so nervig in der main zu haben
*
**************************************************************************************** */
#ifndef OUTPUT_H
#define OUTPUT_H

#include "phase.h"

void update_output(int current_count, Phase old, Phase Now);

void update_led(int current_count);

void update_lcd(double winkel, double geschwindigkeit);

#endif