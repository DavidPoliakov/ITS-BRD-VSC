;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Franz Korf	
;* Version            : V1.0
;* Date               : 11.05.2022
;* Description        : Rahmen zur Loesung von GTP Woche 7-9 (Stoppuhr).
;*******************************************************************************

; Define address of selected GPIO and Timer registers
PERIPH_BASE     	equ 0x40000000                 ;Peripheral base address
AHB1PERIPH_BASE 	equ (PERIPH_BASE + 0x00020000)
APB1PERIPH_BASE         equ PERIPH_BASE

GPIOD_BASE		equ (AHB1PERIPH_BASE + 0x0C00)
GPIOF_BASE	        equ (AHB1PERIPH_BASE + 0x1400)
TIM2_BASE               equ (APB1PERIPH_BASE + 0x0000)
GPIO_F_PIN        	equ (GPIOF_BASE + 0x10)
GPIO_D_PIN		equ (GPIOD_BASE + 0x10)
GPIO_D_SET		equ (GPIOD_BASE + 0x18)
GPIO_D_CLR		equ (GPIOD_BASE + 0x1A)
TIMER		        equ (TIM2_BASE + 0x24)   ; CNT : current time stamp (32 bit),  resolution
TIM2_PSC		equ (TIM2_BASE + 0x28)   ; Prescaler  resolution
TIM2_ERG	        equ (TIM2_BASE + 0x14)   ; 16 Bit register, Bit 0 : 1 Restart Timer


        EXTERN initITSboard
        EXTERN GUI_init
        EXTERN TP_Init
	EXTERN initTimer
	EXTERN lcdSetFont
	EXTERN lcdGotoXY      		; TFT goto x y function
	EXTERN lcdPrintS	        ; TFT output function	
        EXTERN lcdPrintC                ; TFT output one character		
	EXTERN delay			; Behoben: Kleingeschrieben laut Library-Referenz


;********************************************
; Data section, aligned on 4-byte boundery
;********************************************
	AREA MyData, DATA, align = 2

DEFAULT_BRIGHTNESS	DCW     800
init			DCB     "00:00.00", 0
zehnerminuten		DCB	0xFF
einerminuten		DCB	0xFF
zehnersekunden		DCB	0xFF
einersekunden		DCB	0xFF
zehnermillisekunden	DCB	0xFF
einermillisekunden	DCB	0xFF
stoppuhr_zeit      	SPACE 	4    
letzter_timer_wert 	SPACE 	4    
aktueller_zustand  	DCB  	0x03 	; Startet im Zustand 3 (INIT)

;********************************************
; Code section, aligned on 8-byte boundery
;********************************************
	AREA |.text|, CODE, READONLY, ALIGN = 3
;--------------------------------------------
; main subroutine
;--------------------------------------------
	EXPORT main [CODE]
	
main	PROC
        ; Initialisierung der HW
        BL	initITSboard
        ldr   	r1, =DEFAULT_BRIGHTNESS
        ldrh 	r0, [r1]
        bl   	GUI_init
        bl  	initTimer
        ldr 	R1,=TIM2_PSC   			
        mov 	R0,#(90*10-1) 
        strh	R0,[R1]
        ldr 	R1,=TIM2_ERG   		
        mov	R0,#0x01
        strh	R0,[R1]					
        MOV 	R0, #24
        bl  	lcdSetFont

        ; Initiale Hardware-Timer-Auslesung, damit das erste Delta stimmt
        LDR     R1,=TIMER
        LDR     R2,[R1]
        LDR     R3,=letzter_timer_wert
        STR     R2,[R3]

        ; Initiale Display-Ausgabe der Nullen
        MOV     R0,#10
        MOV     R1,#6
        BL      lcdGotoXY
        LDR	R0,=init
        BL	lcdPrintS

