#include <math.h> 
#include <stdbool.h>

/* TODO: 

   --Implement error checking

   --Need to read chapter 5 and apply all basic optimizations

   --implement parallelized routines 
*/

/* This file will encode various matrix structs/operations, in 2D, which will ideally 
   be implemented using fast algorithms. The runtimes for each will be listed in the 
   comments. */

/* Each matrix will be a matrix of floats, which should be more than enough precision. 
   May consider later modification. Also contains size of the matrix*/
typedef struct matrix
{
  int num_rows;
  int num_cols;

  /* the actual matrix. just a float for now. */
  float mat[m][n]; 

} matrix;

/* Given two matrices in the order A and then B, checks to see if AB makes sense*/
bool are_conformable(matrix A, matrix B); 

/* Adds two matrices together */
matrix add_mats()
{

}
/* Multiplies two matrices together */
matrix mult_mats


/* Inverts a square matrix */



/* Given two matrices, concatenates them */
matrix concatenate

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


/* on going issues with C:

   --does not support function overloading on arguments
   --does not support operator overloading
   --no objects/classes (difficult to organize larger projects)
*/
