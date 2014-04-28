#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynamics.h"
#include "fixed-point-iter.h"
#include "dynamics-eom-54.h"
#include "config-fns.h"

#include "find-boundary.h"

extern double zLastStep[13];
extern int failedCount;


/**
 * ccs, cec24@phy.duke.edu
 * 04.04.2014
 * 
 * integrate the system, reads an initial config from stdin and then
 * goes ahead and chugs away using the fixed point midpoint update scheme
 * 
 * 24.04.2014
 * issue - results dont seem to be consistent with varying dt
 * 
 * usage: 
 * reads an input configuration of the first 4 spins, j1x, j1y ... j4x, j4y, j4z from stdin
 * integrates the system up to tstop printing summary variables to stdout and the actual spin configurations
 * to 'spin-traj.dat'.
 *
 * The time step and stop time can be set as the first two command line arguments. Time steps > 0.1 seem to cause
 * floating point exceptions.
 */

double findlowest(double a, double b, double c)
{
    double of_a_b = a < b ? a : b;
    return of_a_b < c ? of_a_b : c;
}

 
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
  // was using 0.001 as the default
  double dt = 0.01;
  // when to stop
  double tstop = 1.0; 

  /* boundary scales, should be small when we get near one */
  double b1, b2, b3; 
  
  double alpha = 0.0, beta = 0.0, gamma = 0.0, wvol = 0.0;
  FILE *fptr = fopen("spin-traj.dat", "w");
  /* how often to print output */
  double output_time = 0.05;
  
  int nstep = 0; //(int)(tstop/dt);
  int print_interval = 0; //(int)(output_time/dt);
  int count = 0;

  int confNames[20] = {54, 53, 52, 51, 43, 42, 41, 35, 34, 32, 31, 25, 24, 23, 21, 15, 14, 13, 12};
  
  int config; 

  /**
   * process some trivial command line stuff 
   */
  
  /** read arg1 -> dt, arg2 -> tstop */
  if(argc > 1){
    dt = atof(argv[1]);
  }
  if(argc > 2){
    tstop = atof(argv[2]);
  }

  nstep = (int)(tstop/dt);
  print_interval = (int)(output_time/dt);
  
  printf("# dt %lf, tstop %lf, nstep %d\n", dt, tstop, nstep);

  /** print out the first step and also clear up some global accumulators */
  printf("0.0 ");
  for(i = 1; i < 13; i++){
    scanf("%lf", &jin);
    jvec[i] = jin;
    printf("%lf ", jvec[i]);
    
    zprev[i] = 0.0; // init this at the same time
    zLastStep[i] = 0.0; // this is a global in fixed-point-iter.c
  }
  printf("\n");

  failedCount = 0;
  
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


  /** dynamics loop here */
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

      get_norms(jvec, norms);
      for(i = 0; i<4; i++)
        printf("%lf ", norms[i]);

      
      config = get_config_index_spin(jvec);
      if(config >= 0){
        printf("%d", config);
      } else {
        printf("%d", config);
      }

      get_boundary_scales(jvec, &b1, &b2, &b3);
      printf(" %lf", findlowest(b1,b2,b3));
      printf("\n");

      fprintf(fptr,"%lf ", time);
      for(i = 1; i < 13; i++)
        fprintf(fptr, "%lf ", jvec[i]);
      fprintf(fptr, "\n");
      
    }
    count++;
  } 

  fclose(fptr);

  printf("# failed steps: %d\n", failedCount);
  
  return(EXIT_SUCCESS);
}
