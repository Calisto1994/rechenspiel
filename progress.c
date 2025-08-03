#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For usleep function

#define PBSTR "===================================================================================================="
#define PBWIDTH 100

// ------------- HEADER --------------
void printProgress(double percentage);
int main ();
// -----------------------------------

void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%s%*s]", val, lpad, PBSTR, ">", rpad, "");
    fflush(stdout);
}