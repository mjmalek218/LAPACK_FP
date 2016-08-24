#include <math.h> 
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* TODO: 

   --Implement error checking with set jumps and long jumps

   --Need to read chapter 5 and apply all basic optimizations

   --implement parallelized routines. This is critical for matrix computations.  
*/

/* This file will encode various matrix structs/operations, in 2D, which will ideally 
   be implemented using fast algorithms. The runtimes for each will be listed in the 
   comments. */

/* Each matrix will be a matrix of floats, which should be more than enough precision. 
   May consider later modification. Also contains size of the matrix. */
struct matrix
{
  unsigned int rows;
  unsigned int cols;

  /* the actual matrix. just an int for now. may code a library to deal with
     fixed point arithmetic.  */
  fp data[rows][cols]; 

} matrix;

/* checks to see if a matrix is valid 
   (sensible row/column numbers and data not NULL).

   IF NOT: prints error message and exits the entire program
 */
void is_valid(struct matrix* A)
{
  if (A == NULL)
    {
      fprintf(stderr, "Error: data object NULL");
      exit(0);
    }

  else if (A->rows <= 0)
    {
      fprintf(stderr, "Error: invalid number of rows");
      exit(0)
    }

  else if (A->cols <= 0)
    {
      fprintf(stderr, "Error: invalid number of cols");
      exit(0);
    }

}

/* Initializes a matrix to 0 values */
void init_matrix_zero(struct matrix* A, int rows, int cols)
{
 if (A == NULL)
   {
     fprintf(stderr, "Error: data object NULL");
     exit(0);
   }

  // error checking
  else if (rows == 0)
    {
      fprintf(stderr, "Error: invalid number of rows");
      exit(0)
    }
  else if (cols == 0)
    {
      fprintf(stderr, "Error: invalid number of cols");
      exit(0);
    }

  unsigned int i,j;
  A->rows = rows;
  B->cols = cols;

  for(i = 0; i < rows; i++)
    {
      for(j = 0; j < cols-1; j+=2)
	{
	  // row major order + loop unrolling
	  A->data[i][j + 1] = 0;
	  A->data[i][j] = 0;
	}
    }
}

/* Initializes first matrix to the second matrix */
void init_matrix_spec(struct matrix* A, struct matrix* B)
{
  if (A == NULL)
    {
      fprintf(stderr, "Error: First arg NULL");
      exit(0);
    }

  is_valid(B);
  
  unsigned int i,j;
  A->rows = rows;
  B->cols = cols;

  for(i = 0; i < rows; i++)
    {
      for(j = 0; j < cols-1; j+=2)
	{
	  A->data[i][j + 1] = B->data[i][j + 1];
	  A->data[i][j] = B->data[i][j];
	}
    } 
}


/* Given two matrices in the order A and then B, checks to see if AB makes sense.
   Since this is a check function...code is so small makes sense to make it
   inline. */
inline bool are_conformable(struct matrix* A, struct matrix* B)
{
  return (A->cols == B->rows);
} 

inline bool same_dim(struct matrix* A, struct matrix* B)
{
  return (A->cols == B->cols && A->rows == B->rows);
}

/* we do this by copying the matrix and then swapping accordingly.
   if we copy row by row a significant number of cache misses 
   may be avoided. Once this is done...we swap in memory. Note
   we need to confirm that the input matrix is NULL so far...as in
   it has yet to be initialized */

