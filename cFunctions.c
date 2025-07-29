#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool getYesNo(); // Funktion zur Abfrage ja/nein
int randomNumber(int min, int max); // Funktion zur Generierung von Zufallszahlen

bool getYesNo () { // Abfrage ja/nein
    char zeichen;

    while (true) {
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