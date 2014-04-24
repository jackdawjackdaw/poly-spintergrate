#include "find-config.h"
#include "mdefs.h"

int test_config_1(double alpha, double beta, double gamma){
  if( alpha > 1 && beta > 1 && alpha*beta <= (-1 + alpha + beta)*gamma && 
   ((alpha > beta && beta*(-1 + alpha + gamma) >= alpha*gamma) || 
     (alpha*(-1 + beta + gamma) >= beta*gamma && alpha < beta)) ){
      return 1;
    } 
    return 0;
}
  
int test_config_2(double alpha, double beta, double gamma){
  if( alpha/gamma > 1 && beta/gamma > 1 && 
   (-1 + (alpha*beta)/(alpha + beta - gamma))/gamma <= 0 && 
   ((alpha*gamma < beta*gamma && beta + alpha*gamma <= alpha*(1 + beta)) || 
     (beta*gamma < alpha*gamma && beta*(-1 + gamma) <= alpha*(-1 + beta))) ){
      return 1;
    } 
    return 0;
}

int test_config_3(double alpha, double beta, double gamma){
  if( alpha/beta > 1 && gamma/beta > 1 && 
   (-1 + (alpha*gamma)/(alpha - beta + gamma))/beta <= 0 && 
   ((alpha*beta < beta*gamma && alpha*beta + gamma <= alpha*(1 + gamma)) || 
     (beta*gamma < alpha*beta && (-1 + beta)*gamma <= alpha*(-1 + gamma))) ){
      return 1;
    } 
    return 0;
}


int test_config_4(double alpha, double beta, double gamma){
  if( beta/alpha > 1 && gamma/alpha > 1 && 
   (-1 + (beta*gamma)/(-alpha + beta + gamma))/alpha <= 0 && 
   ((alpha*beta < alpha*gamma && alpha*beta + gamma <= beta*(1 + gamma)) || 
     (alpha*gamma < alpha*beta && (-1 + alpha)*gamma <= beta*(-1 + gamma))) ){
      return 1;
    } 
    return 0;
}

int test_config_5(double alpha, double beta, double gamma){
  if( alpha < 0 && beta < 0 && alpha*beta <= (-1 + alpha + beta)*gamma && 
   ((beta*(-1 + alpha + gamma) >= alpha*gamma && alpha < beta) || 
     (alpha > beta && alpha*(-1 + beta + gamma) >= beta*gamma)) ){
      return 1;
    } 
    return 0;
}

int test_config_6(double alpha, double beta, double gamma){
  if( (-1 + alpha)/(-1 + gamma) > 1 && (-1 + beta)/(-1 + gamma) > 1 && 
   (alpha*beta - gamma)/((-1 + alpha + beta - gamma)*(-1 + gamma)) <= 0 && 
   (((alpha - beta)*(-1 + gamma) < 0 && alpha*(1 - beta + gamma) <= gamma) || 
     ((alpha - beta)*(-1 + gamma) > 0 && beta*(1 - alpha + gamma) <= gamma)) ){
      return 1;
    } 
    return 0;
}

int test_config_7(double alpha, double beta, double gamma){
  if( (-1 + alpha)/(-1 + beta) > 1 && (-1 + gamma)/(-1 + beta) > 1 && 
   (beta - alpha*gamma)/((-1 + beta)*(1 - alpha + beta - gamma)) <= 0 && 
   (((-1 + beta)*(alpha - gamma) < 0 && alpha*(1 + beta - gamma) <= beta) || 
     ((-1 + beta)*(alpha - gamma) > 0 && (1 - alpha + beta)*gamma <= beta)) ){
      return 1;
    } 
    return 0;
}

int test_config_8(double alpha, double beta, double gamma){
  if( (-1 + beta)/(-1 + alpha) > 1 && (-1 + gamma)/(-1 + alpha) > 1 && 
   (alpha - beta*gamma)/((-1 + alpha)*(1 + alpha - beta - gamma)) <= 0 && 
   (((-1 + alpha)*(beta - gamma) < 0 && 
       alpha*(-1 + beta) <= beta*(-1 + gamma)) || 
     ((-1 + alpha)*(beta - gamma) > 0 && (1 + alpha - beta)*gamma <= alpha)) ){
      return 1;
    } 
    return 0;
}

int test_config_9(double alpha, double beta, double gamma){
  if( alpha > 0 && beta > 0 && gamma < 0 && alpha*(-1 + beta) + gamma <= beta && 
   ((alpha < beta && beta + alpha*gamma <= alpha*(1 + beta)) || 
     (beta < alpha && beta*(-1 + gamma) <= alpha*(-1 + beta))) ){
      return 1;
    } 
    return 0;
}

int test_config_10(double alpha, double beta, double gamma){
  if( (-1 + alpha)*(-1 + gamma) < 0 && (-1 + beta)*(-1 + gamma) < 0 && 
   (-(alpha*beta) + gamma)/((-1 + alpha + beta - gamma)*(-1 + gamma)) <= 0 && 
   (((alpha - beta)*(-1 + gamma) > 0 && alpha*(1 - beta + gamma) <= gamma) || 
     ((alpha - beta)*(-1 + gamma) < 0 && beta*(1 - alpha + gamma) <= gamma)) ){
      return 1;
    } 
    return 0;
}


