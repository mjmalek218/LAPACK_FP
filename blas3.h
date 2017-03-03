/* Implem

   THIS IS THE MOST IMPORTANT ONE TO IMPLEMENT. 


   ALSO to get used to the naming conventions utilized in BLAS, all functions we choose 
   to implement should use the names they use
*/

/* 
   OK so to match the convention they use, we will pass in 
   a pointer to the struct data rather than the entire
   matrix object itself whenever we want to perform a 
   computation here. 
 */

/* 

   Computes C = alpha * A * B and related operations. 

As a side note for what is about to come, it's interesting how they capitalize
the name of arguments in the comments b

Parameters:

   Input, char TRANSA


"char transa":

"char transb":

"int m":

"int n":

"int k":

"double alpha":

"double a[]":

"int 

   
*/
void dgemm ( char transa, char transb, int m, int n, int k, 
  double alpha, double a[], int lda, double b[], int ldb, double beta, 
  double c[], int ldc );



/* Performs B = A * B, or B = B*A, A triangular, B rectangular */
void dtrmm ( char side, char uplo, char transa, char diag, int m, int n, 
  double alpha, double a[], int lda, double b[], int ldb );

/* solves A*X = */
void dtrsm ( char side, char uplo, char transa, char diag, int m, int n, 
  double alpha, double a[], int lda, double b[], int ldb );

void sgemm ( char transa, char transb, int m, int n, int k, 
  float alpha, float a[], int lda, float b[], int ldb, float beta, 
  float c[], int ldc );
void strmm ( char side, char uplo, char transa, char diag, int m, int n, 
  float alpha, float a[], int lda, float b[], int ldb );
void strsm ( char side, char uplo, char transa, char diag, int m, int n, 
  float alpha, float a[], int lda, float b[], int ldb );
