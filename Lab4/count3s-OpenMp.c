/*
   See "Principles of Parallel Programming", page 195.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *array;
int length;
int count;

int count3s()
{
   int i;
   count = 0;
   int count_p = 0;                        /*** needed to move this declaration ***/
#pragma omp parallel firstprivate(count_p) /*** need firstprivate() ***/
   {
#pragma omp for /*** don't need schedule(static) private(i) ***/
      for (i = 0; i < length; i++)
      {
         if (array[i] == 3)
         {
            count_p++;
         }
      }
#pragma omp critical
      {
         count += count_p;
      }
   }
   return count;
}

int main(int argc, char *argv[])
{
   int i;
   length = 100000000; /*  2^20  */

   array = calloc(length, sizeof(int));

   /* initialize the array with random integers between 0 and 9 */
   srand(time(NULL)); /* seed the random number generator with current time */
   for (i = 0; i < length; i++)
   {
      array[i] = rand() % 10;
   }

double start_t_1 = clock();
   count3s();  /* do the actual calculation */

   printf("The number of 3's is %d\n", count);
   double end_t_1 = clock();
   double total_t_1 = (end_t_1 - start_t_1) / CLOCKS_PER_SEC;

   /* As a test, let us count 3's the slow, serial way. */
   double start_t_2 = clock();
   count = 0;
   for (i = 0; i < length; i++)
      if (array[i] == 3)
         count++;
   printf("The number of 3's is %d\n", count);
   double end_t_2 = clock();
   double total_t_2 = (end_t_2 - start_t_2) / CLOCKS_PER_SEC;

   printf("\n\n");
   printf("OpenMp total time taken: %f\n", total_t_1);
   printf("Serial total time taken: %f\n", total_t_2);
   return 0;
}