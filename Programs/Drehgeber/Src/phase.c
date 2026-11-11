/**
 ******************************************************************************
 * @file    phase.c
 * @author  milan Lingner
 * @brief   definiert die zur Phase struct dazugehörigen Funktionen
 ******************************************************************************
 */
 #include "phase.h"
 #define ZUSTANDLÄNGE 5
 #define MASK 0x0003 
 #define TAB 0x9C //= 1001 1100 kann per bit-shift operationen den Phasen einen verständlichen Wert zuordnen
 #define FOR (-1)
 #define BACK (-3)
 #define EQU (-2)
 #define ERROR (0)
 #define STANDARD 2 //standarisiert die Zustände auf: For -> 1, back -> -1, equ -> -2. macht die abfrage nach gültigem Zustand einfacher.
static int phase_switch_tab[ZUSTANDLÄNGE][ZUSTANDLÄNGE] =   {   {EQU, FOR, ERROR, BACK, ERROR},
                                                                {BACK, EQU, FOR, ERROR, ERROR},
                                                                {ERROR, BACK, EQU, FOR, ERROR},
                                                                {FOR, ERROR, BACK, EQU, ERROR},
                                                                {ERROR, ERROR, ERROR, ERROR, ERROR},
                                                            };
static int counter = 0;
static int dir = 0;

Phase get_phase(int io_in, uint32_t time){
    //0 0 = 0 -> 0
    //1 0 = 2 -> 1
    //1 1 = 3 -> 2 
    //0 1 = 1 -> 3

    int phase_value = ((TAB >> (io_in * 2)) & MASK);
    Phase now = {phase_value, time};
    return now;
}  

int phase_switch(Phase now, Phase old){
    return phase_switch_tab[old.val][now.val];
}

void update_counter(int count){
    count = count + STANDARD;
    counter = counter + count;
    dir = count;
}

int get_counter(void){
    return counter;
}

int get_dir(void){
    return dir;
}

void reset_counter(){
    counter = 0;
    dir = 0;
}