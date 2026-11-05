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
#include "functions.h"
<<<<<<< HEAD
#include "stdio.h"
#include "token.h"

#define BUFFER_SIZE 13
#define INT_MINIMUM (-2147483648)

static void print_help(Terminal *term, int line){
    char buf[BUFFER_SIZE];
    sprintf(buf, "%d\n", line);
    printTerm(buf, term);
}
=======
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be

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
<<<<<<< HEAD
    int err_su = stack_pop(&second);
    if(err_su){
        return err_su;
    }
    err_su = stack_pop(&first);
    if(err_su){
        return err_su;
    }
    int err_io;
    if(__builtin_sub_overflow(first, second, &err_io)){
        return INT_UNDERFLOW;
=======
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
    }
    int erg = first - second;
    return stack_push(erg);
}

int mult(){
    int first;
    int second;
<<<<<<< HEAD
    int err_su = stack_pop(&second);
    if(err_su){
        return err_su;
    }
    err_su = stack_pop(&first);
    if(err_su){
        return err_su;
    }
    int err_io;
    if(__builtin_mul_overflow(first, second, &err_io)){
        if(((first > 0) && (second > 0) )|| ((first < 0) && (second < 0))){
                err_io = OVERFLOW;
            } else {
               err_io = INT_UNDERFLOW; 
            }
        return err_io;
=======
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
    }
    int erg = first * second;
    return stack_push(erg);
}

int div(){
    int first;
    int second;
<<<<<<< HEAD
    int err_su = stack_pop(&second);
    if(err_su){
        return err_su;
    }
=======
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
<<<<<<< HEAD
    if(first == INT_MINIMUM){
        return INT_OVERFLOW;
=======
    int err_two = stack_pop(&second);
    if(err_two){
        return err_two;
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
    }
    if(second == 0){
        return DIV_BY_ZERO;
    }
    int erg = first / second;
    return stack_push(erg);
}

int print(){
    int line;
    if(stack_pop(&line)){
        return STACK_UNDERFLOW;
    }
    print_stdout((char* )line);
    stack_push(line);
    return 0;
}

<<<<<<< HEAD
int print_all(Terminal *term){
    int line[3];
    int i = 0;
    for (;i < 3; i++) {
        if(stack_pop(&line[i])){
            break;
=======
int print_all(){
    int line;
    for (int i = 0; i < 4; i++) {
        if(stack_pop(&line + i)){
        return STACK_UNDERFLOW;
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
        }
        print_stdout((char* )line + i);
    }
<<<<<<< HEAD
    i--;
    for (; i >= 0; i--) {
        print_help(term, line[i]);
        stack_push(line[i]);
=======
    for (int i = 0; i < 4; i++) {
        stack_push(line + 3 - i);
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
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
    stack_push(first);
<<<<<<< HEAD
    stack_push(second);
    return 0;
=======
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
}

int clear(){
    stack_clear();
}

int doppeln(){
    int first;
    int err_one = stack_pop(&first);
    if(err_one){
        return err_one;
    }
    stack_push(first);
<<<<<<< HEAD
    return stack_push(first);;
=======
    stack_push(first);
>>>>>>> aab8759ac34da669f70e47db45767de909ece4be
}

