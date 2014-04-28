#ifndef __INC_FIND_BNDRY__
#define __INC_FIND_BNDRY__

typedef void (*pt2BFun)(double*, double*, double*, double*);
void get_boundary_scales(double* J, double *b1, double *b2, double *b3);

#endif