// TODO: OPTIMIZE THIS
void transpose(matrix* result, matrix* A)
{
  result = init_matrix_zero(result, A->cols, A->rows);
  unsigned int i,j;

  /* we swap indices. note this suffers from poor
     locality but it seems as though every approach will tbh */
  for (i = 0; i < A->rows; i++)
    {
      for (j = 0; j < A->cols; j++
      result->data[j][i] = A->data[i][j];	
    }
}

/* Adds two matrices together. Notice the sensitivity to row-major
   ordering of the matrix in main memory/caches */
matrix* add_mats(struct matrix* A, struct matrix* B)
{

  /* First *need* to check to see if A and B are of same dim...
     and sensible. This involves error-catching.  */
  unsigned int i,j;
  unsigned int m = A->rows;
  unsigned int n = A->cols;

  if (!same_dim(A,B))
    {
      fprintf(stderr, "Error: matrices to add are NOT comformable");
      exit(1);
    }

  /* declare and initialize components of the return value */
  struct matrix* sum;     
  sum->rows = m;
  sum->cols = n;
  

  /* row major order, with loop-unrolling.. computing two elements per cycle  */
  for (i = 0; i < m; i++)
    {
      /* Unrolling the column operations is all that makes sense...otherwise
         locality in the cache will be disrupted. */
      for (j = 0; j < n-1; j+=2)
	{
	  sum->data[i][j] = A->data[i][j] + B->data[i][j];
	  sum->data[i][j+1] = A->data[i][j+1] + B->data[i][j+1]; 
	}
    }
    
  return result;

}

/* returns AB via O(n^3) naive matrix multiplication time */
matrix* naive_mat_mult(struct matrix* A, struct matrix* B)
{

  /* valid input error checking */
  is_valid(A);
  is_valid(B);

  if (!are_conformable(A,B))
    {
      fprintf(stderr, "Error: matrices to add are NOT comformable");
      exit(0);
    }
  /* end valid input error checking */

  struct matrix* result = init_matrix(result, A->rows, B->cols);
  unsigned int i,j;

  /* bulk of function */
  for (i = 0; i < result->rows; i++)
    {
      for(j = 0; j <  result->cols; j++)
	{
	  for (k = 0; k < A->cols; k++)
	    {
	      result->data[i][j] = mult(A->data[i][k], B->data[k][j]);
	    }
	}
    }
  
}

/* Multiplies two matrices together using the Strassen algorithm. */
matrix strass_mat_mult(struct matrix* A, struct matrix* B)
{
  /* First step is to copy the matrices into  */  
}

/* Given two matrices, concatenates them row-wise */
matrix* row_concatenate(matrix* A, matrix* B)
{
  if (A->rows != B->rows)
    {
      fprintf(stderr, "Error: matrices to concat are NOT correct dim");
      exit(0);
    }

  unsigned int m = A->rows;

  /* if it works create an appropriate matrix and return */
  struct matrix* result;
  unsigned int i,j;

  result->cols = A->cols + B->cols;
  result->rows = m;

  for (i = 0; i < m; i++)
    {
    for (j = 0; j < A->cols; j++)
      {
	result->data[i][j] = A->data[i][j];
      }
    }

  for (i = 0; i < m; i++)
    {
      for(j = A->cols; j < A->cols + B->cols; j++)
	{
	  result->data[i][j] = B->data[i][j - A->cols];
	}
    }

  return result;
}

/* returns the input matrix but with the ith row multiplied by s */
inline void row_mult(matrix* inp, unsigned int i, fp s)
{
  if (i >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  unsigned int k;

  for (k = 0; k < inp->cols; inp++)
    {
      inp->data[i][k] *= s;
    }
}


/* adds s*row_i to row_j */
inline void row_add_mult(matrix* inp, unsigned int i, unsigned int j, fp s)
{
  if (i >= inp->rows || j >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  unsigned int k;

  for (k = 0; k < inp->cols; inp++)
    {
      inp->data[j][k] += s * inp->data[i][k];
    }
}

/* switches row i with row j*/
inline void switch_row(matrix* inp, int i, int j)
{
  if (i >= inp->rows || j >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  unsigned int k;
  fp temp;

  for (k = 0; k < inp->cols; inp++)
    {
      temp = inp->data[j][k];
      inp->data[j][k] = inp->data[i][k];
      inp->data[i][k] = temp;
    }
}


/* Given a matrix, returns its row-echelon form using gaussian elimination */
matrix* Gauss_Eliminate(matrix mat)
{
  struct matrix* result = init_matrix(result, &mat);
  
  unsigned int curr_col = 0;

}

/* Given a matrix, returns its reduced row-echelon form using gauss-jordan elimination */
matrix Gauss_Jordan_Reduce(matrix mat);

/* Given a matrix, returns its rank */
int rank(matrix mat);

/* Given a matrix, returns solutions to the corresponding homogenous system. */
matrix solve_homog(matrix mat);

/* Given a matrix M and an appropriate vector b (encoded as a matrix), returns the solution 
   to Mx = b using a rudimentary method.  */
matrix basic_solve(matrix M, matrix b);

/* Computes the determinant of M */
fp det(matrix M);

/* on going issues with C:

   --does not support function overloading on arguments
   --does not support operator overloading
   --no objects/classes (difficult to organize larger projects)
*/


