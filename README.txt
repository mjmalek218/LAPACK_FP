Problems with existing libraries:


1. All use floating point basically instead of fixed_point, which results in 
   reduced numerical stability and is overkill for financial applications which
   only require/allow 'cent' level precision. 

2. Overbearing complexity 


SUMMARY:

The following is a computational library based upon matrices. 


DESIGN CHOICES:


       1. *Having functions alter matrices through pointer input 
          as opposed to returning them*, i.e. if we want to alter
	  a matrix A we perform:
	  
	  func(matrix* A, ...)

	  as opposed to

	  A = func(...).
 
	  The reason for this choice is several fold:   

	  --leads to memory leaks if the destination matrix is already allocated

	  --Prevents cascading of functions without resource leaks 

	  --Prevents the destination matrix from being an input itself without
	    a memory leak


       2. When input matrices are entered to a function, the function always
          clears them. We want to support entering in both intialized and
	  uninitialized matrices into these functions: by forcibly freeing
	  input matrices, we can simultaneously support both cases. 


       3. Along the Lines in (2), we assume that matrices are *always* initialized,
          so there is indeed memory to clear. This means whenever a matrix is declared,
	  it should also be initialized lest a segmentaiton fault occur upon attempting
 	  to free stack memory


       4. 1-Based Indexing of matrices. Just makes more sense to my mathematical
          intuition


       5. Including an "initialization" boolean in every matrix to determine
          if its memory has been freed or not. Since this is only modified by
	  *two* functions, init_matrix and free_matrix, it makes it easy to 
	  to debug memory management problems, in theory. There is a downside
	  to this: if the code is shipped this obviously leaves
	  an extrmeley vulnerable hole for discombobulation, but it is only
	  intended for personal usage so not too much of a problem. 
	  Also it requires more memory allocation for a given matrix, but in
	  theory this is made up later because it means I don't need to initialize
	  matrices immediately. 

       6. Including a "resize" function that works similarly to how

 
********************************************************

IMPLEMENTATION DISCUSSION (of interesting functions)


****

Core i7 Optimized Transpose: 

--For the implementation of this function, I used work from CSPP 


****

********************************************************


ONGOING ISSUES/QUESTIONS:

****

In matrix.h :

     Is there a way to check to make sure the allocated virtual memory pointed 
     to by the pointer is indeed the dimensionality, or at least size,
     implied by the row/column fields of the struct? Probably not in C but
     who knows

****

In general:

     No support of overloading functions on argument type/number. This
     leads to irritating organizational issues. 

****
