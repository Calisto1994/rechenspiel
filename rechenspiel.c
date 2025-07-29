#include <stdio.h> // Ein- und Ausgabe-Funktionen
#include <unistd.h> // Für sleep-Funktion
#include <stdbool.h> // Für boolesche Datentypen
#include <stdlib.h> // Für srand und rand-Funktionen
#include <ctype.h> // Für tolower-Funktion
#include <time.h> // Für srand-Funktion - wird benötigt, um Zufallszahlen zu generieren (Seeding)
#include <string.h> // Für strcmp-Funktion - wird benötigt, um die Kommandozeilenargumente zu vergleichen
#include <locale.h> // Für setlocale-Funktion - wird benötigt, um die Locale auf Deutsch zu setzen
#include <wchar.h> // Für wchar_t - wird benötigt, um die Locale auf Deutsch zu setzen
#include "setlocales.h" // Header-Datei für die setLocaleToGerman-Funktion
#include "cFunctions.h" // Header-Datei für "cFunctions.c"
#include "progress.h" // Header-Datei für die Fortschrittsanzeige

/* Rechenspiel 
    Das Spiel fragt den Benutzer in 10 Runden nach zwei ganzen Zahlen.
    Anschließend wird die Summe der beiden Zahlen berechnet und der Benutzer muss das Ergebnis eingeben.
    Der Benutzer kann nach jeder Runde entscheiden, ob er weitermachen möchte.

    Für diesen Code ist stdbool.h erforderlich, um die booleschen Datentypen zu verwenden, da diese in Abfragen und Schleifen verwendet werden.

    Alle Eingaben werden auf Gültigkeit geprüft, um sicherzustellen, dass der Benutzer nur ganze Zahlen eingibt.
*/

// ----------------------------------- HEADER -----------------------------------
// FUNKTIONEN
int main(int argc, char *argv[]); // Hauptfunktion des Programms
// VARIABLEN
bool playsWithRandomNumbers = false; // Variable zur Steuerung, ob mit Zufallszahlen gespielt wird
// -----------------------------------------------------------------------------


