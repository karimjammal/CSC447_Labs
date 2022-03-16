#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int * array;
int length;
int count;

int main(int argc, char *argv[])
{
   int i;
   length = 10000000;  /*  2^20  */

   array = calloc(length, sizeof(int));

   /* initialize the array with random integers between 0 and 9 */
   srand(time(NULL));  /* seed the random number generator with current time */
   for(i = 0; i < length; i++)
   {
      array[i] = rand()%10;
   }

   count = 0;

   clock_t start_t = clock();
   for(i = 0; i < length; i++)
      if(array[i] == 3)
         count++;
   clock_t end_t = clock();

   printf("The number of 3's is %d\n", count);

    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken: %f\n", total_t);

   return 0;
}