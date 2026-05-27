;************************************************
;* Globale Daten
;************************************************
                AREA MyData, DATA, ALIGN=2
sieb            SPACE 1001              

                EXPORT sieb
;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 3
; ----- S t a r t des Hauptprogramms -----

                EXPORT main
                EXTERN initITSboard
main            PROC
                bl    initITSboard 
				LDR R0, =sieb 

for_01
				MOV R1, #2
until_01
				CMP R1, #1000
				BGT endo_01
do_01
				MOV R2, #1
				STRB R2, [R0, R1] 	; Alle auf 1
step_01
				ADD R1, R1, #1
				B until_01
endo_01

for_02
				MOV R1, #2
until_02
				CMP R1, #1000 	   ; äußere Schleife
				BGT endo_02
do_02
if_01
				LDRB R2, [R0, R1]
				CMP R2, #1
				BEQ for_03 			; ==1?
				B endif_01

for_03
				MUL R3, R1, R1
until_03
				CMP R3, #1000
				BGT endo_03
do_03
				MOV R4, #0
				STRB R4, [R0, R3] 	; innere Schleife
step_03
				ADD R3, R3, R1
				B until_03
endo_03

endif_01
step_02
				ADD R1, R1, #1
				B until_02 			; äußere Schleife
endo_02

forever
				B forever
				ENDP

				ALIGN
				END