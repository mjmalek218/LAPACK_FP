/* This file will include a variety of algorithms for solving linear
   matrix systems of the form Ax = b, where notation is canonical.  */

/* Given a matrix, returns its reduced row-echelon form using gauss-jordan elimination */
matrix Gauss_Jordan_Reduce(matrix mat);



/* Given a matrix, returns solutions to the corresponding homogenous system. */
matrix solve_homog(matrix mat);



/* Given a matrix M and an appropriate vector b (encoded as a matrix), returns the solution 
   to Mx = b using a rudimentary method.  */
matrix basic_solve(matrix M, matrix b);

