#ifndef __INC_FIXED_POINT__
#define __INC_FIXED_POINT__

void fixed_point_step(double* jin, double* jout, double* zprev, double dt);
void fixed_point_iterate(double* jin, double* jnext, double dt);
#endif
