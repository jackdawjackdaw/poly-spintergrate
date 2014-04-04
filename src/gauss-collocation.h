#ifndef _inc_gauss_co_
#define _inc_gauss_co_
#include "gsl/gsl_vector.h"
#include "gsl/gsl_matrix.h"


void setup_gauss_tables_2(void);
void setup_gauss_tables_3(void);
void setup_gauss_tables_4(void);
void setup_gauss_working_memory(void);

void free_tables(void);

void equistage_init(gsl_matrix *zinit);

int hamf(gsl_vector *z, gsl_vector *fvec, long double epsilon);

int fixed_point_iter_step(gsl_vector *yn, gsl_matrix* z_in, gsl_matrix *z_next, 
													double dt, long double epsilon);

double matrix_diff(gsl_matrix* z1, gsl_matrix* z2);

void print_state_z(gsl_matrix *z);

int iterate_gauss(gsl_vector *y_now, gsl_vector* y_next, double dt, double epsilon_grad);

/**
 * globals for the collocation coeffs
 */
double **aTab;
double *cVec, *bVec, *dVec;
int sOrder;

/** 
 * worker vars so we don't alloc everything all the time
 */
gsl_vector *pos_temp;
gsl_vector *f_temp;

/**
 * store the z_final we converge to each step so we can start from it next time
 */
gsl_matrix *zprev_step_1;
gsl_matrix *zprev_step_2;


#endif
