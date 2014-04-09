#include "config-fns.h"
#include "find-config.h"
#include "dynamics.h"


/** 
 * usees the functions defined from MM in find-config.c 
 * to match up a set of scalings with the correct configuration
 * oh what a palava 
 */
int get_config_index(double alpha, double beta, double gamma)
{

  pt2IneqFun funcArr[20] = {&test_config_1,
                            &test_config_2,
                            &test_config_3,
                            &test_config_4,
                            &test_config_5,
                            &test_config_6,
                            &test_config_7,
                            &test_config_8,
                            &test_config_9,
                            &test_config_10,
                            &test_config_11,
                            &test_config_12,
                            &test_config_13,
                            &test_config_14,
                            &test_config_15,
                            &test_config_16,
                            &test_config_17,
                            &test_config_18,
                            &test_config_19,
                            &test_config_20
  };

  int i;

  for(i = 0; i < 20; i++){
    if(funcArr[i](alpha, beta, gamma)){
      return i;
    }
  }
  
  return -1;
}


/* wraps up the scalings calculation and the config index into a single fn */
int get_config_index_spin(double* j)
{
  double alpha, beta, gamma, wvol;
  get_scalings(j, &alpha, &beta, &gamma, &wvol);
  //printf("# scalings: %lf %lf %lf %lf\n", alpha, beta, gamma, wvol);
  return(get_config_index(alpha, beta, gamma));
}
