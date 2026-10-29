/**
 * @file exception.c
 * @author Milan Lingner, HAW Hamburg
 * @date Oct 2016
 *
 * @brief This module implements basic arithmetic functions with a stack.
 */

#include "exception.h"
#include "stdio.h"
#include "lcd.h"

#define MAX_SIZE 17

void print_except(int err, Terminal term){
    char chr[MAX_SIZE];
    switch (err){
        case 1:
            sprintf(chr, "UNEXPECTED_TOKEN");
            break;
        case -1:
            sprintf(chr, "STACK_OVERFLOW");
            break;
        case -2:
            sprintf(chr, "STACK_UNDERFLOW");
            break;
        case -3:
            sprintf(chr, "INT_OVERFLOW");
            break;
        case -4:
            sprintf(chr, "INT_UNDERFLOW");
            break;
        case -5:
            sprintf(chr, "DIV_BY_ZERO");
            break;
        default:
            sprintf(chr, "UNKNOWN_ERROR");
            break;
    }
    printTerm(chr, term);
}

// EOF