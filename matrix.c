#include "matrix.h"

/* TODO: 

   -- Implement error checking with set jumps and long jumps

   -- Need to read chapter 5 and apply all basic optimizations

   -- implement parallelized routines. This is critical for matrix computations.  

   -- CREATE COMPANION LATEX FILE ANALYZING RUN-TIMES OF ALL ALGOS 

   -- NEED TO GO THROUGH AND MAKE SURE OUTPUT IS PASSED AS A POINTER ARGUMENT

   -- one bug to be aware about is having a matrix of different dimension than 
      that is stated. make sure to avoid this. 
   
*/

/* This file will encode various matrix structs/operations, in 2D, which will ideally 
   be implemented using fast algorithms. The runtimes for each will be listed in the 
   comments. */

/* Allocates necessary heap memory. actual matrix memory is garbage. */
struct matrix* init_mat(size_t rows, size_t cols)
{
  // error checking
  if (rows == 0)
    {
      fprintf(stderr, "Error: invalid number of rows");
      exit(0);
    }

  else if (cols == 0)
    {
      fprintf(stderr, "Error: invalid number of cols");
      exit(0);
    }

  struct matrix* A = malloc(sizeof(struct matrix));

  /* checks to see if the allocation worked */
  if (A == NULL)
    {
      fprintf(stderr, "Error: struct could not be allocated.");
      exit(0);
    } 

  size_t i,j;
  A->rows = rows;
  A->cols = cols;

  /* need to allocate the memory for the matrix */
  A->data = (fp*) malloc(rows * cols * sizeof(fp));

  /* again...need to check to see if the allocation worked */
  if (A->data == NULL)
    {
      fprintf(stderr, "Error: data array could not be allocated.");
      exit(0);
    }  

  return A;
}


/* performs a deep copy of the given matrix and returns a pointer to new data */
struct matrix* deep_copy(const struct matrix* B)
{
  is_valid(B);
 
  struct matrix* A = malloc(sizeof(struct matrix));
 
  size_t i,j;
  A->rows = B->rows;
  A->cols = B->cols;

  A->data = (fp*) malloc(rows * cols * sizeof(fp));

  for(i = 1; i != rows; i++)
    {
      for(j = 1; j != cols; j++)
	{
	  set_elem(A, i, j, get_elem(B, i, j));
	}
    } 
}

void free_matrix(struct matrix* A)
{
  /* first free the data */
  free(A->data);

  /* then the struct itself */
  free(A);

}

/* Given two matrices in the order A and then B, checks to see if AB makes sense.
   Since this is a check function...code is so small makes sense to make it
   inline. */
inline bool are_conformable(const struct matrix* A, const struct matrix* B)
{
  return (A->cols == B->rows);
} 

/* for addition or subtraction...or a host of other purposes */
inline bool same_dim(const struct matrix* A, const struct matrix* B)
{
  return (A->cols == B->cols && A->rows == B->rows);
}

/* we do this by copying the matrix and then swapping accordingly.
   if we copy row by row a significant number of cache misses 
   may be avoided. Once this is done...we swap in memory. Note
   we need to confirm that the input matrix is NULL so far...as in
   it has yet to be initialized */
struct matrix* transpose(const matrix* A)
{
  struct matrix* result = init_matrix(A->cols, A->rows);
  size_t i,j;

  /* we swap indices. note this suffers from poor
     locality but it seems as though every 'easy' approach will tbh */
  for (i = 0; i < A->rows; i++)
    {
      for (j = 0; j < A->cols; j++)
	result->data[j * result->cols + i] = A->data[i * A->cols + j];	
    }

  return result;
}

/* Returns the sum of two matrices. Notice the sensitivity to row-major
   ordering of the matrix in main memory/caches */
struct matrix* add_mats(const struct matrix* A, const struct matrix* B)
{

  /* First *need* to check to see if A and B are of same dim...
     and sensible. This involves error-catching.  */

  if (!same_dim(A,B))
    {
      fprintf(stderr, "Error: matrices to add are NOT the same dimension");
      exit(1);
    }

  size_t i,j;
  size_t m = A->rows;
  size_t n = A->cols;

 struct matrix* sum = init_matrix(m,n);

  /* initialize components of the return value */
  sum->rows = m;
  sum->cols = n;
  
  /* row major order */
  for (i = 0; i < m; i++)
    {
      /* Unrolling the column operations is all that makes sense...otherwise
         locality in the cache will be disrupted. */
      for (j = 0; j < n-1; j+=2)
	{
	  sum->data[i * n + j] = fp_add(A->data[i * n + j], B->data[i * n + j]);
	}
    }
    
  return result;
}

