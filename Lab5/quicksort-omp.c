// Quicksort.cpp : Parallelized version of Quicksort algorithm.  
//
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000
int A[N];

int Partition (int p, int r)
{
  int x = A[p];
  int k = p;
  int l = r+1;
  int t;
  while (1)
  {
    do 
      k++;
    while ((A[k] <= x) && (k < r));
    do 
      l--;
    while (A[l] > x);

    while (k < l) {
      t = A[k];  A[k] = A[l];  A[l] = t;
      do k++; while (A[k] <= x);
      do l--; while (A[l] > x);
    }
    t = A[p];  A[p] = A[l];  A[l] = t;
    return l;
  }
}

void Quicksort(int p, int r)
{
  if (p < r) 
  {  int q = Partition(p, r);
  #pragma omp task firstprivate(p,q)
     Quicksort(p, q-1);
     Quicksort(q+1, r);
  }
}

void init_data()
{
  int i, x, y, t;
  for (i = 0; i < N; i++)
    A[i] = i;
  for (i = 0; i < N; i++) {
    x = rand()%N;
    y = rand()%N;
    t = A[y]; A[y] = A[x]; A[x] = t;
  }
}

int main(int argc, char* argv[])
{
  double start,stop;
  start = omp_get_wtime();
  init_data();
  for (int i = 0; i < N; i++) printf("%3d ",A[i]);
  printf("\n\n");
  #pragma omp parallel 
  {
  #pragma omp single nowait
  Quicksort(0, N-1);
  }
  for (int j = 0; j < N; j++) printf("%3d ",A[j]);
  stop = omp_get_wtime();
    printf("\nTotal time taken: %f\n",stop - start);
  return 0;
}