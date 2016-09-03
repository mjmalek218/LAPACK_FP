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

  for (i = 1; i <= get_rows(A); i++)
    {
      for (j = 0; j <= get_cols(A); j++)
	{
	  printf(".2% ", get_elem(A, i, j));
	}
      printf("\n");
    }

  printf("\n");
}

/* need to free all the test data */
int main()
{
  struct matrix* mat = init_matrix(5, 5);

  print_matrix(mat);

  free(mat); 
}



