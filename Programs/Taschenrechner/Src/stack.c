#include "stack.h"
#include "exception.h"
#include "token.h"

#define STACK_SIZE 2

static int stack[STACK_SIZE];
static int sp = 0;

int stack_push(int val) {
    if (sp >= STACK_SIZE) {
        return STACK_OVERFLOW;
    }
    stack[sp++] = val; 
    return 0;
}

void stack_clear() {
    sp = 0;
}

int stack_pop(int *val) {
    if (sp <= 0) {
        return STACK_UNDERFLOW;
    }
    *val = stack[--sp] ; 
    return 0;
}

