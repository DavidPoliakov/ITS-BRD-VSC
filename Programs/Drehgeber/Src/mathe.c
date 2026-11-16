#include "mathe.h"

#define PHASENWECHSEL_PRO_UMDREHUNG 1200.0
#define GRAD_PRO_UMDREHUNG          360.0

#ifndef TICKS_PER_US
#define TICKS_PER_US 90
#endif
#define TICKS_PRO_SEKUNDE (TICKS_PER_US * 1000000.0)

double berechneWinkel(Phase p) {
    return (double)p.zaehler * GRAD_PRO_UMDREHUNG / PHASENWECHSEL_PRO_UMDREHUNG;
}

double berechneGeschwindigkeit(Phase alt, Phase neu) {
    uint32_t ticks = neu.zeit - alt.zeit;   
    if (ticks == 0U) {  //unsigned div mit 0       
        return 0.0;     
    }
    double winkel = berechneWinkel(neu) - berechneWinkel(alt);
    double sec     = (double)ticks / TICKS_PRO_SEKUNDE;
    return winkel / sec;
}            