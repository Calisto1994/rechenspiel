#include <stdio.h> // Ein- und Ausgabe-Funktionen
#include <unistd.h> // Für sleep-Funktion
#include <stdbool.h> // Für boolesche Datentypen
#include <stdlib.h> // Für srand und rand-Funktionen
#include <ctype.h> // Für tolower-Funktion
#include <time.h> // Für srand-Funktion - wird benötigt, um Zufallszahlen zu generieren (Seeding)

/* Rechenspiel 
    Das Spiel fragt den Benutzer in 10 Runden nach zwei ganzen Zahlen.
    Anschließend wird die Summe der beiden Zahlen berechnet und der Benutzer muss das Ergebnis eingeben.
    Der Benutzer kann nach jeder Runde entscheiden, ob er weitermachen möchte.

    Für diesen Code ist stdbool.h erforderlich, um die booleschen Datentypen zu verwenden, da diese in Abfragen und Schleifen verwendet werden.

    Alle Eingaben werden auf Gültigkeit geprüft, um sicherzustellen, dass der Benutzer nur ganze Zahlen eingibt.
*/

int main(); // Hauptfunktion des Programms
bool nextRound(); // Funktion zur Abfrage, ob der Benutzer weitermachen möchte
bool randNums(); // Funktion zur Abfrage, ob der Benutzer mit Zufallszahlen spielen möchte
int randomNumber(int min, int max); // Funktion zur Generierung von Zufallszahlen
bool playsWithRandomNumbers = false; // Variable zur Steuerung, ob mit Zufallszahlen gespielt wird

