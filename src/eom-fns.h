#ifndef _INC_EOM_FNS_
#define _INC_EOM_FNS_


typedef void (*pt2EomFun)(double*, double*);
void get_eom_all(double *Jin, double* Jout, int config);


#endif
