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
struct matrix* init_matrix(size_t rows, size_t cols)
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
  set_rows(A, rows);
  set_cols(A, cols);

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

  set_rows(A, get_rows(B));
  set_cols(A, get_cols(B));

  A->data = (fp*) malloc(get_rows(B) * get_cols(B) * sizeof(fp));

  for(i = 1; i <= get_rows(B); i++)
    {
      for(j = 1; j <= get_cols(B); j++)
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
  return (get_cols(A) == get_rows(B));
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
struct matrix* transpose(const struct matrix* A)
{
  is_valid(A);

  struct matrix* result = init_matrix(get_cols(A), get_rows(A));
  size_t i,j;

  /* we swap indices. note this suffers from poor
     locality but it seems as though every 'easy' approach will tbh */
  for (i = 1; i <= get_rows(A); i++)
    {
      for (j = 1; j <= get_cols(A); j++)
	{
	  set_elem(result, j, i,  get_elem(A, i, j));	
	}
    }

  return result;
}

/* Returns the sum of two matrices. Notice the sensitivity to row-major
   ordering of the matrix in main memory/caches */
struct matrix* add_mats(const struct matrix* A, const struct matrix* B)
{

  /* First *need* to check to see if A and B are of same dim...
     and sensible. This involves error-catching.  */
  is_valid(A);
  is_valid(B);

  if (!same_dim(A,B))
    {
      fprintf(stderr, "Error: matrices to add are NOT the same dimension");
      exit(0);
    }

  size_t i,j;
  size_t m = get_rows(A);
  size_t n = get_cols(A);

  struct matrix* sum = init_matrix(m,n);

  /* initialize components of the return value */
  set_rows(sum, m);
  set_cols(sum, n);
  
  /* row major order */
  for (i = 1; i <= m; i++)
    {
      /* Unrolling the column operations is all that makes sense...otherwise
         locality in the cache will be disrupted. */
      for (j = 1; j <= n; j++)
	{
	  set_elem(sum, i, j, fp_add(get_elem(A, i, j), get_elem(B, i, j)));
	}
    }
    
  return sum;
}

/* returns AB via O(n^3) naive matrix multiplication time */
struct matrix* naive_mat_mult(const struct matrix* A, const struct matrix* B)
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
  struct matrix* product = init_matrix(get_rows(A), get_cols(B));
  size_t i,j,k;

  fp inner_sum = 0;

  /* bulk of function */
  for (i = 1; i <= get_rows(product); i++)
    {
      for(j = 1; j <= get_cols(product); j++)
	{
	  for (k = 1; k <= get_cols(A); k++)
	    {
	      inner_sum += fp_mult(get_elem(A,i,k), get_elem(B,k,j));
	    }

	  set_elem(product, i, j, inner_sum);
	  inner_sum = 0;
	}
    }

  return product;
  
}

/* Multiplies two matrices together using the Strassen algorithm. */
void strass_mat_mult(struct matrix* result, const struct matrix* A, const struct matrix* B)
{
  /* First step is to copy the matrices into  */

  //TODO
  
}

/* Given two matrices, returns their row-wise concatenation */
struct matrix* row_concat(const struct matrix* A, const struct matrix* B)
{
  is_valid(A);
  is_valid(B);

  if (get_rows(A) != get_rows(B))
    {
      fprintf(stderr, "Error: matrices to concat are NOT correct dim");
      exit(0);
    }

  struct matrix* result = init_matrix(get_rows(A), get_cols(A) + get_cols(B));

  size_t i,j;

  /* FIX THIS...LOCALITY COULD BE BETTER */
  for (i = 1; i <= get_rows(A); i++)
    {
    for (j = 1; j <= get_cols(A); j++)
      {
	set_elem(result, i, j, get_elem(A, i, j));
      }
    }

  for (i = 1; i <= get_rows(B); i++)
    {
      for(j = get_cols(A)+1; j <= get_cols(A) + get_cols(B); j++)
	{
	  set_elem(result, i, j, get_elem(B, i, j - get_cols(A)));
	}
    }

  return result;
}

/* returns the input matrix but with the ith row multiplied by s */
inline void row_mult(struct matrix* inp, size_t i, fp s)
{
  is_valid(inp);

  if (i >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  size_t k;

  for (k = 1; k <= get_cols(inp); inp++)
    {
      set_elem(inp, i, k, get_elem(inp, i, k) * s);
    }
}


/* adds s*row_i to row_j */
inline void row_add_mult(struct matrix* inp, size_t i, size_t j, fp s)
{
  is_valid(inp);

  if (i >= get_rows(inp) || j >= get_rows(inp))
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  size_t k;

  for (k = 1; k <= get_cols(inp); inp++)
    {
      set_elem(inp, j, k, s*get_elem(inp, i, k) + get_elem(inp, j, k));
    }
}

/* switches row i with row j*/
inline void switch_row(struct matrix* inp, size_t i, size_t j)
{
  if (i >= inp->rows || j >= inp->rows)
    {
      fprintf(stderr, "Error: index out of bounds");
      exit(0);
    }

  size_t k;
  fp temp;

  for (k = 1; k <= get_cols(inp); k++)
    {
      temp = get_elem(inp, j, k);
      set_elem(inp, j, k, get_elem(inp, i, k));
      set_elem(inp, i, k, temp);
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

   while(i <= get_rows(inp))
     {
       // could have gotten rid of boolean operation but want clearer code 
       if (get_elem(inp, i, col) != 0)
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
/*       if (result->data[curr_row][curr_col] !=n 1) */
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
struct matrix Gauss_Jordan_Reduce(struct matrix mat);

/* Given a matrix, returns its rank */
int rank(struct matrix mat);

/* Given a matrix, returns solutions to the corresponding homogenous system. */
struct matrix solve_homog(struct matrix mat);

/* Given a matrix M and an appropriate vector b (encoded as a matrix), returns the solution 
   to Mx = b using a rudimentary method.  */
struct matrix basic_solve(struct matrix M, struct matrix b);

/* Computes the determinant of M */
fp det(struct matrix M);

/* on going issues with C:

   --does not support function overloading on arguments
   --does not support operator overloading
   --no objects/classes (difficult to organize larger projects)
*/


