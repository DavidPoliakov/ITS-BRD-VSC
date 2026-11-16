#ifndef MATHE_H
#define MATHE_H

#include <stdint.h>

typedef struct {
    int32_t  zaehler;   
    uint32_t zeit;      
} Phase;

double berechneWinkel(Phase p);

double berechneGeschwindigkeit(Phase alt, Phase neu); // alt ist zeitlich früher als neu

#endif 