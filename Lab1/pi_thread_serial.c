#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define STEPS 10000000
#define STEP_SIZE 1.0 / STEPS

double serial_pi()
{

    double low = 0.5 * STEP_SIZE;
    double upp = 1;
    double tsum = 0;

    while (low < upp)
    {
        tsum += sqrt(1 - low * low) * STEP_SIZE;
        low += STEP_SIZE;
    }

    return 4 * tsum;
}

int main()
{

    clock_t start_t = clock();
    double sum = serial_pi();
    clock_t end_t = clock();

    printf("Reference PI = %.10lf Computed PI = %.10lf\n", M_PI, sum);
    printf("Difference to Reference is %.10lf\n", M_PI - sum);

    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken: %f\n", total_t);
}