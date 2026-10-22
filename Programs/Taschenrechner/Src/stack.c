#include "stack.h"
#include "exception.h"
#include "token.h"

#define STACK_SIZE 2

static int stack[STACK_SIZE];
static int sp = 0;

int stack_push(int val) {
    if (sp >= STACK_SIZE) {
        return OVERFLOW;
    }
    stack[sp++] = val; // sp nach hochsetzen,  ziel links
    return 0;
}

void stack_init() {
    sp = 0;
}

int stack_pop(int *val) {
    if (sp <= 0) {
        return UNDERFLOW;
    }
    *val = stack[--sp] ; //erst sp runtersetzen, ziel links
    return 0;
}
int stack_peek(int t, int *val) {
    if (t < 0 || t >= sp) {
        return -1;
    }
    *val = stack[sp - 1 - t];
    return 0;
}
