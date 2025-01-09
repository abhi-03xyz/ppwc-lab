// temperature_monitor.c
#include <stdio.h>
#include <stdlib.h>
#define CRITICAL_THRESHOLD 23.0 // in Fahrenheit
#define MAX_SAFE_TEMPERATURE 50.0 // in Fahrenheit
double celsius_to_fahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

void display_results(double celsius, double fahrenheit, const char *status) {
    printf("%10.2lf | %10.2lf | %-6s\n", celsius, fahrenheit, status);
}

int main() {
    FILE *file;
    char filename[] = "tempratures.txt";
    double celsius, fahrenheit;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    printf("%10s | %10s | %s\n", "Temp (C)", "Temp (F)", "Status");
    printf("---------------------------------------------\n");

    while (fscanf(file, "%lf", &celsius) == 1) {
        fahrenheit = celsius_to_fahrenheit(celsius);

        if (fahrenheit < CRITICAL_THRESHOLD) {
            display_results(celsius, fahrenheit, "Below");
        } else if (fahrenheit > MAX_SAFE_TEMPERATURE) {
            display_results(celsius, fahrenheit, "Above");
        } else {
            display_results(celsius, fahrenheit, "Right");
        }
    }

    fclose(file);
    return 0;
}

