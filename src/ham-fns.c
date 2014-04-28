#include "ham-fns.h"
#include "ham-all.h"
#include "config-fns.h"

/**
 * return the ham at a given point
 */

double get_ham_all(double* J)
{
  int config;
  pt2HamFun funcArr[20] = {
    &ham_1,
    &ham_2,
    &ham_3,
    &ham_4,
    &ham_5,
    &ham_6,
    &ham_7,
    &ham_8,
    &ham_9,
    &ham_10,
    &ham_11,
    &ham_12,
    &ham_13,
    &ham_14,
    &ham_15,
    &ham_16,
    &ham_17,
    &ham_18,
    &ham_19,
    &ham_20
  };

  config = get_config_index_spin(J);
  //printf("\nham config: %d\n", config); 

  if(config < 0){
    return(0.0); // no volume for broken configs
  }

  return(funcArr[config](J));
  
}
