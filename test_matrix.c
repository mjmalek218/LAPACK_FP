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

/* This tests all basic memory allocation functions, as well as
   accessor functions. Just eye-ball tests should be sufficient  */
voiud test__basics_matrix()
{
  int i,j;

  /*
    ALREADY WENT THROUGH AND TESTED THESE: KEEP AS COMMENTED THOUGH

  printf("First we go through exactly three '0' edge case initializations. "
	 "These should all print errors\n");
  matrix* test_mat = init_matrix(0, 0);

  test_mat = init_matrix(3, 0);
  test_mat = init_matrix(0, 4);
  

  printf("Now we attempt to print the matrices. Again this should print "
         "an error.\n");
  print_matrix(test_mat);

  printf("To check the 'is_valid' function, we run it on this matrix now. This "
         "should print to standard error\n");
  
  is_valid(test_mat);

  printf("Now we attempt legitimate allocations. First free the memory.\n");

  free_matrix(test_mat); */


  printf("Now we initialize the same matrix to be 6x7. Print immediately "
         "to see what garbage values it takes on\n");

  matrix* test_mat = init_matrix(6, 7);

  print_matrix(test_mat);

  printf("The accessors for rows columns return: \n rows = %zd \n cols = %zd.\nThese"
	 " should be 6 and 7, respectively\n", 
	 get_rows(test_mat), get_cols(test_mat));

  printf("Now we cycle through the matrix and attempt to set each "
          "value to successive natural numbers, printed in row-major order:\n");
 

  for (i = 1; i <= get_rows(test_mat); i++)
    {
      for (j = 1; j <= get_cols(test_mat); j++)
	{
	  set_elem(test_mat, i, j, (i - 1) * get_cols(test_mat) + j);
	}
    }


  print_matrix(test_mat);

  printf("Now perform a deep copy of the previous matrix and print. Should "
          "be exactly the same output as before\n");

  matrix* test_mat_2;

  deep_copy(test_mat, &test_mat_2);

  print_matrix(test_mat_2);

  printf("Reset the matrix handle to a 2x5 matrix using the reset_matrix() function, "
         "and test to see if the result is valid. is_valid() "
         "should not output anything. We print the resulting matrix, which should yield "
         "aribitrary values\n");

  reset_matrix(test_mat, 2, 5);

  is_valid(test_mat);

  print_matrix(test_mat);

  printf("Finally, we perform a deep copy of the previous matrix and print "
          "before freeing.\n");


  deep_copy(test_mat, &test_mat_2);

  print_matrix(test_mat_2);

  free_matrix(test_mat);
  free_matrix(test_mat_2);

  return true;
}

/* tests naive transpose, optimized transpose (for core i7 cache) and
   addition functions. Again as for all these functions eye-ball
   tests should be sufficient  */
bool test__trans_add()
{
  size_t rows = 5;
  size_t cols = 3;
  int i,j; //iterators

  printf("First initialize a matrix to garbage values, and print. "
          "There should be 5 rows and 3 columns.\n");
  matrix* Z = init_matrix(rows, cols);
  
  print_matrix(Z);

  printf("Now compute the result of the transpose (in place) "
          "and print it.\n");

  naive_transpose(Z, Z);   

  print_matrix(Z);

  printf("Now reset the original matrix to a 2x3, "
          "set all the elements to row-wise successive natural "
          "numbers, and print. \n");

  reset_matrix(Z, 2, 3);

  for (i = 1; i <= get_rows(Z); i++)
    {
      for (j = 1; j <= get_cols(Z); j++)
	{
	  set_elem(Z, i, j, (i - 1) * get_cols(Z) + j);
	}
    }

  print_matrix(Z);
  
  naive_transpose(Z, Z); 
  
  printf("Now print the transpose of this matrix with naive_transpose.\n");

  print_matrix(Z);

  printf("Finally test a 1x1 matrix as an edge case. First "
         "reset the previous matrix to {1} and print");

  m = init_matrix(1, 1);
  naive_transpose(ONE, dummy_mat);

  print_matrix(dummy_mat);

  free_matrix(Z);
  free_matrix(dummy_mat);
  free_matrix(R);

  return true;
}  


/* test multiplication/supporting functions */
bool test__mult()
{


  return true;

}


/* write tests for *every* single function  */
int main()
{
  /* Really only want to hear anything if a failure
     has occurred. Keep this in mind in testing.
     
     Also many of these tests will employ "eye-ball" 
     testing and thus bugs may not be immediately detectable
     via the true/false output of the function  

  */
 

  printf("\n\nBEGIN TESTING INIT, FREE, RESET, IS_VALID, AND DEEP_COPY\n\n");

  test__basics_matrix();

  printf("\n\nEND TESTING INIT, FREE, RESET, IS_VALID, AND DEEP_COPY\n\n");


  printf("\n\nBEGIN TESTING TRANSPOSE AND ADD\n\n");

  test__trans_add();

  printf("\n\nEND TESTING TRANSPOSE AND ADD\n\n");

  

}



