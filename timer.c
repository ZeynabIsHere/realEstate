#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(int seconds) {
    int milli_seconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds) ;
}

int main() {
    for (int i = 7; i >= 0; i--) {
        printf("%d  ", i);
        delay(1);
    }
    return 0;
}
