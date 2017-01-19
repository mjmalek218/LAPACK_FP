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
#define MAX_LENGTH 10

/* print a matrix to the console */
void print_matrix(const matrix* A)
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

  printf("\n\n");  if (!test__
  test__add_mats();
}

/* Shouldn't rely on more basic functions to perform the computation.  */
bool test__init_matrix()
{
  /* Go through various edge cases*/
  matrix* test_mat = init_matrix(0, 0);

  /* This should print garbage */
}

bool test__free_matrix()
{

}

bool test__

/* returns true if test is valid: false otherwise */
bool test__naive_transpose()
{
  /* seed random */
  //  srand(time(NULL));

  size_t rows = 5;
  size_t cols = 5;
  int i,j = 0; //iterators

  /* first test matrix of all zeros and see if it still zeros */
  matrix* Z = init_matrix(rows, cols);

  matrix* dummy_mat; 
  print_matrix(Z);

  // DELETE DELETE
  printf("\ntest\n");
  fflush(stdout);   
  // DELETE DELETE


  /* Now compute the result of the transpose */
  naive_transpose(Z, dummy_mat); 

  

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
  matrix* R = init_matrix(rows, cols);
  
  for (i = 1; i <= rows; i++)
    {
      for (j = 1; j <= cols; j++)
	{
	  set_elem(R, i, j, (fp) (rand() % MAX_LENGTH));
	}
    }

  naive_transpose(R, dummy_mat); 
  
  for (i = 1; i <= cols; i++)
    {
      for (j = 1; j <= rows; j++)
	{
	  if (get_elem(dummy_mat, i, j) != get_elem(R, j, i))
	    return false;
	}
    }



  /* finally test a 1x1 matrix */
  matrix* ONE = init_matrix(1, 1);
  naive_transpose(ONE, dummy_mat);

  print_matrix(dummy_mat);

  free_matrix(Z);
  free_matrix(dummy_mat);
  free_matrix(R);

  return true;
}  


/* test addition */


/* test multiplication */


/* write tests for *every* single function  */
int main()
{
  /* Really only want to hear anything if a failure
     has occurred. Keep this in mind in testing.
     
     Also many of these tests will employ "eye-ball" 
     testing and thus bugs may not be immediately detectable
     via the true/false output of the function  

  */

  printf("\n\nBEGIN TESTING init_matrix()\n\n");

  if (!test__init_matrix())
    printf("\ninit_matrix() failed.\n"); 

  printf("\n\nEND TESTING init_matrix()\n\n");

  printf("\n\nBEGIN TESTING init_matrix()\n\n");

  if (!test__free_matrix())
    printf("free_matrix() failed.");

  printf("\n\nBEGIN TESTING init_matrix()\n\n");

  if (!test__reset_matrix())
    printf("reset_matrix() failed.");

  printf("\n\nBEGIN TESTING init_matrix()\n\n");

  if (!test__is_valid())
    printf("is_valid() failed.");

  printf("\n\nBEGIN TESTING init_matrix()\n\n");

  if(!test__accessors())
    print("One of the basic accessor functions failed");
  
  printf("\n\nBEGIN TESTING init_matrix()\n\n");
  
  if (!test__deep_copy())
    printf("deep_copy() failed.");
  
  printf("\n\nBEGIN TESTING init_matrix()\n\n");
  
  if (!test__are_conformable())
    printf("are_conformable() failed.");
  
  if (!test__naive_transpose())
    printf("naive_tranpose() failed.");

  if (!test__add_mats())
    printf("add_mats() failed.");

  if (!test__same_dim())
    naive_transpose();

  if (!test__
  test__add_mats();

  test__row_mult();

  test__row_add_mult();

  test__switch_row();

  
}



