/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/


#include "init.h"
#include "scanner.h"
#include "display.h"
#include "keypad.h"
#include "token.h"
#include "stack.h"
#include "functions.h"
#include "exception.h"

static int process_input(T_token ein, Terminal *term){
   switch(ein.tok) {
         case NUMBER:
            return stack_push(ein.val);
            break;
         case PLUS:
            return plus();
            break;       
         case MINUS:  
            return minus();
            break;    
         case MULT:  
            return mult();
            break;     
         case DIV:  
            return div();
            break;
         case PRT:
            return print_first(term);
            break;
         case SWAP:
            return swap();
            break;
         case PRT_ALL:
            return print_all(term);
            break;
         case CLEAR:
            return clear();
            break;
         case DOUBLE:
            return doppeln();
            break;
         case UNEXPECTED:
            return UNEXPECTED_TOKEN;
            break;
         case OVERFLOW:
            return INT_OVERFLOW;
            break;
         default:
            return 0;
            break;
      }
}

int main(void) {
   initITSboard();
   Terminal term = init_display();
   while (true) {
      T_token ein = next_token();
      int err = process_input(ein, &term);
      if(err){
         print_except(err);
         break;
      }
   }
}



// EOF
