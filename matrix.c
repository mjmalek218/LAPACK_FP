#include <math.h> 
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

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
  int num_rows;
  int num_cols;

  /* the actual matrix. just an int for now. may code a library to deal with
     fixed point arithmetic.  */
  int data[m][n]; 

} matrix;

/* Initializes a matrix to certain values */
void init_matrix(struct matrix* A, int rows, int cols)
{
  

}

/* Sets two matrices equal */

/* Given two matrices in the order A and then B, checks to see if AB makes sense.
   Since this is a check function...code is so small makes sense to make it
   inline. */
inline bool are_conformable(struct matrix* A, struct matrix* B)
{
  return (A->num_cols == B->num_rows);
} 

inline bool same_dim(struct matrix* A, struct matrix* B)
{
  return (A->num_cols == B->num_cols && A->num_rows == B->num_rows);
}

/* Adds two matrices together. Notice the sensitivity to row-major
   ordering of the matrix in main memory/caches */
matrix add_mats(struct matrix* A, struct matrix* B)
{

  /* First *need* to check to see if A and B are of same dim...
     and sensible. This involves error-catching.  */
  int i,j;
  int m = A->num_rows;
  int n = A->num_cols;

  if (!same_dim(A,B))
    {
      fprintf(stderr, "Error: matrices to add are NOT comformable");
      exit(1);
    }

  /* declare and initialize components of the return value */
  struct matrix sum;     
  sum->num_rows = m;
  sum->num_cols = n;
  

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

matrix naive_mat_mult(struct matrix* A, struct matrix* B)
{
  struct matrix result = 

}

/* Multiplies two matrices together using the Strassen algorithm. */
matrix strass_mat_mult(struct matrix* A, struct matrix* B)
{
  


}


/* Inverts a square matrix */



/* Given two matrices, concatenates them */
matrix concatenate(matrix* A, matrix* B);

/* Given a matrix, returns its row-echelon form using gaussian elimination */
matrix Gauss_Eliminate(matrix mat);

/* Given a matrix, returns its reduced row-echelon form using gauss-jordan elimination */
matrix Gauss_Jordan_Reduce(matrix mat);

/* Given a matrix, returns its rank */
int rank(matrix mat);

/* Given a matrix, returns solutions to the corresponding homogenous system. */
int solve_homog(matrix mat);

/* Given a matrix M and an appropriate vector b (encoded as a matrix), returns the solution 
   to Mx = b using a rudimentary method.  */
int basic_solve(matrix M, matrix b);

/* Computes the determinant of M */
float det(matrix M);

/* on going issues with C:

   --does not support function overloading on arguments
   --does not support operator overloading
   --no objects/classes (difficult to organize larger projects)
*/


