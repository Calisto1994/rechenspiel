#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "userInput.h" // Speichersichere Implementierung der Nutzereingaben

int randomNumber(int min, int max); // Funktion zur Generierung von Zufallszahlen

int randomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min; // Zufallszahl zwischen min und max generieren
}