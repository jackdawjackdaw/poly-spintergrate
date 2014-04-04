/**
 * ccs, cec24@phy.duke.edu
 * 
 * implement gauss collocation steps
 * use iterative method to solve
 */
#include "gauss-collocation.h"

/**
 * 
 * consider an RK system 
 * ki = f(t_0 + c_i*h , y_0 + h \sum_j=1^{s} a_ij k_j)
 * y_1 = y_0 + h \sum_i=1^{s} b_i k_i
 * 
 * we can rewrite this as:
 * 
 * Z_in -  h \sum_{j=1}^{s} a_{ij}f(y_n + Z_{jn}) = 0, for i=1..s
 * y_n+1 = y_n + h \sum_{i=1}^{s} b_i f(y_n + Z_{in})
 * 
 *
 * To compute the values $Z_i$ that we need for each step, for a suitable initial 
 * guess Z_{in}^0 we iterate
 *
 * Z_{in}^{k+1} = h \sum_{j=1}^{s} a_ij f(y_n + Z_{jn}^k), for i = 1..s
 * 
 * for a small enough h this should converge to the correct Z quickly.
 *
 * some global values:
 * cVec, bVec, aTab -> butcher tables, cVec, bVec are length s, aTab is s by s
 * sOrder -> defines the size of the tables
 * 
 * external routines needed:
 * a function hamgradZ(z, f, eps) which is called by hamf, on return f is set to f(z) evaluated with a 
 * numerical gradient tolerance eps
 * 
 * define the vector d_i: which is useful for computing updates without additional functional evals
 * y_n+1 = y_n + d_i Z_{ni}
 * d_i = b_j a_ij^{-1} 
 */


// inits the butcher tables for s = 2
void setup_gauss_tables_2(void){
	int i;
	int ndimsY = 4;
	sOrder = 2;


	bVec = malloc(sizeof(double)*sOrder);
	cVec = malloc(sizeof(double)*sOrder);
	dVec = malloc(sizeof(double)*sOrder);


	aTab = malloc(sizeof(double*)*sOrder);
	for(i = 0; i < sOrder; i++)
		aTab[i] = malloc(sizeof(double)*sOrder);
	
	// fill in the values
	cVec[0] = 1.0/2.0 - sqrt(3)/6.0;
	cVec[1] = 1.0/2.0 + sqrt(3)/6.0;
	bVec[0] = 0.5; bVec[1] = 0.5;
	aTab[0][0] = 0.25; aTab[0][1] = 0.25 - sqrt(3)/6.0; 
	aTab[1][0] = 0.25 + sqrt(3)/6; aTab[1][1] = 0.25;
	dVec[0] = -1.732050807568877; dVec[1] = 1.732050807568877;

	setup_gauss_working_memory();	
}

// inits the butcher tables for gauss s = 3
/**
 * strangely there's an un-init memory warning that comes here which doesn't
 * show in the s=2 method
 */
