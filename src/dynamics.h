#ifndef __INC_DYNAMICS__
#define  __INC_DYNAMICS__

void get_eom_full(double* j, double* j_eom);
void get_scalings(double* j, double* alpha, double* beta, double* gamma, double* wvol);
double wijk(double *jvec, int i, int j, int k)

#endif
