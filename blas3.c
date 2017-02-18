/* Implem

   THIS IS THE MOST IMPORTANT ONE TO IMPLEMENT. 


   ALSO to get used to the naming conventions utilized in BLAS, all functions we choose 
   to implement should use the names they use
*/



/* Rather than using *double* or *single* precision, which is evident in the names
   of these functions, I will use fixed point precision. So *all* the names
   are changed to begin with an 'f' char rather than 's' or 'd' */



void fgemm ( char transa, char transb, int m, int n, int k, 
  double alpha, double a[], int lda, double b[], int ldb, double beta, 
  double c[], int ldc );



/* Strassen */