/* returns AB via O(n^3) naive matrix multiplication time */
void naive_mat_mult(struct matrix* result, const struct matrix* A, const struct matrix* B)
{
  /* valid input error checking */
  is_valid(A);
  is_valid(B);

  if (!are_conformable(A,B))
    {
      fprintf(stderr, "Error: matrices to multiply are NOT comformable");
      exit(0);
    }
  /* end valid input error checking */

  result = init_matrix_zero(result, A->rows, B->cols);
  size_t i,j;

  /* bulk of function */
  for (i = 0; i < result->rows; i++)
    {
      for(j = 0; j <  result->cols; j++)
	{
	  for (k = 0; k < A->cols; k++)
	    {
	      result->data[i * result->cols + j] = 
		fp_mult(A->data[i * A->cols + k], B->data[k * B->cols + j]);
	    }
	}
    }
  
}

/* Multiplies two matrices together using the Strassen algorithm. */
void strass_mat_mult(struct matrix* result, const struct matrix* A, const struct matrix* B)
{
  /* First step is to copy the matrices into  */  
}

/* Given two matrices, returns their row-wise concatenation */
struct matrix* row_concat(struct matrix* result, const struct matrix* A, const struct matrix* B)
{
  if (A->rows != B->rows)
    {
      fprintf(stderr, "Error: matrices to concat are NOT correct dim");
      exit(0);
    }

  struct matrix* result = init_matrix(A->rows, A->cols + B->cols);

  size_t i,j;

  for (i = 0; i < A->rows; i++)
    {
    for (j = 0; j < A->cols; j++)
      {
	result->data[i * result->cols + j] = A->data[i * A->cols + j];
      }
    }

  for (i = 0; i < B->rows; i++)
    {
      for(j = A->cols; j < A->cols + B->cols; j++)
	{
	  result->data[i * result->cols + j] = B->data[i * B->cols + j - A->cols];
	}
    }

  return result;
}

/* returns the input matrix but with the ith row multiplied by s */
inline void row_mult(matrix* inp, size_t i, fp s)
{
  if (i >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  size_t k;

  for (k = 0; k < inp->cols; inp++)
    {
      inp->data[i * inp->cols + k] *= s;
    }
}


/* adds s*row_i to row_j */
inline void row_add_mult(matrix* inp, size_t i, size_t j, fp s)
{
  if (i >= inp->rows || j >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  size_t k;

  for (k = 0; k < inp->cols; inp++)
    {
      inp->data[j * inp->cols + k] += s * inp->data[i * inp->cols + k];
    }
}

/* switches row i with row j*/
inline void switch_row(matrix* inp, size_t i, size_t j)
{
  if (i >= inp->rows || j >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  size_t k;
  fp temp;

  for (k = 0; k < inp->cols; inp++)
    {
      temp = inp->data[j * inp->cols + k];
      inp->data[j * inp->cols + k] = inp->data[i * inp->cols + k];
      inp->data[i * inp->cols + k] = temp;
    }
}

/* Locates the first non-zero element in a column. 
   If none is found...returns -1. Note there *could* be an error here if
   the matrix column dimension is MAX_UNSIGNED_INT + 1 (make sure not to 
   allocate such enormous matrices) */
inline size_t 
locate_nonzero_col(const struct matrix* inp, size_t col, size_t starting_row)
 {

   is_valid(inp);
   size_t i = starting_row;

   while(i < inp->rows)
     {
       // could have gotten rid of boolean operation but want clearer code 
       if (inp->data[i][col] != 0)
	 return i;
       else
	 i++;
     }
 
   return -1;
   
 }


/* /\* Given a matrix, returns its row-echelon form using gaussian elimination *\/ */
/* void Gauss_Eliminate(struct matrix* result, const struct matrix* mat) */
/* { */
 
/*   /\* make sure result is NOT NULL *\/ */
/*    if (A == NULL) */
/*    { */
/*      fprintf(stderr, "Error: data object NULL"); */
/*      exit(0); */
/*    } */

/*   /\* initialize it to the input matrix *\/ */
/*   init(result, mat); */

/*   size_t curr_col = 0; */
/*   size_t curr_row = 0; */
/*   size_t i = 0; */
/*   size_t next_piv, j; */

/*   while (curr_col < result->cols) */
/*     { */
/*       /\* First check for first non-zero pivot *\/ */
/*       next_piv = locate_nonzero_col(result, curr_col, curr_row); */
      
/*       if (next_piv == -1) */
/* 	{ */
/* 	  curr_col++; */
/* 	  continue; */
/* 	} */

/*       /\* otherwise if there is a non-zero element that is not this row... */
/*          switch it into this row *\/ */
/*       else if (next_piv != curr_row) */
/* 	{ */
/* 	  switch_row(result, curr_row, next_piv); */
/* 	}   */

/*       /\* By now we know we are dealing with a valid row *\/ */
/*       if (result->data[curr_row][curr_col] != 1) */
/* 	{ */
/* 	  row_mult(result, curr_row, fp_div(1, result->data[curr_row][curr_col])); */
/* 	} */
      
/*       /\* Now go throw and eliminate the remaining rows *\/ */
/*       for (j = curr_row; j < result->rows; j++) */
/* 	{ */
/* 	  if () */
/* 	} */

/*     } */
/* } */

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


