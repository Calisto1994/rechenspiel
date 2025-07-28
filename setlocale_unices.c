#include <stdio.h> // Für printf und fprintf - wird benötigt, um Ausgaben zu machen
#include <locale.h> // Für setlocale-Funktion - wird benötigt, um die Locale auf Deutsch zu setzen
#include <wchar.h> // Für wchar_t - wird benötigt, um die Locale auf Deutsch zu setzen

void setLocaleToGerman(); // Funktion zum Setzen der deutschen Locale

void setLocaleToGerman() {
    if (setlocale(LC_ALL, "de_DE.UTF-8") == NULL) {
        // Fehlerbehandlung, wenn die Locale nicht gesetzt werden kann
        fprintf(stderr, "Warnung: Die Locale konnte nicht auf Deutsch gesetzt werden.\n");
    }
}