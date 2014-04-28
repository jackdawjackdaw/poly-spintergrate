#include "fixed-point-iter.h"
#include "dynamics.h"
#include "config-fns.h"
#include "eom-fns.h"
#include <math.h>


#include <stdio.h>
#include <stdlib.h>

double zLastStep[13];
int failedCount;

/**
 * carry out a fixed point step, part of a loop to compute the new 
 * configuration
 * 
 * this uses the midpoint spin method described in the Mclaclahn paper,
 * the RK coeffs are not explicitly defined but they enter as the (1/2) in the final jout loop
 * 
 * \todo abstract the coeffs to butcher tables as in the gauss-collocation methods
 * 
 * @param jin (13 elt array) initial spin config (input)
 * @param jout (" ") next spin config (output)
 * @param zpred (" ") array used in the previous step of this iterative procedure
 * @param dt time step width 
 */
void fixed_point_step(double* jin, double* jout, double* zprev, double dt)
{
  double tdnorms[4];
  double tvec[13];
  double vecsum[13];
  double jtest[13], jtest2[13];
  double jfvecEuler[13];
  int i;
  int configIndex;
  int configIndexOrig;
  int configIndex2;

  for(i = 1; i < 13; i ++){
    vecsum[i] = jin[i] + zprev[i];
  }
  for(i = 0; i < 4; i++){
    tdnorms[i] = sqrt(pow(vecsum[(i)*3+1],2) + pow(vecsum[(i)*3+2],2)+ pow(vecsum[(i)*3+3],2));
  }
  
  tvec[1] = vecsum[1] / tdnorms[0];
  tvec[2] = vecsum[2] / tdnorms[0];
  tvec[3] = vecsum[3] / tdnorms[0];

  tvec[4] = vecsum[4] / tdnorms[1];
  tvec[5] = vecsum[5] / tdnorms[1];	
  tvec[6] = vecsum[6] / tdnorms[1];	

  tvec[7] = vecsum[7] / tdnorms[2];
  tvec[8] = vecsum[8] / tdnorms[2];	
  tvec[9] = vecsum[9] / tdnorms[2];	

  tvec[10] = vecsum[10] / tdnorms[3];
  tvec[11] = vecsum[11] / tdnorms[3];	
  tvec[12] = vecsum[12] / tdnorms[3];	

  
#ifdef SIMPLEMODE
  /* this runs only the 54 config */
  get_eom_full(tvec, jout);
#else
  /** 
   * we have to be careful here, we can't just use tvec, we need to use something 
   * like jout to estimate the config index and then do it...
   */
  configIndexOrig = get_config_index_spin(jin); // this is the index at the previous point

  if(configIndexOrig < 0){
    fprintf(stderr, "configIndexOrig broken\n");
    exit(EXIT_FAILURE);
  }
  
  /* convert the tvec back from being essentially a Z into a Y */
  for(i = 1; i < 13; i++){
    jtest[i] = 2.0*tvec[i] + jin[i];
  }

  // this is the index at the euler point, use this as our guess for what our actual midpoint will give us?
  //configIndex = get_config_index_spin(tvec); 
  configIndex = get_config_index_spin(jtest); 

  if(configIndex < 0 || configIndex2 < 0){
    fprintf(stderr, "projected config failed\n");
    get_eom_all(tvec, jout, configIndexOrig);
  } else {
    //printf("%d %d\n", configIndex, configIndex2);
    get_eom_all(tvec, jout, configIndex);
  }
  
#endif  
  
  for(i = 1; i < 13; i++){
    jout[i] = 0.5 * dt*jout[i];
  }
  
}

/**
 * computes a fixed midpoint method update step using the procedure designed for spin systems
 * 
 * @param jin (input) initial spin config
 * @param jnext (output) computed new spin config
 * @param dt time step width 
 */
void fixed_point_iterate(double* jin, double* jnext, double dt)
{
  /* loop here silently stops after this many attempts */
  int stepMax = 64; 
  /* minimal discrepancy, Harirer et al suggest something a little bigger than DOUBLE_EPS, see gauss-collocation.c */
  double eps = 1e-13; 
  int nstep = 0;
  double zin[13];
  double znext[13];
  double diff = 1;
  int i;

  /* initiate the fixed point search with the stupidest guess, (totally zero)
   * it would be more sensible to use the znext obtained in the last step 
   */
  for(i = 1; i< 13; i++){
    //zin[i] = 0.0;
    zin[i] = zLastStep[i];
  }
  
  while(diff >= eps && nstep < stepMax){

    fixed_point_step(jin, znext, zin, dt);

    diff = 0.0;
    for(i = 1; i < 13; i++){
      diff += sqrt(pow(zin[i] - znext[i], 2)); /* compute the difference between steps*/
      /* is it any faster to do this using *(zin+i) = *(znext + i)? */
      zin[i] = znext[i]; /* and copy the array bits around */
    }
    nstep++;
  }
  
  if(nstep >= stepMax){
    //fprintf(stderr, "step failed to converge eps %lf\n", log10(diff));
    failedCount++;
  }
  
  for(i = 1; i < 13; i++){
    /* this two here is the butcher C_12 coeff (i think)
     */
    jnext[i] = 2.0*znext[i] + jin[i];
    zLastStep[i] = znext[i];
  }
}
