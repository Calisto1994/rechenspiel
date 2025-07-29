#ifndef __unix__ // For Windows systems
#include <stdio.h> // Für printf und fprintf - wird benötigt, um Ausgaben zu machen
#include <locale.h> // Für setlocale-Funktion - wird benötigt, um die Locale auf Deutsch zu setzen
#include <wchar.h> // Für wchar_t - wird benötigt, um die Locale auf Deutsch zu setzen
#include <windows.h> // Für Windows-spezifische Funktionen

void setLocaleToGerman(); // Funktion zum Setzen der deutschen Locale

void setLocaleToGerman() {
    // Setzen der deutschen Locale für die korrekte Darstellung von Zahlen und Zeichen
    if (SetConsoleOutputCP(65001) == 0) {
        // Fehlerbehandlung, wenn die Konsole nicht auf UTF-8 gesetzt werden kann
        fprintf(stderr, "Warnung: Die Konsole konnte nicht auf UTF-8 gesetzt werden.\n");
    }

    if (SetConsoleCP(65001) == 0) {
        // Fehlerbehandlung, wenn die Eingabe-Konsole nicht auf UTF-8 gesetzt werden kann
        fprintf(stderr, "Warnung: Die Eingabe-Konsole konnte nicht auf UTF-8 gesetzt werden.\n");
    }
}
#else // Unix-like systems (Linux, macOS)
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
#endif 