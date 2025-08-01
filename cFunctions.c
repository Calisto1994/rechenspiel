#include <stdlib.h>

int randomNumber(int min, int max); // Funktion zur Generierung von Zufallszahlen

int randomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min; // Zufallszahl zwischen min und max generieren
}