#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynamics.h"
#include "fixed-point-iter.h"
#include "dynamics-eom-54.h"
#include "config-fns.h"


/**
 * ccs, cec24@phy.duke.edu
 * 04.04.2014
 * 
 * integrate the 54 system, reads an initial config from stdin and then
 * goes ahead and chugs away using the fixed point midpoint update scheme
 */
 
/**
 * the spins are indexed from 1-12 so we have to 
 * alloc a 13 length array
 */
int main(int argc, char * argv[]){
  int i;
  double jin;
  double jvec[13]; // mm references vectors from 1 not zero...
  double j_next_vec[13]; // do one fixedPointSeep
  double zprev[13];
  double norms[4];
  double zvec[4];
  double time = 0.0;
  double dt = 0.01;
  double alpha = 0.0, beta = 0.0, gamma = 0.0, wvol = 0.0;
  int print_interval = 4;
  int nstep = 1000;
  int count = 0;

  int confNames[20] = {54, 53, 52, 51, 43, 42, 41, 35, 34, 32, 31, 25, 24, 23, 21, 15, 14, 13, 12};
  
  int config; 

  printf("0.0 ");
  for(i = 1; i < 13; i++){
    scanf("%lf", &jin);
    jvec[i] = jin;
    printf("%lf ", jvec[i]);
    
    zprev[i] = 0.0; // init this at the same time
  }
  printf("\n");
  
  get_scalings(jvec, &alpha, &beta, &gamma, &wvol);
  printf("# scalings: %lf %lf %lf %lf\n", alpha, beta, gamma, wvol);
  printf("# volume: %lf\n", get_volume(jvec));

  get_norms(jvec, norms);
  printf("# norms: ");
  for(i = 0; i<4; i++)
    printf("%lf ", norms[i]);
  printf("\n");
  
  get_km_phase_space(jvec, zvec);
  printf("# km: ");
  for(i = 0; i<4; i++)
    printf("%lf ", zvec[i]);
  printf("\n");

  config = get_config_index_spin(jvec);
  if(config >= 0){
    printf("# config %d\n", confNames[config]);
  } else {
    printf("# config broken! %d\n", config);
  }
  
  while(count < nstep){
    fixed_point_iterate(jvec, j_next_vec, dt);
    time = count*dt;
    

    for(i =1 ; i < 13; i++)
      jvec[i] = j_next_vec[i];  // have to swap the vectors around

    if((count % print_interval) == 0){
      
      printf("%lf ", time);
      get_scalings(jvec, &alpha, &beta, &gamma, &wvol);
      printf("%lf %lf %lf %lf", alpha, beta, gamma, wvol);
      printf(" %lf ", get_volume(jvec));

      get_km_phase_space(jvec, zvec);
      for(i = 0; i<4; i++)
        printf("%lf ", zvec[i]);

      config = get_config_index_spin(jvec);
      if(config >= 0){
        printf("%d", confNames[config]);
      } else {
        printf("%d", config);
      }
      printf("\n");

      
    }

    
    count++;
  } 

  return(EXIT_SUCCESS);
}
