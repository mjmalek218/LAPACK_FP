#define precision 2 // number of decimal places 
#include <math.h>

/* This file outlines function to perform with fixed-point arithmetic on financial data
   for precise outputs/results. Include decimal precision AS AN ARGUMENT. Built to deal
   with financial data.  
*/

/* These should probably also all be defined to be inline functions since they 
   could be embedded deep in a large loop. */

typedef long fp; 

inline long fixed_to_reg(fp num);
inline fp reg_to_fixed(long num);

/* arithmetic. for subtraction just multiply by -1 to avoid confusion. */
inline fp add(fp num1, fp num2);
inline fp mult(fp num1, fp num2);
inline fp div(fp num1, fp num2);





