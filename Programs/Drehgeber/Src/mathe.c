#include "mathe.h"
#include "phase.h"

#define PHASENWECHSEL_PRO_UMDREHUNG 1200.0
#define GRAD_PRO_UMDREHUNG          360.0

#ifndef TICKS_PER_MS 
#define TICKS_PER_MS 10
#endif
#define TICKS_PRO_SEKUNDE (TICKS_PER_MS * 1000.0)

double berechneWinkel(Phase p) {
    return (double)p.zaehler * GRAD_PRO_UMDREHUNG / PHASENWECHSEL_PRO_UMDREHUNG;
}

double berechneGeschwindigkeit(Phase alt, Phase neu) {
    uint32_t ticks = neu.zeit - alt.zeit;   
    if (ticks == 0U) {  //unsigned div mit 0       
        return 0.0;     
    }
    double new_angle = (double)neu.count * GRAD_PRO_UMDREHUNG / PHASENWECHSEL_PRO_UMDREHUNG;
    double winkel = new_angle - angle;
    double sec     = (double)ticks / TICKS_PRO_SEKUNDE;
    last_out = neu;
    angle = new_angle;
    return winkel / sec;
}            

double get_angle(){
    return angle;
}