int main () {
    srand(time(NULL)); // Initialisierung des Zufallszahlengenerators mit der aktuellen Zeit

    int minRand = 1; // Minimalwert für Zufallszahlen
    int maxRand = 25; // Maximalwert für Zufallszahlen
    int zahl1, zahl2, ergebnis;
    int richtigeAntwort = 0; // Zähler für richtige Antworten
    int falscheAntwort = 0; // Zähler für falsche Antworten
    int anzahlRunden = 0; // Zähler für die Anzahl der Runden

    if (randNums() == true) {
        playsWithRandomNumbers = true; // Mit Zufallszahlen spielen
    } else {
        playsWithRandomNumbers = false; // Ohne Zufallszahlen spielen
    }

    // Eingabe
    while (true) {
        anzahlRunden++; // Runde erhöhen

        // Ausgabe der aktuellen Runde
        printf("Runde %d:\n", anzahlRunden);
        // Eingabe der Zahlen
        playsWithRandomNumbers==false?printf("Bitte geben Sie zwei ganze Zahlen ein.\n"):(void)0;
        while (true) {
            if (playsWithRandomNumbers == true) {
                zahl1 = randomNumber(minRand, maxRand); // Zufallszahl zwischen 1 und 100
                zahl2 = randomNumber(minRand, maxRand); // Zufallszahl zwischen 1 und 100
                printf("  Zahl 1: %d\n", zahl1);
                printf("  Zahl 2: %d\n", zahl2);
                break; // Schleife verlassen, wenn Zufallszahlen verwendet werden
            }
            printf("  Zahl 1: ");
            if (!scanf(" %d", &zahl1)) {
                printf("Fehlerhafte Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
                while (getchar() != '\n'); // Puffer leeren
                continue; // Schleife neu starten
            } else break; // Gültige Eingabe, Schleife verlassen
        }

        while (true) {
            if (playsWithRandomNumbers == true) {
                break; // Wenn Zufallszahlen verwendet werden, wird die Schleife verlassen,
                // da bereits in der oberen Schleife die Zufallszahlen generiert wurden.
            }
            printf("  Zahl 2: ");
            if (!scanf(" %d", &zahl2)) {
                printf("Fehlerhafte Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
                while (getchar() != '\n'); // Puffer leeren
                continue; // Schleife neu starten
            } else break; // Gültige Eingabe, Schleife verlassen
        }

        // Prüfung auf Null
        // Wenn beide Zahlen Null sind, erneut nach Zahlen fragen
        if (zahl1 == 0 && zahl2 == 0) {
            printf("Beide Zahlen sind Null. Bitte geben Sie andere Zahlen ein.\n");
            while (getchar() != '\n'); // Puffer leeren
            continue; // Schleife neu starten
        }

        // Ergebnisberechnung
        printf("Berechne: %d + %d\n", zahl1, zahl2);
        sleep(1); // 1 Sekunde warten, um die Berechnung zu simulieren
        ergebnis = zahl1 + zahl2;

        while (true) {
            printf("Ergebnis: ");
            if (!scanf(" %d", &ergebnis)) {
                printf("Fehlerhafte Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
                while (getchar() != '\n'); // Puffer leeren
                continue; // Schleife neu starten
            }
            break; // Gültige Eingabe, Schleife verlassen
        }

        if (ergebnis == (zahl1 + zahl2)) {
            printf("Richtig!\n");
            richtigeAntwort++; // Zähler für richtige Antworten erhöhen
        }
        else {
            printf("Leider falsch. Das Ergebnis ist %d.\n", zahl1 + zahl2);
            falscheAntwort++; // Zähler für falsche Antworten erhöhen
        }

        if (anzahlRunden == 10) {
            printf("\nSie haben die maximale Anzahl von 10 Runden erreicht.\n");
            printf("Sie haben %d richtige und %d falsche Antworten gegeben.\n", richtigeAntwort, falscheAntwort);
            printf("Auf Wiedersehen!\n");
            break; // Schleife verlassen, wenn der Benutzer nicht mehr spielen möchte
        } else if (nextRound() == false) { // Abfrage, ob der Benutzer weitermachen möchte
            printf("Sie haben %d richtige und %d falsche Antworten in %d Runden gegeben.\n", richtigeAntwort, falscheAntwort, anzahlRunden);
            printf("Auf Wiedersehen!\n");
            break; // Schleife verlassen, wenn der Benutzer nicht mehr rechnen möchte
            // Wird die Abfrage nicht mit nein beantwortet, wird die Schleife fortgesetzt
        }

        // Eingabe zurücksetzen
        while (getchar() != '\n'); // Puffer leeren

    }
    printf("Drücke STRG+C, um das Programm zu beenden.\n");
    pause(); // Warten auf Signal/Eingabe (STRG+C) oder Signal (z.B. SIGTERM), bevor das Programm endet
    return 0; // Programm erfolgreich beendet
}

bool nextRound () {  // Abfrage, ob der Benutzer weitermachen möchte
    char zeichen;

    while (true) {
        printf("Möchten Sie noch eine Runde? (j/n): ");
        scanf(" %c", &zeichen);

        if (tolower(zeichen) == 'j') {
            printf("\n"); // Neue Zeile für bessere Lesbarkeit
            return true; // Ja
        } else if (tolower(zeichen) == 'n') {
            printf("\n"); // Neue Zeile für bessere Lesbarkeit    
            return false; // Nein
        } else {
            printf("Ungültige Eingabe. Bitte geben Sie 'j' oder 'n' ein.\n");
            while (getchar() != '\n'); // Puffer leeren
            continue; // Schleife neu starten
        }
    }
}

bool randNums () { // Abfrage, ob der Benutzer mit Zufallszahlen spielen möchte
    char zeichen;

    while (true) {
        printf("Möchten Sie mit Zufallszahlen spielen? (j/n): ");
        scanf(" %c", &zeichen);

        if (tolower(zeichen) == 'j') {
            printf("\n"); // Neue Zeile für bessere Lesbarkeit
            return true; // Ja
        } else if (tolower(zeichen) == 'n') {
            printf("\n"); // Neue Zeile für bessere Lesbarkeit    
            return false; // Nein
        } else {
            printf("Ungültige Eingabe. Bitte geben Sie 'j' oder 'n' ein.\n");
            while (getchar() != '\n'); // Puffer leeren
            continue; // Schleife neu starten
        }
    }
}

int randomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min; // Zufallszahl zwischen min und max generieren
}