void setup_gauss_tables_3(void){
	int i;
	int ndimsY = 4;
	sOrder = 3;

	bVec = malloc(sizeof(double)*sOrder);
	cVec = malloc(sizeof(double)*sOrder);
	dVec = malloc(sizeof(double)*sOrder);
	
	aTab = malloc(sOrder*sizeof(double *));

	if(aTab==NULL){
		fprintf(stderr, "# can't malloc aTab\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < sOrder; i++){
		aTab[i] = malloc(sizeof(double)*sOrder);
		if(aTab[i] == NULL){
			fprintf(stderr, "# can't malloc atab\n");
			exit(EXIT_FAILURE);
		}
	}
	
	cVec[0] = 0.5 - sqrt(15.0)/10.0;
	cVec[1] = 0.5;
	cVec[2] = 0.5 + sqrt(15.0)/10.0;

	bVec[0] = 5.0/18.0;
	bVec[1] = 4.0/9.0;
	bVec[2] = 5.0/18.0;

	dVec[0] = 1.66666666666667;
	dVec[1] = -1.333333333333333;
	dVec[2] =  1.666666666666667;
	
	aTab[0][0] = 5.0/36.0; 	
	aTab[1][0] = 5.0/36.0 + sqrt(15.0)/24;	
	aTab[2][0] = 5.0/36.0 + sqrt(15.0)/30;	

	aTab[0][1] = 2.0/9.0 - sqrt(15.0)/15.0; 
	aTab[1][1] = 2.0/9.0; 
	aTab[2][1] = 2.0/9.0 + sqrt(15.0)/15.0; 

	aTab[0][2] = 5.0/36.0 - sqrt(15.0)/30;
	aTab[1][2] = 5.0/36.0 - sqrt(15.0)/24;
	aTab[2][2] = 5.0/36.0;

	setup_gauss_working_memory();
}

// butcher tables for gauss s = 4
/**
 * from butchers ACM paper 
 */
void setup_gauss_tables_4(void){
	int i;
	int ndimsY = 4;
	sOrder = 4;
	// this is how butcher defines his constants
	double w1, w1p, w2, w2p;
	double w3, w3p, w4, w4p;
	double w5, w5p;

	w1 = 1.0/8.0 - sqrt(30)/(144.0);
	w1p = 1.0/8.0 + sqrt(30)/(144.0);
	
	w2 = 0.5*sqrt((15.0+2*sqrt(30.0))/(35.0));
	w2p = 0.5*sqrt((15.0-2.0*sqrt(30.0))/(35.0));
	
	w3 = w2*(1.0/6.0 + sqrt(30.0)/(24.0));
	w3p = w2p*(1.0/6.0 - sqrt(30.0)/(24.0));

	w4 = w2 * (1.0/21.0 + (5.0*sqrt(30.0))/(168.0));
	w4p = w2p * (1.0/21.0 - (5.0*sqrt(30.0))/(168.0));

	w5 = w2 - 2.0*w3;
	w5p = w2p - 2.0*w3p;
		

	bVec = malloc(sizeof(double)*sOrder);
	cVec = malloc(sizeof(double)*sOrder);
	dVec = malloc(sizeof(double)*sOrder);

	aTab = malloc(sOrder*sizeof(double *));

	if(aTab==NULL){
		fprintf(stderr, "# can't malloc aTab\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < sOrder; i++){
		aTab[i] = malloc(sizeof(double)*sOrder);
		if(aTab[i] == NULL){
			fprintf(stderr, "# can't malloc atab\n");
			exit(EXIT_FAILURE);
		}
	}
	
	cVec[0] = 0.5 - w2;
	cVec[1] = 0.5 - w2p;
	cVec[2] = 0.5 + w2p;
	cVec[3] = 0.5 + w2;

	bVec[0] = 2.0*w1;
	bVec[1] = 2.0*w1p;
	bVec[2] = 2.0*w1p;
	bVec[3] = 2.0*w1;

	dVec[0] = -1.64070532173926;
	dVec[1] = 1.21439396979858;
	dVec[2] = -1.214393969798578;
	dVec[3] = 1.640705321739257;

	aTab[0][0] = w1;
	aTab[1][0] = w1 - w3p + w4;
	aTab[2][0] = w1 + w3p + w4;
	aTab[3][0] = w1 + w5;

	aTab[0][1] = w1p - w3 + w4p;
	aTab[1][1] = w1p;
	aTab[2][1] = w1p + w5p;
	aTab[3][1] = w1p + w3 + w4p;

	aTab[0][2] = w1p - w3 - w4p;
	aTab[1][2] = w1p - w5p;
	aTab[2][2] = w1p;
	aTab[3][2] = w1p + w3 - w4p;

	aTab[0][3] = w1 - w5;

	aTab[1][3] = w1 - w3p - w4;
	aTab[2][3] = w1 + w3p - w4;
	aTab[3][3] = w1;

	setup_gauss_working_memory();
}

/**
 * this is called by the setup_gauss_tables routines
 */
void setup_gauss_working_memory(void)
{ 
	int ndimsY = 4;
	/** 
	 * these are used in the iterate steps
	 */
	pos_temp = gsl_vector_alloc(ndimsY);
	f_temp = gsl_vector_alloc(ndimsY);

	zprev_step_1 = gsl_matrix_alloc(sOrder, ndimsY);
	zprev_step_2 = gsl_matrix_alloc(sOrder, ndimsY);
	gsl_matrix_set_zero(zprev_step_1);
	gsl_matrix_set_zero(zprev_step_2);
}

/**
 * should be called when you're done to release all that lovely 
 * memory
 */
void free_tables(void)
{
	int i;
	free(bVec);
	free(cVec);
	free(dVec);
	for(i = 0; i < sOrder; i++)
		free(aTab[i]);
	free(aTab);
	gsl_vector_free(pos_temp);
	gsl_vector_free(f_temp);
	gsl_matrix_free(zprev_step_1);
	gsl_matrix_free(zprev_step_2);
}
	

// f = J \del H 
// \del = {dq1, dq2, dp1, dp2}
// J = {{0, -I}, {I, 0}}
/**
 * should grad really be allocated here? 
 * thread safe, yes, but could use fvec otherwise
 */
int hamf(gsl_vector *z, gsl_vector *fvec, long double epsilon)
{
	int retval;

	double g0,g1;
	retval = hamgradZ(z, fvec, epsilon);
	
	g0 = gsl_vector_get(fvec, 0);
	g1 = gsl_vector_get(fvec, 1);
	gsl_vector_set(fvec, 0, gsl_vector_get(fvec, 2));
	gsl_vector_set(fvec, 1, gsl_vector_get(fvec, 3));
	gsl_vector_set(fvec, 2, -1.0*g0);
	gsl_vector_set(fvec, 3, -1.0*g1);
	return retval;
}


/** 
 * do a fixed point step for a phase-space vector yn
 *  z_in is a matrix (s x 4) with rows giving each z of the s cpts of z
 *
 * so what if Z becomes unstable and grows instead of converging? then we're boned
 * it seems like this will happen if |f'(y)| -> big?
 * this usually happens around q1,q2 -> 2pi or 0
 */
int fixed_point_iter_step(gsl_vector *yn, gsl_matrix* z_in, gsl_matrix *z_next, double dt, long double epsilon){
	int i, j;
	int retval;
	int ndimY = 4; // size of phase-space vecs

	gsl_vector_view row_view;
	
	for(i = 0; i < sOrder; i++){
		for(j = 0; j < sOrder; j++){
			gsl_vector_memcpy(pos_temp, yn); // copy y_n into pos_temp
			row_view = gsl_matrix_row(z_in, j); // get the j'th row of Z_in
			gsl_vector_add(pos_temp, &(row_view.vector)); // add this to y_n

			/* printf("# (%d %d)pos_temp: %lf %lf %lf %lf\n", i, j, */
			/* 			 gsl_vector_get(pos_temp, 0), gsl_vector_get(pos_temp, 1), */
			/* 			 gsl_vector_get(pos_temp, 2), gsl_vector_get(pos_temp, 3)); */
			
			retval = hamf(pos_temp, f_temp, epsilon);
			if(retval == GSL_FAILURE){
				fprintf(stderr, "# grad error in fixed_point_iter_step\n");
				return GSL_FAILURE;
			}
			gsl_vector_scale(f_temp, aTab[i][j]*dt); // multiply by h*a_ij 

			/* printf("# f_temp: lf %lf %lf %lf\n",  */
			/* 			 gsl_vector_get(f_temp, 0), gsl_vector_get(f_temp, 1), */
			/* 			 gsl_vector_get(f_temp, 2), gsl_vector_get(f_temp, 3)); */
						 
			// now view the appropriate row in z_next
			row_view = gsl_matrix_row(z_next, i);
			gsl_vector_add(&(row_view.vector), f_temp); // add f_temp to the matrix row
		}
	}

	return GSL_SUCCESS;
}

/**
 * returns the L2 element wise distance between the two matrices
 */
double matrix_diff(gsl_matrix* z1, gsl_matrix* z2){
	double eps = 0.0;
	double diff;
	int i, j;
	int ndimY = 4;
	for(i = 0; i < sOrder; i++){
		for(j = 0; j < ndimY; j++){
			eps += pow(gsl_matrix_get(z1, i, j) - gsl_matrix_get(z2, i, j), 2.0);
		}
	}
	return(sqrt(eps));
}

void print_state_z(gsl_matrix *z){
	int i, j;
	int ndimY = 4;
	for(i = 0; i < sOrder; i++){
		for(j = 0; j < ndimY; j++){
			printf("%.12lf ", gsl_matrix_get(z, i, j));
		}
		printf("\n");
	}
}

/**
 *  inits z_n with the matrix zpprev_step_1 = z_{n-1} and zprev_step_2 = z_{n-2} like this
 *
 * z_n = z_n-1 + Del Z_n-1 
 * where 
 * Del Z_n-1 = Z_{n-1} - Z_{n-2}
 *
 * could certainly go to higher orders here by storing more previous z steps
 */
void equistage_init(gsl_matrix *zinit){
	int i;
	int ndimsY = 4;
	gsl_matrix* diff_mat = gsl_matrix_alloc(sOrder, ndimsY); // use this to accumulate the finite differences
	gsl_matrix_set_zero(diff_mat);
	
	gsl_matrix_memcpy(zinit, zprev_step_1); // order k = 0

	gsl_matrix_memcpy(diff_mat, zprev_step_1); // diff_mat <- z_{n-1}
	gsl_matrix_sub(diff_mat, zprev_step_2); // diff_mat <- diff_mat - z_{n-2}
	gsl_matrix_add(zinit, diff_mat); // zinit <- zinit + diff_mat

	gsl_matrix_free(diff_mat);
}


/**
 * iterate a phase-space step using an implicit RK method
 * currently the butcher tables are for s=2,s=3 gauss methods which 
 * give pretty solid results.
 * 
 * the number of iterations needed is a function of the stepsize, the tolerance for the 
 * final result, and slightly a function of where the point is in phase space
 * 
 *
 * possibilities for initial condition:
 * 1) just zero
 * 2) copy in the previous z values we used from zprev_step (equistage init)
 * 
 * 3) z_i = h*b[i] *f(y)
 */
int iterate_gauss(gsl_vector *y_now, gsl_vector* y_next, double dt, double epsilon_grad){
	/* the tolerance for the fixed point iterations
	 * doesn't seem to converge if < 1e-10, presumably because of 
	 * problems with the hamiltonian accuracy 
	 * 
	 * this dials the accuracy and the speed of the whole process
	 */
	//double epsilon_z_min = 1e-10; 
	double epsilon_z_min = 1e-8;
	//double epsilon_z_min = sqrt(DBL_EPSILON);
	int i, iter = 0;
	int retval;
	int j;
	int ndimsY = 4;
	int stopflag = 0;
	int stepMax = 64;
	double diffValue = 0.0;
	double sumEps[4] = {0.0,0.0,0.0,0.0}; // compensated summation accumulator
	double sumT = 0.0;
	double sumY = 0.0;
	gsl_matrix *z_init = gsl_matrix_alloc(sOrder, ndimsY);
	gsl_matrix *z_next = gsl_matrix_alloc(sOrder, ndimsY);
	gsl_vector_view row_view;
	gsl_vector *f_temp = gsl_vector_alloc(ndimsY);
	gsl_vector *y_temp = gsl_vector_alloc(ndimsY);

	gsl_matrix_set_zero(z_next);
	
	/**
	 * the just use zero method
	 */
	gsl_matrix_set_zero(z_init); // start with the stupidest possible init all zeros

	/**
	 * the initial z from f method
	 */
	/* hamf(y_now, f_temp, epsilon_grad); */
	/* for(i = 0; i < sOrder; i++){ */
	/* 	gsl_vector_scale(f_temp, bVec[i]*dt); */
	/* 	for(j = 0; j < ndimsY; j++){ */
	/* 		gsl_matrix_set(z_init, i, j, gsl_vector_get(f_temp, j)); */
	/* 	} */
	/* } */
	// gsl_vector_set_zero(f_temp);

	/**
	 * use the previous steps answer
	 * this is the 'equistage method' (6.15) in Harier et al
	 * 
	 * zprev_step(0) = {0,,,,,0} so we don't have any problem here
	 */
	equistage_init(z_init);
	//print_state_z(z_init);
	
	iter = 0;
	while(iter < stepMax){
		retval = fixed_point_iter_step(y_now, z_init, z_next, dt, epsilon_grad);
		if(retval == GSL_FAILURE){
			return GSL_FAILURE;
		}
		diffValue = matrix_diff(z_next, z_init);
		if(diffValue <= epsilon_z_min){
			break;
		} else {
			// copy z_next back to z_init
			gsl_matrix_memcpy(z_init, z_next);
			// reset z_next so we don't break anything
			gsl_matrix_set_zero(z_next);
			#ifdef DEBUG
			fprintf(stderr, "# %d %.12lf\n", iter, log10(diffValue));
			#endif
			//print_state_z(z_init);
			iter++;
		}
	} 


	fprintf(stderr, "# %d %.12lf\n", iter, log10(diffValue));
	//print_state_z(z_init);

	/**
	 * once we've converged we can use z_n to update the position 
	 * y_n+1 = y_n + \sum_{i=1..s} d_i Z_i
	 */
	gsl_vector_memcpy(y_next, y_now); // set: y_n+1 = y_n
	for(i = 0; i < sOrder; i++){ 
		gsl_vector_memcpy(y_temp, y_now); // y_temp = y_n
		row_view = gsl_matrix_row(z_init, i); 
		gsl_vector_scale(&(row_view.vector), dVec[i]); // scale by the d_i = b_j A_ij^{-1}

		for(j = 0; j < ndimsY; j++){ // compensated summation here 
			//printf("%.12lf ", gsl_vector_get(f_temp, j));
#ifdef COMPSUM			
			sumY = gsl_vector_get(&(row_view.vector), j) - sumEps[j];
			sumT = gsl_vector_get(y_next, j) + sumY;
			sumEps[j] = (sumT - gsl_vector_get(y_next, j)) - sumY;
			gsl_vector_set(y_next, j, sumT);
			//printf("%.32lf ", sumEps[j]);
#endif
		}
		//printf("\n");
		// accumulate this part onto y_next
#ifndef COMPSUM		
		gsl_vector_add(y_next, &(row_view.vector));
#endif		
	}

	// rotate the previous steps correctly
	gsl_matrix_memcpy(zprev_step_2, zprev_step_1);
	gsl_matrix_memcpy(zprev_step_1, z_next);

	gsl_matrix_free(z_init);
	gsl_matrix_free(z_next);
	gsl_vector_free(f_temp);
	gsl_vector_free(y_temp);
	return GSL_SUCCESS;
}
