#ifndef __INC_DYNAMICS__
#define  __INC_DYNAMICS__

void get_eom_full(double* j, double* j_eom);
void get_scalings(double* j, double* alpha, double* beta, double* gamma, double* wvol);
double wijk(double *jvec, int i, int j, int k);

double ham_54(double alpha, double beta, double gamma, double wvol);
double get_volume(double* j);

void get_norms(double*j, double* norms);
  
double three_vec_triple_prod(double* vec_i, double* vec_j, double* vec_k);
double three_vec_norm(double *vec);
double three_vec_dot(double *v1, double* v2);
void three_vec_cross(double* v1, double* v2, double* result);
double signed_angle(double* avec, double* bvec, double* dirn);

double get_km_phase_space(double* jvec, double* zvec);

#endif