int test_config_11(double alpha, double beta, double gamma){
  if( (alpha - beta)*(beta - gamma) > 0 && (-1 + beta)*(beta - gamma) < 0 && 
   (-alpha + beta*gamma)/((beta - gamma)*(-1 - alpha + beta + gamma)) <= 0 && 
   alpha != 1 && (((-1 + alpha)*(beta - gamma) < 0 && 
       alpha*(-1 + beta + gamma) <= beta*gamma) || 
     ((-1 + alpha)*(beta - gamma) > 0 && gamma <= alpha + beta*(-1 + gamma))) ){
      return 1;
    } 
    return 0;
}
  
int test_config_12(double alpha, double beta, double gamma){
  if( (-1 + alpha)*(alpha - gamma) < 0 && (alpha - beta)*(alpha - gamma) < 0 && 
   (-beta + alpha*gamma)/((alpha - gamma)*(-1 + alpha - beta + gamma)) <= 
    0 && beta != 1 && (((-1 + beta)*(alpha - gamma) < 0 && 
       beta*(-1 + alpha + gamma) <= alpha*gamma) || 
     ((-1 + beta)*(alpha - gamma) > 0 && gamma <= beta + alpha*(-1 + gamma))) ){
      return 1;
    } 
    return 0;
}

int test_config_13(double alpha, double beta, double gamma){
  if( alpha > 0 && gamma > 0 && beta < 0 && beta + alpha*(-1 + gamma) <= gamma && 
   ((alpha < gamma && alpha*beta + gamma <= alpha*(1 + gamma)) || 
     (gamma < alpha && (-1 + beta)*gamma <= alpha*(-1 + gamma))) ){
      return 1;
    } 
    return 0;
}


int test_config_14(double alpha, double beta, double gamma){
  if( (-1 + alpha)*(-1 + beta) < 0 && (-1 + beta)*(-1 + gamma) < 0 && 
   (-beta + alpha*gamma)/((-1 + beta)*(1 - alpha + beta - gamma)) <= 0 && 
   (((-1 + beta)*(alpha - gamma) > 0 && alpha*(1 + beta - gamma) <= beta) || 
     ((-1 + beta)*(alpha - gamma) < 0 && (1 - alpha + beta)*gamma <= beta)) ){
      return 1;
    } 
    return 0;
}

int test_config_15(double alpha, double beta, double gamma){
  if( (beta - gamma)*(-1 + gamma) > 0 && (alpha - gamma)*(-beta + gamma) > 0 && 
   (alpha - beta*gamma)/((beta - gamma)*(-1 - alpha + beta + gamma)) <= 0 && 
   alpha != 1 && (((-1 + alpha)*(beta - gamma) < 0 && 
       gamma <= alpha + beta*(-1 + gamma)) || 
     ((-1 + alpha)*(beta - gamma) > 0 && 
       alpha*(-1 + beta + gamma) <= beta*gamma)) ){
      return 1;
    } 
    return 0;
}

int test_config_16(double alpha, double beta, double gamma){
  if( (-1 + alpha)*(alpha - beta) < 0 && (alpha - beta)*(alpha - gamma) < 0 && 
   (alpha*beta - gamma)/((alpha - beta)*(-1 + alpha + beta - gamma)) <= 0 && 
   gamma != 1 && (((alpha - beta)*(-1 + gamma) < 0 && 
       (-1 + alpha + beta)*gamma <= alpha*beta) || 
     ((alpha - beta)*(-1 + gamma) > 0 && beta <= alpha*(-1 + beta) + gamma)) ){
      return 1;
    } 
    return 0;
}

int test_config_17(double alpha, double beta, double gamma){
  if( beta > 0 && gamma > 0 && alpha < 0 && alpha + beta*(-1 + gamma) <= gamma && 
   ((beta < gamma && alpha*beta + gamma <= beta*(1 + gamma)) || 
     (gamma < beta && (-1 + alpha)*gamma <= beta*(-1 + gamma))) ){
      return 1;
    } 
    return 0;
}

int test_config_18(double alpha, double beta, double gamma){
  if( (-1 + alpha)*(-1 + beta) < 0 && (-1 + alpha)*(-1 + gamma) < 0 && 
   (-alpha + beta*gamma)/((-1 + alpha)*(1 + alpha - beta - gamma)) <= 0 && 
   (((-1 + alpha)*(beta - gamma) > 0 && 
       alpha*(-1 + beta) <= beta*(-1 + gamma)) || 
     ((-1 + alpha)*(beta - gamma) < 0 && (1 + alpha - beta)*gamma <= alpha)) ){
      return 1;
    } 
    return 0;
}

int test_config_19(double alpha, double beta, double gamma){
  if( (alpha - gamma)*(-1 + gamma) > 0 && (alpha - gamma)*(-beta + gamma) > 0 && 
   (beta - alpha*gamma)/((alpha - gamma)*(-1 + alpha - beta + gamma)) <= 0 && 
   beta != 1 && (((-1 + beta)*(alpha - gamma) < 0 && 
       gamma <= beta + alpha*(-1 + gamma)) || 
     ((-1 + beta)*(alpha - gamma) > 0 && 
       beta*(-1 + alpha + gamma) <= alpha*gamma)) ){
      return 1;
    } 
    return 0;
}

int test_config_20(double alpha, double beta, double gamma){
  if( (alpha - beta)*(-1 + beta) > 0 && (alpha - beta)*(beta - gamma) > 0 && 
   (-(alpha*beta) + gamma)/((alpha - beta)*(-1 + alpha + beta - gamma)) <= 
    0 && gamma != 1 && (((alpha - beta)*(-1 + gamma) < 0 && 
       beta <= alpha*(-1 + beta) + gamma) || 
     ((alpha - beta)*(-1 + gamma) > 0 && 
       (-1 + alpha + beta)*gamma <= alpha*beta)) ){
      return 1;
    } 
    return 0;
}

