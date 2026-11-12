/**
 ******************************************************************************
 * @file    phase.h
 * @author  milan Lingner
 * @brief   definiert Phase struct und deklariert die zugehrigen Funktionen
 ******************************************************************************
 */
#ifndef PHASE_H
#define PHASE_H

#include <stdint.h>

typedef struct {
    int val;
    int time;
} Phase;

/************************************************************************* 
* berechnet aus den IOs die aktuelle Phase und gibt diese als struct zurück
* @param io_in der aktuelle Wert des io_registers
* @return ein Phasenstruct mit der aktuellen Phase 
**************************************************************************/
 Phase get_phase(int io_in, uint32_t time);

/********************************************************************
* berechnet den Wert des Phasenwechsels
* @param now: aktuelle Phase
* @param old: die letzte Phase
* @return -1/-3 für reguläre Drehung, -2 für keinen Phasenwechsel und 0 
* für illegale Phasenwechsel
********************************************************************** */
int phase_switch(Phase now, Phase old);

/***************************************************************************
* updatet den Counter und die Richtung (dir)
* @param count der aktuelle Stand des Phasenwechsels
*******************************************************************/
int update_counter(int count);

/******************************************************************
* gibt den aktuellen Wert des Counters
* @return der aktuelle Wert des Counters
***************************************************************/
int get_counter(void);

/******************************************************************
* gibt den aktuellen Wert der Richtung
* @return der aktuelle Wert der Richtung
***************************************************************/
int get_dir(void);

/*************************************************************************
* resettet den Counter und direction zu 0
*******************************************************************/
void reset_counter(void);

#endif