#include <math.h> 
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "fixed_point.h"
#include "fixed_point.c"
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

  //  else if (sizeof(A->data) != (A->rows * A->cols * sizeof(fp)))
  // {
  //  fprintf(stderr, "Error: matrix not correct size.\n");
  //  exit(0);
  //}
}

/* Allows easy access to a matrix using base-1 indexing. Make these get/set 
   functions inline to speed up time considerably: they are likely to be 
   deeply nested. No out of bounds checking: would be way too much overhead */
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

/* NOTE: We make the deliberate design decision to  */
struct matrix* init_matrix(size_t rows, size_t cols);
struct matrix* deep_copy(const struct matrix* B);
void free_matrix(struct matrix* A);

inline bool are_conformable(const struct matrix* A, const struct matrix* B);
inline bool same_dim(const struct matrix* A, const struct matrix* B);

struct matrix* transpose(const struct matrix* A);
struct matrix* add_mats(const struct matrix* A, const struct matrix* B);
struct matrix* naive_mat_mult(const struct matrix* A, const struct matrix* B);
struct matrix* row_concat(const struct matrix* A, const struct matrix* B);

inline void row_mult(struct matrix* inp, size_t i, fp s);
inline void row_add_mult(struct matrix* inp, size_t i, size_t j, fp s);
inline void switch_row(struct matrix* inp, size_t i, size_t j);
inline size_t 
locate_nonzero_col(const struct matrix* inp, size_t col, size_t starting_row);

//STOPPED AT NAIVDE MAT MULT. NEED TO GO BACK AND RE-IMPLEMENT
