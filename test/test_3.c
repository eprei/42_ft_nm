#include <stdio.h>

double g_var = 3.14;

double add(int x, double y) {
    return x + y;
}

int main(void) {
    const int local_var = 100;

    printf("Global variable: %f\n", g_var);
    printf("Local variable: %d\n", local_var);
    printf("Sum of %d and %f is %f\n", local_var, g_var, add(local_var, g_var));

    return 0;
}