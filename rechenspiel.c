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
#ifndef PORTABLE
    #include "userInput.h" // Header-Datei für die speichersichere Implementierung der Nutzereingaben
#endif
#ifdef __unix__ // only for unices, this won't work on Win32. There, we have to link against libuserInput.dll, but it can be in the apps directory
    #include <dlfcn.h> // dynamisches Laden von Bibliotheken
#endif

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

    #ifdef __unix__
        #ifdef PORTABLE
            // Portable binary, also wird libuserInput.so aus dem Verzeichnis der Anwendung geladen, nicht aus dem System heraus
            // Hierbei ist es NICHT nötig, LD_LIBRARY_PATH als Umgebungsvariable zu setzen, da die Anwendung SELBST das
            // Laden und Linken der Bibliothek übernimmt.
            void* libuserInput = dlopen("./libuserInput.so", RTLD_LAZY);
            if (!libuserInput) {
                const char* error;
                error = dlerror();
                fprintf(stderr, "Error loading library: %s\n", error);
                return 1; // Quit with error
            }
            int (*userInput) (char **buffer, char* prompt) = dlsym(libuserInput, "userInput");
            int (*userInput_c) (char *buffer, char* prompt) = dlsym(libuserInput, "userInput_c");
            int (*userInput_ml) (char **buffer, char* prompt) = dlsym(libuserInput, "userInput_ml");
            int (*userInput_int) (int *buffer, char* prompt) = dlsym(libuserInput, "userInput_int");
            int (*userInput_double) (double *buffer, char* prompt) = dlsym(libuserInput, "userInput_double");
            int (*userInput_yesno) (bool *buffer, char* prompt, char yesChar, char noChar) = dlsym(libuserInput, "userInput_yesno");
            int (*userInput_version) (char **versionInfo, char ***featureList) = dlsym(libuserInput, "userInput_version");
        #endif
    #endif

    char* versionInfo;
    char** featureList;
    userInput_version(&versionInfo, &featureList);
    printf("Umgesetzt mit libuserInput %s\n\n", versionInfo);

    bool requestRandom = true; // Variable, um zu überprüfen, ob das Programm mit einem Kommandozeilenargument gestartet wurde
    int minRand = 1; // Minimalwert für Zufallszahlen
    int maxRand = 25; // Maximalwert für Zufallszahlen
    int zahl1, zahl2, ergebnis;
    int richtigeAntwort = 0; // Zähler für richtige Antworten
    int falscheAntwort = 0; // Zähler für falsche Antworten
    int anzahlRunden = 0; // Zähler für die Anzahl der Runden
    int i; // Zähler für Schleifen
    double percentageRichtig = 0.0; // Variable für die prozentuale Angabe der richtigen Antworten
    bool yesNo; // Puffer für Ja/Nein

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

        // Wandle das Kommandozeilenargument in einen statischen Puffer, der nicht freigegeben werden muss
        // außerdem ist dieser ein `char`, kein `char*` und kann somit in einem switch()-Statement eingesetzt werden.
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
                printf("  --hilfe, -?:     Hilfe anzeigen\n");
                return 0; // Programm erfolgreich beendet
                break;
            default:
                printf("Ungültiges Kommandozeilenargument!\n");
                return 1; // Programm mit Fehlercode beenden
                break;
        }
    } else if (requestRandom == true) { // Nur, wenn keine (gültigen) Kommandozeilenargumente übergeben wurden
        while (userInput_yesno(&yesNo, "Möchten Sie mit Zufallszahlen spielen? (j/n): ", 'j', 'n') != 0) (void)0; // wiederhole, bis erfolgreich (j/n)
        if (yesNo == true) {
            printf("Gut. Es wird mit Zufallszahlen gespielt.\n");
            playsWithRandomNumbers = true; // Mit Zufallszahlen spielen
        } else {
            printf("Gut. Es wird ohne Zufallszahlen gespielt.\n");
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
            if (userInput_int(&zahl1, "  Zahl 1: ") != 0) { // Eingabe der ersten Zahl
                printf("Fehlerhafte Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
                continue; // Schleife neu starten
            } else break; // Gültige Eingabe, Schleife verlassen
        }

        while (true) {
            if (playsWithRandomNumbers == true) {
                break; // Wenn Zufallszahlen verwendet werden, wird die Schleife verlassen,
                // da bereits in der oberen Schleife die Zufallszahlen generiert wurden.
            }
            if (userInput_int(&zahl2, "  Zahl 2: ") != 0) { // Eingabe der zweiten Zahl
                printf("Fehlerhafte Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
                continue; // Schleife neu starten
            } else break; // Gültige Eingabe, Schleife verlassen
        }

        // Prüfung auf Null
        // Wenn beide Zahlen Null sind, erneut nach Zahlen fragen
        if (zahl1 == 0 && zahl2 == 0) {
            printf("Beide Zahlen sind Null. Bitte geben Sie andere Zahlen ein.\n");
            continue; // Schleife neu starten
        }

        // Ergebnisberechnung
        printf("Berechne: %d + %d\n", zahl1, zahl2);
        sleep(1); // 1 Sekunde warten, um die Berechnung zu simulieren
        ergebnis = zahl1 + zahl2;

        while (true) {
            if (userInput_int(&ergebnis, "Ergebnis: ") != 0) {
                printf("Fehlerhafte Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
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
            int steps = percentageRichtig + 1; // Anzahl der Schritte für die Fortschrittsanzeige
            int sleepPerStep = 1000*1000 / steps; // 1s insgesamt
            for (i = 0; i < steps; i++) {
                printProgress(i / 100.0); // Fortschrittsanzeige
                usleep(sleepPerStep); // Warten, um die Fortschrittsanzeige zu simulieren
            }            
            printf("\nAuf Wiedersehen!\n");
            break; // Schleife verlassen, wenn der Benutzer nicht mehr spielen möchte
        }

        while (userInput_yesno(&yesNo, "Möchten Sie noch eine Runde spielen? (j/n): ", 'j', 'n') != 0) (void)0;
        if (yesNo == false) { // Abfrage, ob der Benutzer weitermachen möchte
            printf("Sie haben %d richtige und %d falsche Antworten in %d Runden gegeben.\n", richtigeAntwort, falscheAntwort, anzahlRunden);
            percentageRichtig = (int)richtigeAntwort * 100 / anzahlRunden; // Prozentuale Angabe der richtigen Antworten
            int steps = percentageRichtig + 1; // Anzahl der Schritte für die Fortschrittsanzeige
            int sleepPerStep = 1000*1000 / steps; // 1s insgesamt
            for (i = 0; i < steps; i++) {
                printProgress(i / 100.0); // Fortschrittsanzeige
                usleep(sleepPerStep); // Warten, um die Fortschrittsanzeige zu simulieren
            }            
            printf("\nAuf Wiedersehen!\n");
            break; // Schleife verlassen, wenn der Benutzer nicht mehr rechnen möchte
            // Wird die Abfrage nicht mit nein beantwortet, wird die Schleife fortgesetzt
        }
    }
    char* dummy = NULL;
    userInput(&dummy, "Drücke Enter, um zu beenden..."); // Warten auf Enter-Taste, um das Programm
    free(dummy); // Freigeben des Puffers, da er nicht mehr benötigt wird
    return 0; // Programm erfolgreich beendet
}