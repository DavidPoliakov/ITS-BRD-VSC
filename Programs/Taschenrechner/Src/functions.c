/**
 * @file functions.c
 * @author Milan Lingner, HAW Hamburg
 * @date Oct 2016
 *
 * @brief This module implements basic arithmetic functions with a stack.
 */

#include "display.h"
#include "keypad.h"
#include "token.h"
#include "stack.h"
#include "exception.h"
#include "scanner.h"
#include "exception.h"

#ifndef UNDERFLOW
#define UNDERFLOW (-1)
#endif


int plus(){
    int first;
    int second;
    if(stack_pop(&first)){
        return UNDERFLOW;
    }
    if(stack_pop(&second)){
        return UNDERFLOW;
    }
    int erg = first + second;
    return stack_push(erg);
}

int minus(){
    int first;
    int second;
    if(stack_pop(&first)){
        return UNDERFLOW;
    }
    if(stack_pop(&second)){
        return UNDERFLOW;
    }
    int erg = first - second;
    return stack_push(erg);
}

int mult(){
    int first;
    int second;
    if(stack_pop(&first)){
        return UNDERFLOW;
    }
    if(stack_pop(&second)){
        return UNDERFLOW;
    }
    int erg = first * second;
    return stack_push(erg);
}

int div(){
    int first;
    int second;
    if(stack_pop(&first)){
        return UNDERFLOW;
    }
    if(stack_pop(&second)){
        return UNDERFLOW;
    } else if(second == 0){
        return DIV_BY_ZERO;
    }
    int erg = first / second;
    return stack_push(erg);
}

int print(){
    int line;
    if(stack_pop(&line)){
        return UNDERFLOW;
    }
    print_stdout((char* )line);
    stack_push(line);
    return 0;
}

int printAll(){
    int line_one;
    for (int i = 0; ; inc-expression) {
    
    }
    if(stack_pop(&line)){
        return UNDERFLOW;
    }
    print_stdout((char* )line);
    stack_push(line);
    return 0;
}

int swap(){
    int first = stack_pop();
    int second = stack_pop();
    int a = 0;
    if(a = stack_push(second)){
        return  stack_push(first);
    }
    return 
}
int clear(){
    clear_stack();
}

