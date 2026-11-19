#ifndef MATHE_H
#define MATHE_H

#include <stdint.h>
#include "phase.h"

double berechneWinkel(int counter);

double berechneGeschwindigkeit(Phase alt, Phase neu); // alt ist zeitlich früher als neu

#endif 