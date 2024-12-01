
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void type_effect(const char *text) {
    while (*text) {
        printf("%c", *text++);
        fflush(stdout);
        usleep(35000);
    }
}
int get_random_between(int min, int max) {
    if (max < min) return -1;

    return min + rand() % (max - min + 1);
}
