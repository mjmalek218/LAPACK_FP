#include <math.h> 
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "fixed_point.h"
#include <stdlib.h>


/* Each matrix will be a matrix of fixed point, of arbitrary precision. 
   May consider later modification. Also contains size of the matrix.

   Everything is to be allocated on the heap. */

struct matrix
{
  size_t rows;
  size_t cols;

  /* The actual matrix. */
  fp* data; 

};

/* checks to see if a matrix is valid 
   (sensible row/column numbers, data not NULL, and matrix is correct size).

   IF NOT: prints error message and exits the entire program
 */
void is_valid(const struct matrix* A)
{
  if (A == NULL)
    {
      fprintf(stderr, "Error: data object NULL");
      exit(0);
    }

  else if (A->rows == 0)
    {
      fprintf(stderr, "Error: invalid number of rows");
      exit(0);
    }

  else if (A->cols == 0)
    {
      fprintf(stderr, "Error: invalid number of cols");
      exit(0);
    }

  else if (A->data == NULL)
    {
      fprintf(stderr, "Error: data not initialized.");
      exit(0);
    }

  else if (sizeof(A->data) != (A->rows * A->cols * sizeof(fp)))
    {
      fprintf(stderr, "Error: matrix not correct size.");
      exit(0);
    }
}

/* Allows easy access to a matrix using base-1 indexing. Make these get/set 
   functions inline to speed up time considerably: they are likely to be 
   deeply nested. No out of bounds checking: would be way too much overhead */
inline fp get_elem(struct matrix* A, size_t row, size_t col)
{
  return A->data[(row - 1) * A->cols + (col - 1)];
}

inline void set_elem(struct matrix* A, size_t row, size_t col, fp new_elem)
{
  A->data[(row - 1) * A->cols + (col - 1)] = new_elem;
}

inline size_t get_rows(struct matrix* A)
{
  return A->rows;
} 

inline size_t get_cols(struct matrix* A)
{
  return A->cols;
}


/* Functions to be defined... */
struct matrix* init_mat(size_t rows
