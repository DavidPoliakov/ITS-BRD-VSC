#ifndef MATHE_H
#define MATHE_H

#include <stdint.h>

typedef struct {
    int32_t  zaehler;   
    uint32_t zeit;      
} Phasenzaehler;

double berechneWinkel(Phasenzaehler p);

double berechneGeschwindigkeit(Phasenzaehler alt, Phasenzaehler neu); // alt ist zeitlich früher als neu

#endif 