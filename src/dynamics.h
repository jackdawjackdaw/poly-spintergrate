#ifndef __INC_DYNAMICS__
#define  __INC_DYNAMICS__

void get_eom_full(double* j, double* j_eom);
void get_scalings(double* j, double* alpha, double* beta, double* gamma, double* wvol);
double wijk(double *jvec, int i, int j, int k);

double ham_54(double alpha, double beta, double gamma, double wvol);
double get_volume(double* j);

void get_norms(double*j, double* norms);
  

#endif
