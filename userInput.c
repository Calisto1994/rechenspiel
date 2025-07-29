#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

// ****** Nutzereingabefunktionen ******
// Wichtige Funktionen:
// userInput: Liest eine Zeichenkette von der Standardeingabe ein und speichert sie in einem dynamisch allozierten Puffer.
// userInput_c: Liest ein einzelnes Zeichen von der Standardeingabe ein und speichert es in einem char-Puffer.
// userInput_ml: Liest mehrere Zeilen von der Standardeingabe ein und speichert sie in einem dynamisch allozierten Puffer.
// userInput_int: Liest eine Ganzzahl von der Standardeingabe ein und speichert sie in einem int-Puffer.
// userInput_double: Liest eine Gleitkommazahl von der Standardeingabe ein und speichert sie in einem double-Puffer.    

// !!!!! WICHTIG: Alle Funktionen sind speichersicher implementiert, d.h. sie verwenden dynamische Speicherallokation (malloc/realloc) und behandeln Fehlerfälle wie Speicherknappheit oder ungültige Eingaben.
// Allerdings müssen Anwendungen, die diese Funktionen verwenden, den zurückgegebenen Puffer nach der Verwendung mit free() freigeben, um Speicherlecks zu vermeiden.

int userInput (char **buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe
int userInput_c (char *buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe (Einzelzeichen)
int userInput_ml (char **buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe (mehrere Zeilen)
int userInput_int (int *buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe für Ganzzahlen
int userInput_double (double *buffer, char* prompt); // Speichersichere Implementierung der Nutzereingabe für Gleitkommazahlen

// ****** Zeicheneingabefunktionen ******

int userInput (char **buffer, char* prompt) {
    char thisChar;
    *buffer = malloc(1);
    size_t size = 1;
    size_t len = 0;

    printf("%s", prompt);
    while ((thisChar = getchar()) != '\n' && thisChar != EOF) {
        if (len + 2 > size) {
            size *= 2;
            char* tmp = realloc(*buffer, size);
            if (!tmp) {
                fprintf(stderr, "Memory allocation failed\n");
                free(*buffer);
                return 1;
            }
            *buffer = tmp;
        }
        (*buffer)[len++] = thisChar;
        (*buffer)[len] = '\0'; // Null-terminate the string
    }
    return 0;
}

int userInput_c (char *buffer, char* prompt) {
    char* thisChar;
    if (userInput(&thisChar, prompt) != 0) {
        return 1;
    }
    *buffer = thisChar[0]; // Nur das erste Zeichen wird übernommen
    return 0;
}

int userInput_ml (char **buffer, char* prompt) {
    char thisChar;
    *buffer = malloc(1);
    size_t size = 1;
    size_t len = 0;

    printf("%s", prompt);
    while ((thisChar = getchar()) != EOF) { // Nur nach EOF abfragen für mehrere Zeilen ("\n" wird nicht berücksichtigt)
        if (len + 2 > size) {
            size *= 2;
            char* tmp = realloc(*buffer, size);
            if (!tmp) {
                fprintf(stderr, "Memory allocation failed\n");
                free(*buffer);
                return 1;
            }
            *buffer = tmp;
        }
        (*buffer)[len++] = thisChar;
        (*buffer)[len] = '\0'; // Null-terminate the string
    }
    return 0;
}

// ****** Nummerneingabefunktionen ******

int userInput_int (int *buffer, char* prompt) {
    // Variablen
    char *input;
    char *endptr;

    // Eingabe durch den Nutzer
    if (userInput(&input, prompt) != 0) {
        printf("Fehler bei der Eingabe.\n");
        free(input);
        return 1; // Fehler bei der Eingabe
    }

    int value = strtol(input, &endptr, 10);

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        printf("Ungültige Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
        free(input);
        return 1; // Fehler bei der Eingabe
    }
    errno=0; // Zurücksetzen von errno für die nächste Eingabe

    free(input);
    *buffer = value;
    return 0; // Erfolgreiche Eingabe
}

int userInput_double (double *buffer, char* prompt) {
    // Variablen
    char *input;
    char *endptr;

    // Eingabe durch den Nutzer
    if (userInput(&input, prompt) != 0) {
        printf("Fehler bei der Eingabe.\n");
        free(input);
        return 1; // Fehler bei der Eingabe
    }

    int value = strtof(input, &endptr);

    if (errno == ERANGE || (endptr == input) || (*endptr != '\0')) {
        printf("Ungültige Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
        free(input);
        return 1; // Fehler bei der Eingabe
    }
    errno=0; // Zurücksetzen von errno für die nächste Eingabe

    free(input);
    *buffer = value;
    return 0; // Erfolgreiche Eingabe
}