superloop
        BL	updateClk		; Zeitspanne berechnen und aufaddieren
        BL	checkButtons	        ; Taster einlesen und Zustand wechseln
        BL	zustandAusfuehren       ; LEDs aktualisieren

        LDR     R1, =aktueller_zustand
        LDRB    R0, [R1]
        
        CMP     R0, #3                  ; Wenn Zustand = INIT (3)
        BEQ     ausgabe_init
        CMP     R0, #2                  ; Wenn Zustand = HOLD (2)
        BEQ     skip_display            ; Anzeige einfrieren
        
        ; Im Zustand RUNNING (1) und STOP (4) Uhrzeit aktualisieren
        BL	displayTime
        B       skip_display

ausgabe_init
        MOV     R0,#10
        MOV     R1,#6
        BL      lcdGotoXY
        LDR	R0,=init
        BL	lcdPrintS
        
        ; Nach dem Zeichnen der Nullen automatisch in den Zustand STOP (4) wechseln
        LDR     R1, =aktueller_zustand
        MOV     R0, #4              
        STRB    R0, [R1]

skip_display
        ; Kurze Verzögerung zur Stabilisierung und Tasterentprellung
        MOV     R0, #10
        b	superloop
        ENDP
;--------------------------------------------
; updateClk
;--------------------------------------------
updateClk PROC
        LDR     R1,=TIMER
        LDR     R2, [R1]                

        LDR     R3, =letzter_timer_wert
        LDR     R4, [R3]                

        SUB     R5, R2, R4              ; R5 = Delta Ticks
        STR     R2, [R3]                

        LDR     R1, =aktueller_zustand
        LDRB    R7, [R1]

        CMP     R7, #1                  ; Nur im Zustand 1 (RUNNING) wird hochgezählt
        BNE     updateClk_end

        LDR     R6, =stoppuhr_zeit
        LDR     R7, [R6]
        ADD     R7, R7, R5              
        STR     R7, [R6]

updateClk_end
        BX		LR
        ENDP
;--------------------------------------------
; checkButtons
;--------------------------------------------
checkButtons PROC
        LDR     R0,=GPIO_F_PIN
        LDRB    R0,[R0]
        
        ; S7 (Bit 7) -> RUNNING (1)
        ANDS    R1, R0, #0x80           
        BEQ     ZustandRunning          
        
        ; S6 (Bit 6) -> HOLD (2)
        ANDS    R1, R0, #0x40          
        BEQ     ZustandHold            
        
        ; S5 (Bit 5) -> INIT (3)
        ANDS    R1, R0, #0x20           
        BEQ     ZustandInit             
        
        B       checkButtons_end
        
ZustandRunning
        LDR     R1,=aktueller_zustand
        MOV     R0,#1
        STRB    R0,[R1]
        B       checkButtons_end

ZustandHold
        LDR     R1,=aktueller_zustand
        MOV     R0,#2
        STRB    R0,[R1]
        B       checkButtons_end

ZustandInit
        LDR     R1,=aktueller_zustand
        MOV     R0,#3
        STRB    R0,[R1]

checkButtons_end
        BX      LR
        ENDP
;--------------------------------------------
; zustandAusfuehren
;--------------------------------------------
zustandAusfuehren PROC
        LDR     R1, =aktueller_zustand
        LDRB    R7, [R1]
        CMP	R7,#1
        BEQ	RUNNING
        CMP	R7,#2
        BEQ     HOLD
        CMP	R7,#3
        BEQ	INIT
        CMP	R7,#4
        BEQ	STOP
        BX      LR

STOP	; Zustand 4: Uhr steht still (LEDs aus)
        MOV 	R0,#0x03						
        LDR	R1,=GPIO_D_CLR
        STR	R0,[R1]
        BX	LR

HOLD	; Zustand 2: HOLD (LED D8 und D9 an)
        MOV     R0,#3							
        LDR	R1,=GPIO_D_SET
        STR	R0,[R1]         
        BX	LR

INIT	; Zustand 3: Reset (Uhrzeit nullen, LEDs aus)
        MOV 	R0,#0x03						
        LDR	R1,=GPIO_D_CLR
        STR	R0,[R1]

        LDR     R1, =stoppuhr_zeit              
        MOV     R0, #0                   
        STR     R0, [R1]           
        BX	LR
        
