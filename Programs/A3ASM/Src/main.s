;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2
Base
VariableA          DCW 0x1234
VariableB          DCW 0x4711

VariableC          DCD  0

MeinHalbwortFeld   DCW 0x22 , 0x3e , -52, 78 , 0x27 , 0x45

MeinWortFeld       DCD 0x12345678 , 0x9dca5986
                   DCD -872415232 , 1308622848
                   DCD 0x27000000
                   DCD 0x45000000

MeinTextFeld       DCB "ABab0123",0

                   EXPORT VariableA
                   EXPORT VariableB
                   EXPORT VariableC
                   EXPORT MeinHalbwortFeld
                   EXPORT MeinWortFeld
                   EXPORT MeinTextFeld

;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 3
; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard                 ; HW Initialisieren

; Laden von Konstanten in Register
                mov   r0,#0x12                      ; Anw-1 Konstante 0x12 in r0 laden
                mov   r1,#-128                      ; Anw-2 Konstante -128 in r1 laden
                ldr   r2,=0x12345678                ; Anw-3 Adresse 0x12345678 in r2 laden

; Zugriff auf Variable
                ldr   r0,=VariableA                 ; Anw-4 Adresse von VariableA in r0 laden
                ldrh  r1,[r0]                       ; Anw-5 2 Bytes von VariableA in r1 laden
                ldr   r2,[r0]                       ; Anw-6 4 Bytes von VariableA in r2 laden 
                str   r2,[r0,#VariableC-VariableA]  ; Anw-7 Speichert 4 Bytes von r2 in VariableC (Adresse von VariableA + Offset von VariableC)

; Zugriff auf Felder (Speicherzellen)
                ldr   r0,=MeinHalbwortFeld          ; Anw-8 Adresse von MeinHalbwortFeld in r0 laden
                ldrh  r1,[r0]                       ; Anw-9 2 Bytes von MeinHalbwortFeld [0] in r1 laden
                ldrh  r2,[r0,#2]                    ; Anw-10 2 Bytes von MeinHalbwortFeld [1] in r2 laden
                mov   r3,#10                        ; Anw-11 Konstante 10 in r3 laden
                ldrh  r4,[r0,r3]                    ; Anw-12 2 Bytes von MeinHalbwortFeld [5] in r4 laden

                ldrh  r5,[r0,#2]!                   ; Anw-13 2 Bytes von MeinHalbwortFeld [1] in r5 laden und r0 um 2 erhöhen 
                ldrh  r6,[r0,#2]!                   ; Anw-14 2 Bytes von MeinHalbwortFeld [2] in r6 laden und r0 um 2 erhöhen
                strh  r6,[r0,#2]!                   ; Anw-15 2 Bytes von r6 in MeinHalbwortFeld [2] speichern und r0 um 2 erhöhen

; Addition und Subtraktion von unsigned / signed Integer-Werten
                ldr  r0,=MeinWortFeld               ; Anw-16 Adresse von MeinWortFeld in r0 laden
                ldr  r1,[r0]                        ; Anw-17 4 Bytes von MeinWortFeld [0] in r1 laden 
                ldr  r2,[r0,#4]                     ; Anw-18 4 Bytes von MeinWortFeld [1] in r2 laden
                adds r3,r1,r2                       ; Anw-19 Addition von r1 und r2 in r3 speichern 

                ldr  r4,[r0,#8]                     ; Anw-20 4 Bytes von MeinWortFeld [2] in r4 laden
                ldr  r5,[r0,#12]                    ; Anw-21 4 Bytes von MeinWortFeld [3] in r5 laden
                subs r6,r4,r5                       ; Anw-22 Subtraktion von r4 und r5 in r6 speichern

                ldr  r7,[r0,#16]                    ; Anw-23 4 Bytes von MeinWortFeld [4] in r7 laden
                ldr  r8,[r0,#20]                    ; Anw-24 4 Bytes von MeinWortFeld [5] in r8 laden
                subs r9,r7,r8                       ; Anw-25 Subtraktion von r7 und r8 in r9 speichern

forever         b   forever                         ; Anw-26 Endlosschleife
                ENDP
                END