/**
 * @file stack.h
 * @author Milan Lingner, HAW Hamburg
 * @date Oct 2026
 * @brief beschreibt den Stack
 */

#ifndef STACK_H
#define STACK_H

int stack_push(int val);
int stack_pop(int *val);
void stack_init();
int stack_peek(int tin, int *val);

#endif