RUNNING	; Zustand 1: RUNNING (Nur LED D8 an, D9 aus)
        MOV 	R0,#0x02		; D9 aus				
        LDR	R1,=GPIO_D_CLR
        STR	R0,[R1]
        MOV     R0,#1                   ; D8 an                
        LDR	R1,=GPIO_D_SET
        STR	R0,[R1]         
        BX	LR
        ENDP
;--------------------------------------------
; displayTime
;--------------------------------------------
displayTime PROC
        PUSH    {R4-R11, LR}

        LDR     R0, =stoppuhr_zeit
        LDR     R0, [R0]
        LDR     R1,=60000000
        UDIV    R11,R0,R1 ; R11 = zehner min.
        MUL     R1,R11,R1
        SUB     R0,R0,R1

        LDR     R1,=6000000
        UDIV    R4,R0,R1 ; R4 = einer min.
        mul     R1,R4,R1
        sub     R0,R0,R1

        LDR     R1,=1000000
        UDIV    R5,R0,R1 ; R5 = zehner sek.
        mul     R1,R5,R1
        sub     R0,R0,R1

        LDR     R1,=100000
        UDIV    R6,R0,R1 ; R6 = einer sek.
        mul     R1,R6,R1
        sub     R0,R0,R1

        LDR     R1,=10000
        UDIV    R7,R0,R1 ; R7 = zehner millisek.
        mul     R1,R7,R1
        sub     R0,R0,R1

        LDR     R1,=1000
        UDIV    R8,R0,R1 ; R8 = einer millisek.
        ADD     R11,#'0'
        ADD     R4,#'0'
        ADD     R5,#'0'
        ADD     R6,#'0'
        ADD     R7,#'0'
        ADD     R8,#'0'

if_01	        
        LDR	R9,=zehnerminuten
        LDRB	R10,[R9]
        CMP	R10,R11
        BEQ	endif_01
then_01
        MOV     R0,#10
        MOV     R1,#6
        BL      lcdGotoXY
        MOV	R0,R11
        BL	lcdPrintC
        STRB	R11, [R9]		

endif_01
if_02	        
        LDR	R9,=einerminuten
        LDRB	R10,[R9]
        CMP	R10,R4
        BEQ	endif_02
then_02		
        MOV     R0,#11
        MOV     R1,#6
        BL      lcdGotoXY
        MOV	R0,R4
        BL	lcdPrintC
        STRB	R4, [R9]		

endif_02
if_03	        
        LDR	R9,=zehnersekunden
        LDRB	R10,[R9]
        CMP	R10,R5
        BEQ	endif_03
then_03
        MOV     R0,#13
        MOV     R1,#6
        BL      lcdGotoXY
        MOV	R0,R5
        BL	lcdPrintC
        STRB	R5, [R9]		

endif_03
if_04	
        LDR	R9,=einersekunden
        LDRB	R10,[R9]
        CMP	R10,R6
        BEQ	endif_04
then_04
        MOV     R0,#14
        MOV     R1,#6
        BL      lcdGotoXY
        MOV	R0,R6
        BL	lcdPrintC
        STRB	R6, [R9]		

endif_04
if_05
	LDR	R9,=zehnermillisekunden
        LDRB	R10,[R9]
        CMP	R10,R7
        BEQ     endif_05
then_05		
        MOV     R0,#16
        MOV     R1,#6
        BL      lcdGotoXY
        MOV	R0,R7
        BL	lcdPrintC
        STRB	R7, [R9]		

endif_05
if_06	
        LDR	R9,=einermillisekunden
        LDRB	R10,[R9]
        CMP	R10,R8
        BEQ	endif_06
then_06		
        MOV     R0,#17
        MOV     R1,     #6
        BL      lcdGotoXY
        MOV     R0,R8
        BL	lcdPrintC
        STRB	R8, [R9]
endif_06				
        POP     {R4-R11, PC}
        ENDP

        ALIGN
        END