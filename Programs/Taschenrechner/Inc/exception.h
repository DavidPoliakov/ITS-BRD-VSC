/**
 * @file exception.h
 * @author Milan Lingner, HAW Hamburg
 * @date Oct 2026
 * @brief This file stores the "magic numbers" used for Exceptions in the Stack and declares a second printstream
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#define STACK_OVERFLOW (-1)        //!< Token for an int number
#define STACK_UNDERFLOW (-2)       //!< Token for + operator
#define INT_OVERFLOW (-3)          //!< Token for - operator
#define INT_UNDERFLOW (-4)
#define DIV_BY_ZERO(-5)
#define UNEXPECTED_TOKEN (1)

void print_except(int);

#endif