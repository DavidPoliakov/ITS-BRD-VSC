public class PrimzahlSieb {
    byte[] sieb = new byte[1001];
    int[] primzahl = new int[200];

    public void berechnen() {
        // Initialisieren
        for (int i = 2; i <= 1000; i++) {
            sieb[i] = 1;
        }

        // Sieben
        for (int i = 2; i <= 1000; i++) {
            if (sieb[i] == 1) {
                for (int v = i * i; v <= 1000; v += i) {
                    sieb[v] = 0;
                }
            }
        }

        // Speichern
        int index = 0;
        for (int i = 2; i <= 1000; i++) {
            if (sieb[i] == 1) {
                primzahl[index] = i;
                index++;
            }
        }
    }
}