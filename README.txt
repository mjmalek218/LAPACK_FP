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
 
	  The reasons for this choice are several fold:   

	  --leads to memory leaks if the input matrix 
