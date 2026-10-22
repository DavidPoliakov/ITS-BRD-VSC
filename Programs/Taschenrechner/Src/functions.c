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
    int *first;
    int *second;
    if(stack_pop(*first)){
        return UNDERFLOW;
    }
    if(stack_pop(*second)){
        return UNDERFLOW
    }
    int erg = (int *first + int *second);
    return stack_push(erg);
}

int minus(){
    if(getPointer() < 2){
        return UNDERFLOW;
    }
    int first = stack_pop();
    int second = stack_pop();
    int erg = second - first;
    return stack_push(erg);
}

int mult(){
    if(getPointer() < 2){
        return UNDERFLOW;
    }
    int first = stack_pop();
    int second = stack_pop();
    int erg = second * first;
    return stack_push(erg);
}

int div(){
    if(getPointer() < 2){
        return UNDERFLOW;
    }
    int first = stack_pop();
    int second = stack_pop();
    int erg = second / first;
    return stack_push(erg);
}

int print(){
    if(getPointer() < 0){
        return UNDERFLOW;
    }
    print_stdout((char* )&stack_peek(1));
    return 0;
}

int printAll(){
    if(getPointer() < 2){
        return UNDERFLOW;
    }
    for(int i = 0; i < 3; i++){
        print_stdout((char*)&stack_peek(3));
    }
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

