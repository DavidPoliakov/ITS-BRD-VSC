#include "stack.h"
#include "exception.h"

#define STACK_SIZE 10

static int stack[STACK_SIZE];
static int stp = 0;

int stack_push(int val) {
    if (stp >= STACK_SIZE) {
        return STACK_OVERFLOW;
    }
    stack[stp++] = val; 
    return 0;
}

void stack_clear() {
    stp = 0;
}

int stack_pop(int *val) {
    if (stp <= 0) {
        return STACK_UNDERFLOW;
    }
    *val = stack[--stp] ; 
    return 0;
}

