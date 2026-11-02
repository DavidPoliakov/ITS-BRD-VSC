/**
 * @file exception.c
 * @author Milan Lingner, HAW Hamburg
 * @date Oct 2016
 *
 * @brief This module implements basic arithmetic functions with a stack.
 */

#include "terminal.h"
#include "stack.h"
#include "exception.h"
#include "functions.h"
#include "stdio.h"

#define MAX_SIZE 32

void print_except(int err, Terminal *term){
    char chr[MAX_SIZE];
    switch (err){
        case 1:
            sprintf(chr, "UNEXPECTED_TOKEN\n Press 'C'");
            break;
        case -1:
            sprintf(chr, "STACK_OVERFLOW\n Press 'C'");
            break;
        case -2:
            sprintf(chr, "STACK_UNDERFLOW\n Press 'C'");
            break;
        case -3:
            sprintf(chr, "INT_OVERFLOW\n Press 'C'");
            break;
        case -4:
            sprintf(chr, "INT_UNDERFLOW\n Press 'C'");
            break;
        case -5:
            sprintf(chr, "DIV_BY_ZERO\n Press 'C'");
            break;
        default:
            sprintf(chr, "UNKNOWN_ERROR\n Press 'C'");
            break;
    }
    printTerm(chr, term);
}

// EOF