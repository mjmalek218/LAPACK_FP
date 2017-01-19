#include <math.h> 
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "fixed_point.h"
#include <stdlib.h>
#include "system_spec.h"
#include <pthread.h>

/*
   Data is fixed point, precision specified in fixed_point.h. 
   Also contains size of the matrix, and data of the matrix
   is allocated on the heap. 
*/

typedef struct matrix
{
  size_t rows;
  size_t cols;

  /* The actual matrix. */
  fp* data; 

  /* Boolean to determine if the matrix has been initialized. 
     0 if no, 1 if yes. The free_matrix function reverts this 
     to 0. DO NOT ALTER OUTSIDE OF FREE/INIT/RESET FUNCTIONS. */
  bool is_initialized;
} matrix;

/* checks to see if a matrix is valid 
   (sensible row/column numbers, data not NULL, and matrix is correct size).

   IF NOT: prints error message and exits the entire program

   NOTE: I know of no way to implement a way to check for the size of the 
         corresponding array independently of the row/column sizes provided:
	 so for right now I must be exceedingly careful in determining how
	 the pointer memory is allocated for this individual array element. 
	 This is noted in the README.
 */
void is_valid(const struct matrix* A)
{
  if (A == NULL)
    {
      fprintf(stderr, "Error: data object NULL\n");
      exit(0);
    }

  else if (A->rows == 0)
    {
      fprintf(stderr, "Error: invalid number of rows\n");
      exit(0);
    }

  else if (A->cols == 0)
    {
      fprintf(stderr, "Error: invalid number of cols\n");
      exit(0);
    }

  else if (A->data == NULL)
    {
      fprintf(stderr, "Error: data not initialized.\n");
      exit(0);
    }
}

/* Allows easy access to a matrix using base-1 indexing. Make these get/set 
   functions inline to speed up time considerably: they are likely to be 
   deeply nested. Out of bounds checking is also performed (NOT as of 
   right now though...maybe this should be changed...could slow
   things down though by a factor).  */
inline fp get_elem(const struct matrix* A, size_t row, size_t col)
{
  return A->data[(row - 1) * A->cols + (col - 1)];
}

inline void set_elem(struct matrix* A, size_t row, size_t col, fp new_elem)
{
  A->data[(row - 1) * A->cols + (col - 1)] = new_elem;
}

inline size_t get_rows(const struct matrix* A)
{
  return A->rows;
} 

inline size_t get_cols(const struct matrix* A)
{
  return A->cols;
}

inline void set_rows(struct matrix* A, size_t new_rows)
{
  A->rows = new_rows;
}

inline void set_cols(struct matrix* A, size_t new_cols)
{
  A->cols = new_cols;
}


/* Functions to be defined... */

/* NOTE: We make the deliberate design decision to pass the output in (via pointer)
         as opposed to having the functions return it. Discussion in
         Design Doc. */
struct matrix* init_matrix(size_t rows, size_t cols);
void deep_copy(const struct matrix*, struct matrix*);
void free_matrix(struct matrix* A);
void resize_matrix(struct matrix* B, size_t rows, size_t cols);

inline bool are_conformable(const struct matrix* A, const struct matrix* B);
inline bool same_dim(const struct matrix* A, const struct matrix* B);

/* Destination for output is always the last argument. 

   WARNING: All these methods completely overwrite memory associated with 
            the output matrix 
*/
void naive_transpose(const struct matrix* A, struct matrix* B);
void add_mats(const struct matrix* A, const struct matrix* B, struct matrix* C);
void naive_mat_mult(const struct matrix* A, const struct matrix* B, struct matrix* C);
void row_concat(const struct matrix* A, const struct matrix* B, struct matrix* C);

inline void row_mult(struct matrix* inp, size_t i, fp s);
inline void row_add_mult(struct matrix* inp, size_t i, size_t j, fp s);
inline void switch_row(struct matrix* inp, size_t i, size_t j);
inline size_t locate_nonzero_col(const struct matrix* inp, 
				 size_t col, size_t starting_row);


/* Following functions are optimized for the x1 carbon target machine */
void transpose_i7(const struct matrix*, struct matrix*);
void strass_mat_mult_i7(struct matrix* result, const struct matrix* A, const struct matrix* B);

