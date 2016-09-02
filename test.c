/* This is a test suite for the functions in matrix.c */
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "matrix.c" 

/* print a matrix to the console */
void print_matrix(struct matrix* A)
{
  is_valid(A);

  int i,j;

  printf("\n\n");

  for (i = 0; i < A->rows; i++)
    {
      for (j = 0; j < A->cols; j++)
	{
	  printf(".2% ", A->data[i][j]);
	}
      printf("\n");
    }

  printf("\n");
}

/* need to free all the test data */
int main()
{
  struct matrix* mat = init_matrix(mat, 5, 5);

  print_matrix(mat);

  free(mat); 
}



