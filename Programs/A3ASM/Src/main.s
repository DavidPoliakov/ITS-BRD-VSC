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
; Konstante 0x12 in r0 laden
                mov   r0,#0x12                      ; Anw-1
; Konstante -128 in r1 laden
                mov   r1,#-128                      ; Anw-2
; Adresse 0x12345678 in r2 laden
                ldr   r2,=0x12345678                ; Anw-3


; Zugriff auf Variable
; Adresse von VariableA in r0 laden
                ldr   r0,=VariableA                 ; Anw-4
; 2 Bytes von VariableA in r1 laden
                ldrh  r1,[r0]                       ; Anw-5
; 4 Bytes von VariableA in r2 laden
                ldr   r2,[r0]                       ; Anw-6
; 4 Bytes von r2 in VariableC speichern (Adresse von VariableA + Offset von VariableC)
                str   r2,[r0,#VariableC-VariableA]  ; Anw-7


; Zugriff auf Felder (Speicherzellen)
; Adresse von MeinHalbwortFeld in r0 laden
                ldr   r0,=MeinHalbwortFeld          ; Anw-8
; 2 Bytes von MeinHalbwortFeld[0] in r1 laden
                ldrh  r1,[r0]                       ; Anw-9
; 2 Bytes von MeinHalbwortFeld[1] in r2 laden
                ldrh  r2,[r0,#2]                    ; Anw-10
; Konstante 10 in r3 laden
                mov   r3,#10                        ; Anw-11
; 2 Bytes von MeinHalbwortFeld[5] in r4 laden
                ldrh  r4,[r0,r3]                    ; Anw-12


; 2 Bytes von MeinHalbwortFeld[1] in r5 laden und r0 um 2 erhöhen
                ldrh  r5,[r0,#2]!                   ; Anw-13
; 2 Bytes von MeinHalbwortFeld[2] in r6 laden und r0 um 2 erhöhen
                ldrh  r6,[r0,#2]!                   ; Anw-14
; 2 Bytes von r6 in MeinHalbwortFeld[2] speichern und r0 um 2 erhöhen
                strh  r6,[r0,#2]!                   ; Anw-15


; Addition und Subtraktion von unsigned / signed Integer-Werten
; Adresse von MeinWortFeld in r0 laden
                ldr  r0,=MeinWortFeld               ; Anw-16
; 4 Bytes von MeinWortFeld[0] in r1 laden
                ldr  r1,[r0]                        ; Anw-17
; 4 Bytes von MeinWortFeld[1] in r2 laden
                ldr  r2,[r0,#4]                     ; Anw-18
; Addition von r1 und r2 in r3 speichern
                adds r3,r1,r2                       ; Anw-19


; 4 Bytes von MeinWortFeld[2] in r4 laden
                ldr  r4,[r0,#8]                     ; Anw-20
; 4 Bytes von MeinWortFeld[3] in r5 laden
                ldr  r5,[r0,#12]                    ; Anw-21
; Subtraktion von r4 und r5 in r6 speichern
                subs r6,r4,r5                       ; Anw-22


; 4 Bytes von MeinWortFeld[4] in r7 laden
                ldr  r7,[r0,#16]                    ; Anw-23
; 4 Bytes von MeinWortFeld[5] in r8 laden
                ldr  r8,[r0,#20]                    ; Anw-24
; Subtraktion von r7 und r8 in r9 speichern
                subs r9,r7,r8                       ; Anw-25


; Endlosschleife
forever         b   forever                         ; Anw-26
                ENDP
                END