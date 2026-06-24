;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Franz Korf	
;* Version            : V1.0
;* Date               : 11.05.2022
;* Description        : Rahmen zur Loesung von GTP Woche 7-9 (Stoppuhr).
;
;*******************************************************************************

; Define address of selected GPIO and Timer registers
PERIPH_BASE     	equ	0x40000000                 ;Peripheral base address
AHB1PERIPH_BASE 	equ	(PERIPH_BASE + 0x00020000)
APB1PERIPH_BASE     equ PERIPH_BASE

GPIOD_BASE			equ	(AHB1PERIPH_BASE + 0x0C00)
GPIOF_BASE			equ	(AHB1PERIPH_BASE + 0x1400)
TIM2_BASE           equ (APB1PERIPH_BASE + 0x0000)
	
GPIO_F_PIN        	equ	(GPIOF_BASE + 0x10)

GPIO_D_PIN			equ	(GPIOD_BASE + 0x10)
GPIO_D_SET			equ (GPIOD_BASE + 0x18)
GPIO_D_CLR			equ	(GPIOD_BASE + 0x1A)
	
TIMER				equ (TIM2_BASE + 0x24)   ; CNT : current time stamp (32 bit),  resolution
TIM2_PSC			equ (TIM2_BASE + 0x28)   ; Prescaler  resolution
TIM2_ERG			equ (TIM2_BASE + 0x14)   ; 16 Bit register, Bit 0 : 1 Restart Timer


    EXTERN initITSboard
    EXTERN GUI_init
	EXTERN TP_Init
	EXTERN initTimer
	EXTERN lcdSetFont
	EXTERN lcdGotoXY      		; TFT goto x y function
	EXTERN lcdPrintS			; TFT output function	
    EXTERN lcdPrintC            ; TFT output one character		
	EXTERN Delay				; Delay (ms) function


;********************************************
; Data section, aligned on 4-byte boundery
;********************************************
	AREA MyData, DATA, align = 2

DEFAULT_BRIGHTNESS	DCW     800
init				DCB		"00:00.00", 0
zehnerminuten		DCB		0xFF
einerminuten		DCB		0xFF
zehnersekunden		DCB		0xFF
einersekunden		DCB		0xFF
zehnermillisekunden	DCB		0xFF
einermillisekunden	DCB		0xFF
stoppuhr_zeit      	SPACE 	4    
letzter_timer_wert 	SPACE 	4    
aktueller_zustand  	DCB  	0x04 

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
		BL		initITSboard
		ldr   	r1, =DEFAULT_BRIGHTNESS
		ldrh 	r0, [r1]
		bl   	GUI_init
		bl  	initTimer
		ldr 	R1,=TIM2_PSC   			; Set pre scaler such that 1 timer tick represents 10 us
		mov 	R0,#(90*10-1) 
		strh	R0,[R1]
		ldr 	R1,=TIM2_ERG   			; Restart timer	
		mov		R0,#0x01
		strh	R0,[R1]					; Set UG Bit
		MOV 	R0, #24
		bl  	lcdSetFont

		; Ihre Initialisierung
		MOV     R0,#10
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#'0'
		BL		lcdPrintC

		MOV     R0,#11
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#'0'
		BL		lcdPrintC

		MOV     R0,#12
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#':'
		BL		lcdPrintC

		MOV     R0,#13
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#'0'
		BL		lcdPrintC

		MOV     R0,#14
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#'0'
		BL		lcdPrintC

		MOV     R0,#15
        MOV     R1,#6
		BL      lcdGotoXY
		mov		R0,#'.'
		BL		lcdPrintC

		MOV     R0,#16
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#'0'
		BL		lcdPrintC

		MOV     R0,#17
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,#'0'
		BL		lcdPrintC

superloop
		BL		updateClk		; Zeitspanne seit letztem Durchlauf berechnen und addieren
		BL		checkButtons	; Taster einlesen und FSM-Zustand aktualisieren
		BL		zustandAusfuehren ; LEDs setzen, Zeit anzeigen, INIT ausfuehren
		b		superloop

		ENDP


