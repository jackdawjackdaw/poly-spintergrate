#include "find-boundary.h"
#include "boundary-fns.h"
#include <stdio.h>
#include <stdlib.h>


void get_boundary_scales(double* J, double *b1, double *b2, double *b3)
{
  
  int config;
  pt2BFun funcArr[20] = {&boundary_fn_1,
                         &boundary_fn_2,
                         &boundary_fn_3,
                         &boundary_fn_4,
                         &boundary_fn_5,
                         &boundary_fn_6,
                         &boundary_fn_7,
                         &boundary_fn_8,
                         &boundary_fn_9,
                         &boundary_fn_10,
                         &boundary_fn_11,
                         &boundary_fn_12,
                         &boundary_fn_13,
                         &boundary_fn_14,
                         &boundary_fn_15,
                         &boundary_fn_16,
                         &boundary_fn_17,
                         &boundary_fn_18,
                         &boundary_fn_19,
                         &boundary_fn_20
  };

  config = get_config_index_spin(J);
  if(config < 0){
    fprintf(stderr, "# find-boundary, cannot get config\n");
    exit(EXIT_FAILURE);
  }
  
  /** call the right function */
  funcArr[config](J, b1, b2, b3);
}
