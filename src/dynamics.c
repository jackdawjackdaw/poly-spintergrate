#include <math.h>
#include "mdefs.h"

#include "dynamics.h"
#include "dynamics-eom-54.h"

/**
 * general functions which are helpful for the dynamics
 * spin indices are counted from 1, to match up with the MM definitions
 * 
 */

/**
 * we are numerically solving: D[j, t] = f(j)
 * this function provides f(j)
 *
 * @param j, a 13 element array, with entries 1..12 = {j1, ..., j12}
 * @param j_eom, a 13 element array,
 * 
 * @return j_eom <- f(j), entries 1..12 are populated
 */
void get_eom_full(double* j, double* j_eom)
{
  /** 
   * this is ugly, in the future we want to use a fnptr array here, one for each config class
   * but at least its unrolled..
   */
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

/** 
 * compute the hamiltonian in the 54 coords, using the scalings 
 */
double ham_54(double alpha, double beta, double gamma, double wvol)
{
  return( (sqrt(2.0)/3.0) * ( sqrt( fabs(alpha*beta*gamma))
                              - sqrt(fabs( (alpha-1)*(beta-1)*(gamma-1))) ) * sqrt(fabs(wvol)));
}

/* wrap ham_54 to give the vol from a j list */
double get_volume(double* j)
{
  double alpha = 0.0, beta = 0.0, gamma = 0.0, wvol = 0.0;
  get_scalings(j, &alpha, &beta, &gamma, &wvol);
  return(ham_54(alpha, beta, gamma, wvol));
}

/** 
 * compute the canonical scalings from a given spin config
 * 
 */
void get_scalings(double* j, double* alpha, double* beta, double* gamma, double* wvol)
{
  double denom = wijk(j,1,2,3);
  
  *alpha = -1.0*wijk(j,2,3,4) / denom;
  *beta = wijk(j,1,3,4)/ denom;
  *gamma = -1.0*wijk(j,1,2,4)/denom;
  *wvol = denom;
}

/**
 * compute the norms of the spins for debugging
 */
void get_norms(double*j, double* norms) 
{
  int i;
  for(i = 0; i < 4; i++){
    norms[i] = sqrt(pow(j[(i)*3+1],2) + pow(j[(i)*3+2],2)+ pow(j[(i)*3+3],2));
  }
}

/**
 * compute wijk from the given set of spins
 * 
 * wijk = J_i . J_j \cross J_k
 *
 * a.b \cross c = -a2 b1 c0 + a1 b2 c0 + a2 b0 c1 - a0 b2 c1 - a1 b0 c2 + a0 b1 c2
 */
double wijk(double *jvec, int i, int j, int k)
{
  double j_vec_i[3];
  double j_vec_j[3];
  double j_vec_k[3];
  int count;

  for(count = 0; count < 3; count++){
    j_vec_i[count] = jvec[3*(i-1)+count+1];
    j_vec_j[count] = jvec[3*(j-1)+count+1];
    j_vec_k[count] = jvec[3*(k-1)+count+1];
  }

  /* printf("%lf %lf %lf\n", j_vec_i[0], j_vec_i[1], j_vec_i[2]); */
  /* printf("%lf %lf %lf\n", j_vec_j[0], j_vec_j[1], j_vec_j[2]); */
  /* printf("%lf %lf %lf\n", j_vec_k[0], j_vec_k[1], j_vec_k[2]); */
  
  return(  -1*j_vec_i[2] * j_vec_j[1] * j_vec_k[0] 
           + j_vec_i[1] * j_vec_j[2] * j_vec_k[0] 
           + j_vec_i[2] * j_vec_j[0] * j_vec_k[1]
           - j_vec_i[0] * j_vec_j[2] * j_vec_k[1]
           - j_vec_i[1] * j_vec_j[0] * j_vec_k[2]
           + j_vec_i[0] * j_vec_j[1] * j_vec_k[2]);
}
