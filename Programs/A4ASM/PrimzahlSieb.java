public class PrimzahlSieb {
// nötigen Felder
byte[] sieb = new byte[1001]; // Speicher für Wahrheitswerte für jeweiligem Wert reserviern
int [] primzahl = new int[200]; //Speicher für Primzahlen reservieren

// Initialisieren
for (i = 2; i <= 1000; i++){
    sieb[i] = 1; // Alle Werte auf 1 setzen (als Primzahl markieren)
}

// sieben
for (i = 2; s <= 1000; s++){ // äußere Schleife
    if (sieb[i] == 1){ 
        for (int v = i*i; v <= 1000; v += i){ // innere Schleife (alle Vielfachen von i streichen (auf 0 setzen))
            sieb[v] = 0;
        }
    }
}

// speichern
index = 0;
for (i = 2; i <= 1000; i++){
    if (sieb[i] == 1){
        primzahl[index] = i; // alle Werte mit 1 werden in primzahl abgespeichert
        index++;
    }
}
}
