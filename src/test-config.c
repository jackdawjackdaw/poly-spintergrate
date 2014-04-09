#include <stdio.h>
#include <stdlib.h>
#include "find-config.h"
#include "config-fns.h"

int main (int argc, char* argv[]){
  double alpha, beta, gamma;
  int config;

  
  int confNames[20] = {54, 53, 52, 51, 43, 42, 41, 35, 34, 32, 31, 25, 24, 23, 21, 15, 14, 13, 12};

  
  while(scanf("%lf %lf %lf", &alpha, &beta, &gamma) != EOF){
    config = get_config_index(alpha, beta, gamma);
    if(config > 0){
      printf("%lf %lf %lf %d\n", alpha, beta, gamma, confNames[config]);
    } else { // just print a zero where we can't find the bit
      printf("%lf %lf %lf %d\n", alpha, beta, gamma, config);
    }
  }
 
  return EXIT_SUCCESS; 
}
