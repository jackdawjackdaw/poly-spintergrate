#ifndef __config_fns__
#define __config_fns__

int get_config_index(double alpha, double beta, double gamma);
int get_config_index_spin(double* j);

typedef int (*pt2IneqFun)(double, double, double);

#endif
