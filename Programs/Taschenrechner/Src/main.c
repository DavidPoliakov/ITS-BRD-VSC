/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "exception.h"
#include "init.h"
#include "scanner.h"
#include "display.h"
#include "keypad.h"
#include "token.h"
#include "stack.h"
#include "functions.h"




int main(void) {
   initITSboard();
   init_display();
   Terminal term = makeKeyPad();
   while (true) {
      T_token ein = next_token();
      switch(ein.tok) {
         case NUMBER:
            if(stack_push(ein.val)){
               return STACK_OVERFLOW;
            }
            break;
         case PLUS:
            if(plus()){
               return STACK_UNDERFLOW;
            }
            break;       
         case MINUS:  
            if(minus()){
               return STACK_UNDERFLOW;
            }
            break;    
         case MULT:  
            if(mult()){
               return STACK_UNDERFLOW;
            }
            break;     
         case DIV:  
            if(div()){
               return STACK_UNDERFLOW;
            }
            break;
         case PRT:
            if(print_first(&term)){
               return STACK_UNDERFLOW;
            }
            break;
         case SWAP:
            if(swap()){
               return STACK_UNDERFLOW;
            }
            swap();
            break;
         case PRT_ALL:
            if(print_all()){
               return STACK_UNDERFLOW;
            }
            break;
         case CLEAR:
            clear();
            break;
         case DOUBLE:
            if(doppeln()){
               return STACK_OVERFLOW;
            }
            break;
         case UNEXPECTED:
            break;
         case OVERFLOW:
            return STACK_OVERFLOW;
            break;
         default:
            continue;
      }
   }
}

// EOF
