/* Implem

   THIS IS THE MOST IMPORTANT ONE TO IMPLEMENT. 


   ALSO to get used to the naming conventions utilized in BLAS, all functions we choose 
   to implement should use the names they use
*/

/* This should be *all* that needs to be included here tbh */
#include fixed_point.h

/* 

   Rather than using *double* or *single* precision, which is evident in the names
   of these functions, I will use fixed point precision. So *all* the names
   are changed to begin with an 'f' char rather than 's' or 'd'

 */

     
/* 
   start doing this in the comments: whenever a function or parameter is mentioned
   in the comments, always capitalize it all evne though the actual name is
   lower case 
*/

/* 

   Also need to implement multi-threading here

*/

/* 

   Purpose:

     FGEMM computes C = alpha * A * B and related operations. 
   
   Discussion:

     FGEMM performs one of the matrix-matrix operations
     
      C := alpha * op ( A ) * op ( B ) + beta * C

     where op ( X ) = X    or   op ( X ) = X^T 
     (for now only real fixed point elements are implemented)

    ALPHA and BETA are scalars, and A, B, and C are matrices, with op ( A )
    an M by K matrix, op ( B ) a K by N matrix and C an N by N matrix. 

   Parameters:

     Input, char TRANSA, specifies the form of op ( A ) to be used in 
     the matrix multiplication as follows:
     'N' or 'n', op ( A ) = A.
     'T' or 't', op ( A ) = A^T.

     Input, char TRANSB, specifies the form of op ( B ) to be usd in 
     the matrix multiplication as follows:
     'N' or 'n', op ( B ) = B.
     'T' or 't', op ( B ) = B^T.

     Input, int M, the number of rows of the matrix op ( A ) and of the 
     matrix C. 0 <= M. 

     Input, int N, the number of clumns of the matrix op ( B ) and the 
     number of columns of the matrix C. 0 <= N.

     Input, int K, the number of columns of the matrix op ( A ) and the 
     number of rows of the matrix

     Input, fp ALPHA, the scalar multiplier
     for op ( A ) * op ( B ).

     Input fp A(LDA


*/

void fgemm ( char transa, char transb, int m, int n, int k, 
  fp alpha, fp a[], int lda, fp b[], int ldb, fp beta, 
  fp c[], int ldc )

{
  /* First we go through and */



}



/* Strassen algorithm implementation attempt, to be used as a supporting function
   for fgemm and other matrix multiplication functions in BLAS (whatever those
   may be tbh). 
*/


/* The arguments for multiplication here are A and B, with the result being stored
   in C. Interestingly enough in the BLAS implementations it seems as though the 
   second argument is where the matrix gets stored, so one is actually updated...*/

/* OK... what *should* be here is low-level matrix muliplication optimized for 
   the core-i7 cache, *NOT* the recursive strassen algo. *THAT* should be implemented
   in matrix.c and then call upon the blas implementations in its lowest level of 
   recursion. */
void strass_mult(matrix* A, matrix* B, matrix* C)



/* Multi-threaded optimized transpose routine.

   -- Inner most caches of core i7 is 32 kB. With this in mind, we operate upon 
      16 kB of source matrix and 16 kB of the destination matrix at once

   -- There are four cores total, so we limit the computation to 4 threads maximum

 */
void transpose_i7(const matrix* A, matrix* B)
{
  /* error input checking. Need to make sure A and B are the correct sizes. */
  is_valid(A);

  size_t s_rows = get_rows(A);
  size_t s_cols = get_cols(A);
  size_t net_size = s_rows * s_cols;

  /* s and d are the indices for which "block" we are in for the source
     and destination matrices in the iteration */
  size_t s;
  size_t d;

  
  size_t i;
  size_t j;

  size_t min_s;
  size_t min_d;

  /* For each element i in the source matrix, we can reverse engineer the 
     corresponding row and col in the destination matrix. These variables
     will hold the results of this reverse engineering on each iteration. */
  size_t dest_row;
  size_t dest_col;
   
  /* We create this array then operate on it independently of 
     the accessor functions. We need to do this to optimize 
     Cache memory. This is one of the few instances in which 
     we ignore the safety measures, but in general
     attempt to avoid it. */
  reset_matrix(B, s_cols, s_rows);
  const fp* source = A->data;
  
  /* Loop over blocks for source array */
  for (s = 1; s <= net_size; s += (L1D_SIZE/2))
    {
      min_s = min(net_size, s + L1D_SIZE/2);

      /* Loop over blocks for destination array */
      for (d = 1; d <= net_size; d+= (L1D_SIZE/2))
	{
	  min_d = min(net_size, d + L1D_SIZE/2);

	  for (i = s; i <= min_s; i++)
	    {
	      dest_col = i / s_cols + 1;
	      dest_row = (i-1) % s_cols +1;

	      /* Since we are iterating over blocks we *do* need
	         to compute the absolute index j inside the d 
	         range. */
	      j = dest_col + (dest_row-1) * s_rows;

	      /* We make sure to limit our editing to the data that is
	         already cached, attempting to minimize thrashing. */
	      if (j <= min_d)
		{
		  set_elem(B, dest_row, dest_col, get_elem(A, dest_col, dest_row));
		}

	    }
	}
    }
}

