#include <stdio.h>

double calc() {
    double x = 100.32462344, y=200.333456533452;

    for (int i = 0; i < 100000000; i++) {
        x += y;
    }

    return x;
}

int main() {
    double total = calc();
    printf("%lf", total);
    return 0;
}