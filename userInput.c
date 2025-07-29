#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

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
    userInput(&thisChar, prompt);
    *buffer = thisChar[0]; // Nur das erste Zeichen wird übernommen
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

    if (errno = ERANGE || (endptr == input) || (*endptr != '\0')) {
        printf("Ungültige Eingabe. Bitte geben Sie eine ganze Zahl ein.\n");
        free(input);
        return 1; // Fehler bei der Eingabe
    }

    free(input);
    *buffer = value;
    return 0; // Erfolgreiche Eingabe
}