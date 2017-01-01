/* This is a test suite for the functions in matrix.c. 
   Trying to make it comprehensive.  */
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "matrix.c" 
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

/* This is the maximum size of a single dimension for our test matrices */
#define MAX_LENGTH 1000

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
	  printf("%10.2f ", (float)get_elem(A, i, j));
	}
      printf("\n");
    }

  printf("\n\n");
}

/* returns true if test is valid: false otherwise */
bool test_transpose()
{
  /* seed random */
  srand(time(NULL));

  size_t rows = rand() % MAX_LENGTH;
  size_t cols = rand() % MAX_LENGTH;
  int i,j = 0; //iterators

  /* first test matrix of all zeros and see if it still zeros */
  struct matrix* Z = init_matrix(rows, cols);

  struct matrix* dummy_mat;

  print_matrix(Z);


  for (i = 1; i <= rows; i++)
    {
      for (j = 1; j <= cols; j++)
	{
	  set_elem(Z, i, j, (fp)0);
	}
    }

  /* Now compute the result of the transpose */
  transpose_i7(Z, dummy_mat); 

  print_matrix(Z);
  print_matrix(dummy_mat);

  for (i = 1; i <= cols; i++)
    {
      for (j = 1; j <= rows; j++)
	{
	  if (get_elem(Z, i, j) != 0)
	    return false;
	}
    }

  /* Now create a matrix full of random integers to test */
  struct matrix* R = init_matrix(rows, cols);
  
  for (i = 1; i <= rows; i++)
    {
      for (j = 1; j <= cols; j++)
	{
	  set_elem(R, i, j, (fp) (rand() % MAX_LENGTH));
	}
    }

  transpose_i7(R, dummy_mat); 
  
  for (i = 1; i <= cols; i++)
    {
      for (j = 1; j <= rows; j++)
	{
	  if (get_elem(dummy_mat, i, j) != get_elem(R, j, i))
	    return false;
	}
    }



  /* finally test a 1x1 matrix */
  struct matrix* ONE = init_matrix(1, 1);
  transpose_i7(ONE, dummy_mat);

  print_matrix(dummy_mat);

  free_matrix(Z);
  free_matrix(dummy_mat);
  free_matrix(R);

  return true;
}  


/* test addition */


/* test multiplication */


/* need to free all the test data */
int main()
{
  struct matrix* mat = init_matrix(5, 5);

  print_matrix(mat);

  free_matrix(mat); 
}



