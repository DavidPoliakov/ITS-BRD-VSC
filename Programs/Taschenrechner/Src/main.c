/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "init.h"
#include "keypad.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#include "display.h"
#include "scanner.h"
#include "terminal.h"
#include "token.h"
#include "stack.h"

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards

   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   TP_Init(false); // Initialisierung des LCD Boards mit Touch

   init_display();
   Terminal terminal = makeKeyPad();
   
   stack_init();
   // Test in Endlosschleife
   // const int POLL_DELAY = 10000;
   while (1) {
      // HAL_Delay(POLL_DELAY);
      T_token token = next_token();
      
      if (token.tok == NUMBER) {
         int erg = stack_push(token.val);
         if (erg == -1) {
            set_err_mode();
            print_stdout("overflow");
         }
      }
   }
}

// EOF