;--------------------------------------------
; updateClk
; Liest den Timer, berechnet das Delta zum letzten Aufruf
; und addiert es auf stoppuhr_zeit (nur in Zustand 1 oder 2).
; Eingabe:  keine
; Ausgabe:  stoppuhr_zeit aktualisiert, R5 = Delta
; Aendert:  R1-R7
;--------------------------------------------
updateClk PROC
		NOP
		LDR     R1,=TIMER
        LDR     R2, [R1]                ; R2 = Aktueller Hardware-Tick-Wert
        
        LDR     R3, =letzter_timer_wert
        LDR     R4, [R3]                ; R4 = Wert aus der letzten Runde
        
        SUB     R5, R2, R4              ; R5 = Delta (vergangene Ticks)
        STR     R2, [R3]                ; Aktuellen Wert für die nächste Runde merken

        LDR     R1, =aktueller_zustand
        LDRB    R7, [R1]
        
        cmp     R7, #1                  ; Sind wir im Zustand 1 (RUNNING)
        beq     Zeit_Hochzaehlen
        cmp     R7, #2                  ; Sind wir im Zustand 2 (HOLD)
        beq     Zeit_Hochzaehlen
        
        ; wenn 3 oder 4, dann überspringen
        b       updateClk_end

Zeit_Hochzaehlen
        LDR     R6, =stoppuhr_zeit
        LDR     R7, [R6]
        ADD     R7, R7, R5              ; Addiere das Delta auf unsere Software-Uhr
        STR     R7, [R6]

updateClk_end
		BX		LR
		ENDP


;--------------------------------------------
; checkButtons
; Liest GPIO_F_PIN und setzt aktueller_zustand
; gemaess gedruecktem Taster (S7=Bit7, S6=Bit6, S5=Bit5).
; Eingabe:  keine
; Ausgabe:  aktueller_zustand aktualisiert
; Aendert:  R0-R3
;--------------------------------------------
checkButtons PROC
		NOP
		LDR		R0,=GPIO_F_PIN
		ldrb	R0,[R0]
		eor		R0,#0xFF
		and		R1,R0,#0x80
        and     R2,R0,#0x40
		and		R3,R0,#0x20

		cmp 	R1,#0x80
		beq 	ZustandRunning
		cmp		R2,#0x40
		beq		ZustandHold
		cmp		R3,#0x20
		beq		ZustandInit
		b		checkButtons_end
		
ZustandRunning
		ldr		R1,=aktueller_zustand
		mov		R0,#1
		strb	R0,[R1]
		b		checkButtons_end

ZustandHold
		ldr		R1,=aktueller_zustand
		mov		R0,#2
		strb	R0,[R1]
		b		checkButtons_end

ZustandInit
		ldr		R1,=aktueller_zustand
		mov		R0,#3
		strb	R0,[R1]

checkButtons_end
		BX		LR
		ENDP


;--------------------------------------------
; zustandAusfuehren
; Verzweigt anhand von aktueller_zustand zu den
; Unterprogrammen STOP, HOLD, INIT oder RUNNING.
; Eingabe:  keine
; Ausgabe:  keine
; Aendert:  R0, R1, R7
;--------------------------------------------
zustandAusfuehren PROC
		NOP
		LDR     R1, =aktueller_zustand
        LDRB    R7, [R1]
		cmp		R7,#1
		beq		RUNNING
		cmp		R7,#2
		beq 	HOLD
		cmp		R7,#3
		beq		INIT
		cmp		R7,#4
		beq		STOP
		BX		LR

STOP	;Gehilfe von INIT, um Uhr einmalig auf 0 zu setzten
		BX		LR

HOLD	;Unterprogramm, um den Timer anzuhalten
	    mov 	R0,#0xFC						;LED
        LDR		R1,=GPIO_D_CLR					;LED
		str		R0,[R1]							;LED
		mov     R0,#3							;LED
		LDR		R1,=GPIO_D_SET					;LED
		str		R0,[R1]         				;LED
		BX		LR

INIT	;Unterprogramm, um den Timer zu resetten
		mov 	R0,#0xFF						;LED
        LDR		R1,=GPIO_D_CLR					;LED
		str		R0,[R1]							;LED

		ldr     R1, =stoppuhr_zeit              
        mov     R0, #0                   
        str     R0, [R1]           
		MOV     R0,#10
        MOV     R1,#6
		BL      lcdGotoXY

		LDR		R0,=init
		BL		lcdPrintS
		LDR     R1, =aktueller_zustand
        MOV     R0, #4              
        STRB    R0, [R1]
		BX		LR
		
