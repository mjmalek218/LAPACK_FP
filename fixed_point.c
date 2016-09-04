#include "fixed_point.h"

/* Note that none of these functions return any overflow yet */

const int num_shift = precision << 4;

inline long fixed_to_reg(fp num)
{
  return num >> num_shift;
}

inline fp reg_to_fixed(long num)
{
  return num << num_shift;
}

inline fp fp_add(fp num1, fp num2)
{
  /* just add...pretty easy */
  return num1 + num2;
}

inline fp fp_mult(fp num1, fp num2)
{
  return (num1 * num2) >> num_shift;
}


// returns (first argument) / (second argument)
inline fp fp_div(fp num1, fp num2)
{
  return ((num1 << num_shift) / num2);
}
