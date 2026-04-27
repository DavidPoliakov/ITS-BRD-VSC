Adresse von VariableA in R0
Wert von VariableA in R2, aber nur das niederwertige Byte (0xef) 	
Wert von VariableA in R3, aber nur das höherwertige Byte (0xbe)
R2 um 8 Bit nach links schieben, damit es das höherwertige Byte von VariableA enthält (0xef00)
R2 und R3 werden bitweise ODER-verknüpft (Disjunktion), um den ursprünglichen Wert von VariableA zu rekonstruieren (0xbeef)
Der rekonstruierte Wert von VariableA wird zurück in den Speicher geschrieben, aber nur die niederwertigen 16 Bit (0xbeef) 
Konstante 0xaffe in R5 laden
Speichern der Konstante 0xaffe in VariableA
Adresse von VariableB in R1
Wert von VariableB in R6
Konstante 0x30ED in R7 laden
R6 und R7 werden addiert, um die Bits zu vertauschen und in R6 gespeichert (0x1234 + 0x30ED = 0x4321)
Wert von R6 (0x4321) wird zurück in VariableB geschrieben
Endlosschleife 