int main (int argc, char *argv[]) {
    bool requestRandom = true; // Variable, um zu überprüfen, ob das Programm mit einem Kommandozeilenargument gestartet wurde
    int minRand = 1; // Minimalwert für Zufallszahlen
    int maxRand = 25; // Maximalwert für Zufallszahlen
    int zahl1, zahl2, ergebnis;
    int richtigeAntwort = 0; // Zähler für richtige Antworten
    int falscheAntwort = 0; // Zähler für falsche Antworten
    int anzahlRunden = 0; // Zähler für die Anzahl der Runden
    int i; // Zähler für Schleifen
    double percentageRichtig = 0.0; // Variable für die prozentuale Angabe der richtigen Antworten

    srand(time(NULL)); // Initialisierung des Zufallszahlengenerators mit der aktuellen Zeit

    setLocaleToGerman(); // Setzen der deutschen Locale für die korrekte Darstellung von Zahlen und Zeichen

    // Überprüfen der Kommandozeilenargumente
    if (argc > 1) {
        char* cmdArg = malloc(strlen(argv[1]) + 1); // Reservieren von Speicher für das Kommandozeilenargument
        strcpy(cmdArg, argv[1]); // Kopieren des Kommandozeilenarguments in eine neue Variable

        for(int i = 0; cmdArg[i]; i++){ // Alle Zeichen des ersten Kommandozeilenarguments in Kleinbuchstaben umwandeln
            cmdArg[i] = tolower(cmdArg[i]);
        }

        // Abfangen des Kommandozeilenarguments und Anlegen der Variable userSelect
        // Dies ermöglicht verschiedene Schreibweisen des gleichen Befehls
        // und die Anzeige der Hilfe.
        // Die Variable userSelect wird später in einem Switch-Statement verwendet,
        // um die gewünschte Aktion auszuführen.

        char userSelect;
        if (strcmp(cmdArg, "random") == 0) userSelect = 'r'; // Mit Zufallszahlen spielen
        else if (strcmp(cmdArg, "--random") == 0) userSelect = 'r'; // Ohne Zufallszahlen spielen
        else if (strcmp(cmdArg, "-r") == 0) userSelect = 'r'; // Ohne Zufallszahlen spielen
        else if (strcmp(cmdArg, "norandom") == 0) userSelect = 'n'; // Ohne Zufallszahlen spielen
        else if (strcmp(cmdArg, "--norandom") == 0) userSelect = 'n'; // Ohne Zufallszahlen spielen
        else if (strcmp(cmdArg, "-n") == 0) userSelect = 'n'; // Ohne Zufallszahlen spielen
        else if (strcmp(cmdArg, "--help") == 0) userSelect = 'h'; // Hilfe anzeigen
        else if (strcmp(cmdArg, "-h") == 0) userSelect = 'h'; // Hilfe anzeigen
        else if (strcmp(cmdArg, "--hilfe") == 0) userSelect = 'h'; // Hilfe anzeigen
        else if (strcmp(cmdArg, "-?") == 0) userSelect = 'h'; // Hilfe anzeigen
        else userSelect = 'x'; // Ungültiges Kommandozeilenargument
        free(cmdArg); // Freigeben des reservierten Speichers für das Kommandozeilenargument

        switch (userSelect) {
            case 'r': // Mit Zufallszahlen spielen
                printf("Es wird mit Zufallszahlen gespielt.\n");
                playsWithRandomNumbers = true; // Mit Zufallszahlen spielen
                requestRandom = false; // Explizite Anforderung von Zufallszahlen            
                break;
            case 'n': // Ohne Zufallszahlen spielen
                printf("Es wird ohne Zufallszahlen gespielt.\n");
                playsWithRandomNumbers = false; // Ohne Zufallszahlen spielen
                requestRandom = false; // Explizite Anforderung von Nicht-Zufallszahlen
                break;
            case 'h': // Hilfe anzeigen"
                printf("Verwendung: %s [random|norandom]\n", argv[0]);
                printf("  random:          Mit Zufallszahlen spielen\n");
                printf("  norandom:        Ohne Zufallszahlen spielen\n");
                printf("  -r, --random:    Mit Zufallszahlen spielen\n");
                printf("  -n, --norandom:  Mit Zufallszahlen spielen\n");
                printf("  -h, --help,\n");
                printf("  --hilfe, -?:      Hilfe anzeigen\n");
                return 0; // Programm erfolgreich beendet
                break;
            default:
                printf("Ungültiges Kommandozeilenargument!\n");
                return 1; // Programm mit Fehlercode beenden
                break;
        }
    } else if (requestRandom == true) { // Nur, wenn keine (gültigen) Kommandozeilenargumente übergeben wurden
        if (getYesNo("Möchten Sie mit Zufallszahlen spielen? (j/n): ") == true) {
            playsWithRandomNumbers = true; // Mit Zufallszahlen spielen
        } else {
            playsWithRandomNumbers = false; // Ohne Zufallszahlen spielen
        }
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
            percentageRichtig = (int)richtigeAntwort * 100 / anzahlRunden; // Prozentuale Angabe der richtigen Antworten
            for (i = 0; i < (percentageRichtig + 1); i++) {
                printProgress(i / 100.0); // Fortschrittsanzeige
                usleep(25000); // 25 ms warten, um die Fortschrittsanzeige zu simulieren
            }            
            printf("\nAuf Wiedersehen!\n");
            break; // Schleife verlassen, wenn der Benutzer nicht mehr spielen möchte
        }
        
        if (getYesNo("Möchten Sie noch eine Runde? (j/n): ") == false) { // Abfrage, ob der Benutzer weitermachen möchte
            printf("Sie haben %d richtige und %d falsche Antworten in %d Runden gegeben.\n", richtigeAntwort, falscheAntwort, anzahlRunden);
            percentageRichtig = (int)richtigeAntwort * 100 / anzahlRunden; // Prozentuale Angabe der richtigen Antworten
            for (i = 0; i < (percentageRichtig + 1); i++) {
                printProgress(i / 100.0); // Fortschrittsanzeige
                usleep(25000); // 25 ms warten, um die Fortschrittsanzeige zu simulieren
            }            
            printf("\nAuf Wiedersehen!\n");
            break; // Schleife verlassen, wenn der Benutzer nicht mehr rechnen möchte
            // Wird die Abfrage nicht mit nein beantwortet, wird die Schleife fortgesetzt
        }

        // Eingabe zurücksetzen
        while (getchar() != '\n'); // Puffer leeren

    }
    printf("Drücke STRG+C, um das Programm zu beenden.\n");
    while (scanf("%*c") != '\n'); // Warten auf Tastendruck, bevor das Programm endet
    return 0; // Programm erfolgreich beendet
}