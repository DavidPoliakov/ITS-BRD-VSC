/**
 ******************************************************************************
 * @file    phase.c
 * @author  milan Lingner
 * @brief   definiertPhase struct und deklariert die zugehrigen Funktionen
 ******************************************************************************
 */

typedef struct {
    int val;
    int time;
} Phase;

/************************************************************************* 
* berechnet aus den IOs die aktuelle Phase und gibt diese als struct zurück
* @param io1 IO1 als int
* @param 1o2 IO2 als int
* @return ein Phasenstruct mit der aktuellen Phase 
**************************************************************************/
 Phase getPhase(int io1, int io2, int time);

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
 void update_counter(int count);

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