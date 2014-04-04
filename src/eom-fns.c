#include "eom-fns.h"


void get_eom_all(double *Jin, double* Jout, int config)
{
  pt2EomFun funcArr[20] = {
    &eom_rhs_1,
    &eom_rhs_2,
    &eom_rhs_3,
    &eom_rhs_4,
    &eom_rhs_5,
    &eom_rhs_6,
    &eom_rhs_7,
    &eom_rhs_8,
    &eom_rhs_9,
    &eom_rhs_10,
    &eom_rhs_11,
    &eom_rhs_12,
    &eom_rhs_13,
    &eom_rhs_14,
    &eom_rhs_15,
    &eom_rhs_16,
    &eom_rhs_17,
    &eom_rhs_18,
    &eom_rhs_19,
    &eom_rhs_20
  };

  /* now call the thing */
  funcArr[config](Jin, Jout);
}
