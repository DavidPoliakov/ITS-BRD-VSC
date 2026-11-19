#ifndef MATHE_H
#define MATHE_H

#include <stdint.h>
#include "phase.h"

<<<<<<< HEAD
typedef struct {
    int32_t  zaehler;   
    uint32_t zeit;      
} Phasenzaehler;

double berechneWinkel(Phasenzaehler p);

double berechneGeschwindigkeit(Phasenzaehler alt, Phasenzaehler neu); // alt ist zeitlich früher als neu
=======
double get_angle(void);

double berechneGeschwindigkeit(Phase now); // alt ist zeitlich früher als neu
>>>>>>> a1f0dc4762ea1eb5241cdb0e87c6bec2c6013419

#endif 