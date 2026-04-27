;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Martin Becke    
;* Version            : V1.0
;* Date               : 01.06.2021
;* Description        : This is a simple main to demonstrate data transfer
;                     : and manipulation.
;                     : 
;
;*******************************************************************************
    EXTERN initITSboard ; Helper to organize the setup of the board

    EXPORT main         ; we need this for the linker - In this context it set the entry point,too

ConstByteA  EQU 0xaffe
    
;* We need some data to work on
    AREA DATA, DATA, align=2    
VariableA   DCW 0xbeef
VariableB   DCW 0x1234
VariableC   DCW 0x0000

;* We need minimal memory setup of InRootSection placed in Code Section 
    AREA  |.text|, CODE, READONLY, ALIGN = 3    
    ALIGN   
main
    BL initITSboard             ; needed by the board to setup
;* swap memory - Is there another, at least optimized approach?
    ldr     R0,=VariableA   ; Adresse von VariableA in R0
    ldrb    R2,[R0]         ; Wert von VariableA in R2, aber nur das niederwertige Byte (0xef) 	
    ldrb    R3,[R0,#1]      ; Wert von VariableA in R3, aber nur das höherwertige Byte (0xbe)
    lsl     R2, #8          ; R2 um 8 Bit nach links schieben, damit es das höherwertige Byte von VariableA enthält (0xef00)
    orr     R2, R3          ; R2 und R3 werden bitweise ODER-verknüpft, um den ursprünglichen Wert von VariableA zu rekonstruieren (0xbeef)
    strh    R2,[R0]         ; Der rekonstruierte Wert von VariableA wird zurück in den Speicher geschrieben, aber nur die niederwertigen 16 Bit (0xbeef) 
    
;* const in var
    mov     R5,#ConstByteA  ; Konstante 0xaffe in R5 laden
    strh    R5,[R0]         ; Speichern der Konstante 0xaffe in VariableA

	ldr     R0,=VariableC
	ldrb    R5,[R0]      
	ldrb    R6,[R0,#1]   
	lsl     R7, #8       
	orr     R6, R7       
	strh    R6,[R0]      

;* Change value from x1234 to x4321
    ldr     R1,=VariableB   ; Adresse von VariableB in R1
    ldrh    R8,[R1]         ; Wert von VariableB in R8
    mov     R9, #0x21DE     ; Konstante 0x21DE in R9 laden (0x1234 -> 0x4321)
    add     R8, R8, R9      ; R8 und R9 werden addiert, um die Bits zu vertauschen und in R8 gespeichert (0x1234 + 0x21DE = 0x4321)
    strh    R8,[R1]         ; Wert von R8 (0x4321) wird zurück in VariableB geschrieben
    b .                     ; Endlosschleife 
    
    ALIGN
    END