RUNNING	; Unterprogramm, um den Timer laufen zu lassen
		mov 	R0,#0xFE						;LED
        LDR		R1,=GPIO_D_CLR					;LED
		str		R0,[R1]							;LED
		mov     R0,#1							;LED
		LDR		R1,=GPIO_D_SET					;LED
		str		R0,[R1]         				;LED

		BL		displayTime
		BX		LR
		ENDP


;--------------------------------------------
; displayTime
; Liest stoppuhr_zeit, zerlegt sie in Ziffern und
; gibt nur geaenderte Ziffern auf dem TFT aus.
; Eingabe:  keine
; Ausgabe:  TFT-Anzeige aktualisiert
; Aendert:  R0-R11
;--------------------------------------------
displayTime PROC
		NOP
		LDR     R0, =stoppuhr_zeit
        LDR     R0, [R0]
		LDR     R1,=60000000
		udiv    R11,R0,R1 ; R11 = zehner min.
		mul     R1,R11,R1
		sub     R0,R0,R1

		LDR     R1,=6000000
		udiv    R4,R0,R1 ; R4 = einer min.
		mul     R1,R4,R1
		sub     R0,R0,R1

		LDR     R1,=1000000
		udiv    R5,R0,R1 ; R5 = zehner sek.
		mul     R1,R5,R1
		sub     R0,R0,R1

		LDR     R1,=100000
		udiv    R6,R0,R1 ; R6 = einer sek.
		mul     R1,R6,R1
		sub     R0,R0,R1

		LDR     R1,=10000
		udiv    R7,R0,R1 ; R7 = zehner millisek.
		mul     R1,R7,R1
		sub     R0,R0,R1

		LDR     R1,=1000
		udiv    R8,R0,R1 ; R8 = einer millisek.
	    add     R11,#'0'
        add     R4,#'0'
		add     R5,#'0'
		add     R6,#'0'
		add     R7,#'0'
		add     R8,#'0'

if_01	LDR		R9,=zehnerminuten
		LDRB	R10,[R9]
		cmp		R10,R11
		beq		endif_01
then_01
		MOV     R0,#10
        MOV     R1,#6
		BL      lcdGotoXY
		mov		R0,R11
		BL		lcdPrintC
		strb	R11, [R9]		

endif_01
if_02	LDR		R9,=einerminuten
		LDRB	R10,[R9]
		cmp		R10,R4
		beq		endif_02
then_02		
		MOV     R0,#11
        MOV     R1,#6
		BL      lcdGotoXY
		mov		R0,R4
		BL		lcdPrintC
		strb	R4, [R9]		

endif_02
if_03	LDR		R9,=zehnersekunden
		LDRB	R10,[R9]
		cmp		R10,R5
		beq		endif_03
then_03
		MOV     R0,#13
        MOV     R1,#6
		BL      lcdGotoXY
		mov		R0,R5
		BL		lcdPrintC
		strb	R5, [R9]		

endif_03
if_04	LDR		R9,=einersekunden
		LDRB	R10,[R9]
		cmp		R10,R6
		beq		endif_04
then_04
		MOV     R0,#14
        MOV     R1,#6
		BL      lcdGotoXY
		mov		R0,R6
		BL		lcdPrintC
		strb	R6, [R9]		

endif_04
if_05	LDR		R9,=zehnermillisekunden
		LDRB	R10,[R9]
		cmp		R10,R7
		beq		endif_05
then_05		
		MOV     R0,#16
        MOV     R1,#6
		BL      lcdGotoXY
		mov		R0,R7
		BL		lcdPrintC
		strb	R7, [R9]		

endif_05
if_06	LDR		R9,=einermillisekunden
		LDRB	R10,[R9]
		cmp		R10,R8
		beq		endif_06
then_06		
		MOV     R0,#17
        MOV     R1,#6
		BL      lcdGotoXY
		mov     R0,R8
		BL		lcdPrintC
		strb	R8, [R9]
endif_06				
		BX		LR
		ENDP

		ALIGN
		END
