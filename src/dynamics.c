#include <math.h>
#include "mdefs.h"

#include "dynamics-eom-54.h"

/**
 * general functions which are helpful for the dynamics
 * spin indices are counted from 1, to match up with the MM definitions
 * 
 */

/**
 * we are numerically solving: D[j, t] = f(j)
 * this function provides f(j)
 *
 * @param j, a 13 element array, with entries 1..12 = {j1, ..., j12}
 * @param j_eom, a 13 element array,
 * 
 * @return j_eom <- f(j), entries 1..12 are populated
 */
void get_eom_full(double* j, double* j_eom)
  /** 
   * this is ugly, use a fnptr array here
   * but at least its unrolled..
   */
  j_eom[1] = eom_rhs_54_1(j);
  j_eom[2] = eom_rhs_54_2(j);
  j_eom[3] = eom_rhs_54_3(j);
  j_eom[4] = eom_rhs_54_4(j);
  j_eom[5] = eom_rhs_54_5(j);
  j_eom[6] = eom_rhs_54_6(j);
  j_eom[7] = eom_rhs_54_7(j);
  j_eom[8] = eom_rhs_54_8(j);
  j_eom[9] = eom_rhs_54_9(j);
  j_eom[10] = eom_rhs_54_10(j);
  j_eom[11] = eom_rhs_54_11(j);
  j_eom[12] = eom_rhs_54_12(j);        
}

