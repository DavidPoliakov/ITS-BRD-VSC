/**
 * @file functions.c
 * @author Milan Lingner, HAW Hamburg
 * @date Oct 2016
 *
 * @brief This module implements basic arithmetic functions with a stack.
 */

#include "display.h"
#include "terminal.h"
#include "stack.h"
#include "exception.h"
#include "functions.h"

int plus(){
    int first;
    int second;
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
    }
    int erg = first + second;
    return stack_push(erg);
}

int minus(){
    int first;
    int second;
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
    }
    int erg = first - second;
    return stack_push(erg);
}

int mult(){
    int first;
    int second;
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
    }
    int erg = first * second;
    return stack_push(erg);
}

int div(){
    int first;
    int second;
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
    }
    if(second == 0){
        return DIV_BY_ZERO;
    }
    int erg = first / second;
    return stack_push(erg);
}

int print_first(Terminal *term){
    int line;
    int err_one = stack_pop(&line);
    if(err_one){
        return STACK_UNDERFLOW;
    }
    printTerm((char*)&line, term);
    stack_push(line);
    return 0;
}

int print_all(){
    int line;
    for (int i = 0; i < 4; i++) {
        if(stack_pop(&line + i)){
        return STACK_UNDERFLOW;
        }
        print_stdout((char* )line + i);
    }
    for (int i = 0; i < 4; i++) {
        stack_push(line + 3 - i);
    }
    return 0;
}

int swap(){
    int first;
    int second;
    if(stack_pop(&first)){
        return STACK_UNDERFLOW;
    }
    if(stack_pop(&second)){
        return STACK_UNDERFLOW;
    }
    stack_push(second);
    stack_push(first);
    return 0;
}

int clear(){
    stack_clear();
    return 0;
}

int doppeln(){
    int first;
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    stack_push(first);
    stack_push(first);
    return 0;
}

