#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** these are currently defined in dynamics-test.c 
 * which is populated by running splice["/path/to/dynamics-test.mc"] in the mathematica note book
 * very elegant
 */
extern double eom_rhs_54_1(double* J);
extern double eom_rhs_54_2(double* J);
extern double eom_rhs_54_3(double* J);
extern double eom_rhs_54_4(double* J);
extern double eom_rhs_54_5(double* J);
extern double eom_rhs_54_6(double* J);
extern double eom_rhs_54_7(double* J);
extern double eom_rhs_54_8(double* J);
extern double eom_rhs_54_8(double* J);
extern double eom_rhs_54_9(double* J);
extern double eom_rhs_54_10(double* J);
extern double eom_rhs_54_11(double* J);
extern double eom_rhs_54_12(double* J);

void get_eom_full(double* j, double* j_eom){
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

void fixed_point_step(double* jin, double* jout, double* zprev, double dt){
  double tdvec[13];
  double tdnorms[4];
  double tvec[13];
  double vecsum[13];
  int i;

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

  
  get_eom_full(tvec, jout);
  
  for(i = 0; i < 13; i++){
    jout[i] = 0.5 * dt*jout[i];
  }
  
}

void fixed_point_iterate(double* jin, double* jnext, double dt){
  int stepMax = 16;
  double eps = 1e-12;
  int nstep = 0;
  double zin[13];
  double znext[13];
  double diff = 1;
  int i;

  for(i = 1; i< 13; i++)
    zin[i] = 0.0;
  
  while(diff >= eps && nstep < stepMax){

    fixed_point_step(jin, znext, zin, dt);

    diff = 0.0;
    for(i = 1; i < 13; i++){
      diff += sqrt(pow(zin[i] - znext[i], 2)); /* compute the difference between steps*/
      zin[i] = znext[i]; /* and copy the array bits around */
    }
    nstep++;
  }
  
  for(i = 1; i < 13; i++){
    jnext[i] = 2*znext[i] + jin[i];
  }
}

int main(int argc, char * argv[]){
  int i;
  double jin;
  double jvec[13]; // mm references vectors from 1 not zero...
  double j_eom_vec[13];
  double j_next_vec[13]; // do one fixedPointSeep
  double zprev[13];
  double time = 0.0;
  double dt = 0.01;
  int print_interval = 4;
  int nstep = 10000;
  int count = 0;

  printf("0.0 ");
  for(i = 1; i < 13; i++){
    scanf("%lf", &jin);
    jvec[i] = jin;
    printf("%lf ", jvec[i]);
    
    zprev[i] = 0.0; // init this at the same time
  }
  printf("\n");


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
