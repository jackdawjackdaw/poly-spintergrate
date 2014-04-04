#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynamics.h"
#include "fixed-point-iter.h"
#include "dynamics-eom-54.h"


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
  double j_eom_vec[13];
  double j_next_vec[13]; // do one fixedPointSeep
  double zprev[13];
  double time = 0.0;
  double dt = 0.01;
  double alpha, beta, gamma, wvol;
  int print_interval = 4;
  int nstep = 1;
  int count = 0;

  printf("0.0 ");
  for(i = 1; i < 13; i++){
    scanf("%lf", &jin);
    jvec[i] = jin;
    printf("%lf ", jvec[i]);
    
    zprev[i] = 0.0; // init this at the same time
  }
  printf("\n");

  get_scalings(jvec, &alpha, &beta, &gamma, &wvol);
  printf("# scalings: %lf %lf %lf %lf\n");

  while(count < nstep){
    fixed_point_iterate(jvec, j_next_vec, dt);
    time = count*dt;
    

    for(i =1 ; i < 13; i++)
      jvec[i] = j_next_vec[i];  // have to swap the vectors around

    if((count % print_interval) == 0){
      printf("%lf ", time);
      for(i =1 ; i < 13; i++)
        printf("%lf ", jvec[i]);
      printf("\n");
    }

    
    count++;
  } 

  return(EXIT_SUCCESS);
}
