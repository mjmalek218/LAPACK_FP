/* NEED TO WRITE TEST SUITE FOR THIS GARBAGE TODO TODO TODO
******************************************************************************************

D SADASDSADSADSADSADSADSADSADASDASDASDASD */



/* Contains operations for fixed_point arithmetic. 

   Not can probably re-use this file for other projects.

   This is as recommended in section B.6 of the Pintos Directory

   Notation (given by Pintos documentation): 

   -- x and y are fixed-point numbers

   -- n is an integer

   -- fixed-pointer numbers are in signed p.q format where p+q = 31

   NOTE: Arithmetic operators are used in lieu of the simpler shift 
         operators due to unpredictable behavior on negative #'s

	 Actually...it seems as though 2's complement preserves 
	 even negative numbers under left-shifting unless there
         is overflow

   WARNING: This implementation assumes arithmetic right shifting for the underlying 
            implementation. The C compiler could very well implement logical shifting:
            nothing is required by any standard 

 */

/*  NEED TO ALSO IMPLEMENT COMPLEX FIXED POINT */ 

#include <inttypes.h>

/* Define the desired level of fractional precision...for now we use the example's 14
   fractional bits.  */
#define FRAC_P 14

/* note we use signed here. 


   THINK: I want to be able to effortlessly convert between 64 bit fixed point
   and 32 bit. I need to determine how exactly to do this, but I want it to
   simply involve changing a line in the macro-definition top of the file
*/
typedef int32_t fp;

/* Also define complex numbers, which are just pointers to an array of size 2.
   Not really a magic number as */
typedef fp complex_fp[2];

inline min(fp x, fp y)
{
  return (x < y) ? x : y;
}

inline max(fp x, fp y)
{
  return (x < y) ? y : x;
}

inline fp int_to_fp(int32_t);
inline int32_t fp_to_int(int32_t);
inline fp add_fp(fp, fp);
inline fp mult_fp(fp, fp);
inline fp div_fp(fp, fp);



inline fp int_to_fp(int32_t n)
{
  return n << FRAC_P;
}

/* Most convenient way to do this is probably to perform the  */
inline fp int_to_complex_fp(int32_t real, int32_t imag)
{


}

/* This attempts to maximize precision by rounding to the nearest, at
   the expensive of extra computational cost. We don't implement the 
   simpler version of always rounding towards 0...for now */
inline int32_t fp_to_int(int32_t x)
{
  if (x >= 0)
    return (x + (1 << (FRAC_P - 1))) >> FRAC_P;

  else 
    return (x - (1 << (FRAC_P - 1))) >> FRAC_P;
}

/* To subtract, multiply values by -1 using the 'mult_fp' functon then add. */
inline fp add_fp(fp x, fp y)
{
  return x + y;
}

/* The simplest way to implement this is to employ 64 bit integers.
   Even 32 bit machines allow for these extensions, as demonstrated
   by the casting we use. */
inline fp mult_fp(fp x, fp y)
{
  return (fp) ((( (int64_t) x) * y) >> FRAC_P);  
}

inline fp div_fp(fp x, fp y)
{
  return (fp) ((( (int64_t) x) << FRAC_P) / y);
}


inline factorial(size_t n)
{
  size_t product = 1;
  
  while (n > 0)
    {
      product *= n 
      n--;
    }

  return product;
}


/* The following functions we implement via Taylor Polynomial approxinations, for
   now. This involves computing a bound on our error value/remainder */

/* This will compute exponents using fixed point arithmetic to the desired precision. 
   Remember that fp is a 32 bit representation. For right now we only implement
   with natural base, but the extension should be simple (need to examine its
   numerical stability). */
fp exp_fp()
{

  /* Pre-compute the max/min values for every  */
  MAX_Q = ;

  /* easy...just set this to 0 because it basically is */
  MIN_Q = 0;




}

complex_fp exp_complex_fp()
{


}

/* Again for now we only have the natural base as an implementation */
fp log_fp()
{

}

complex_fp log_complex_fp()
{


}


/* */
fp sin_fp()
{

}


complex_fp sin_complex_fp()
{

}


//...need to do cos too
