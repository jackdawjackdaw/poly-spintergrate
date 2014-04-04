


void fixed_point_step(double* jin, double* jout, double* zprev, double dt){
  double tdvec[13];
  double tdnorms[4];
  double tvec[13];
  double vecsum[13];
  int i;

  for(i = 1; i < 13; i ++){
    vecsum[i] = jin[i] + zprev[i];
  }
  for(i = 0; i < 4; i++){
    tdnorms[i] = sqrt(pow(vecsum[(i)*3+1],2) + pow(vecsum[(i)*3+2],2)+ pow(vecsum[(i)*3+3],2));
  }
  
  tvec[1] = vecsum[1] / tdnorms[0];
  tvec[2] = vecsum[2] / tdnorms[0];
  tvec[3] = vecsum[3] / tdnorms[0];

  tvec[4] = vecsum[4] / tdnorms[1];
  tvec[5] = vecsum[5] / tdnorms[1];	
  tvec[6] = vecsum[6] / tdnorms[1];	

  tvec[7] = vecsum[7] / tdnorms[2];
  tvec[8] = vecsum[8] / tdnorms[2];	
  tvec[9] = vecsum[9] / tdnorms[2];	

  tvec[10] = vecsum[10] / tdnorms[3];
  tvec[11] = vecsum[11] / tdnorms[3];	
  tvec[12] = vecsum[12] / tdnorms[3];	

  
  get_eom_full(tvec, jout);
  
  for(i = 0; i < 13; i++){
    jout[i] = 0.5 * dt*jout[i];
  }
  
}

void fixed_point_iterate(double* jin, double* jnext, double dt){
  int stepMax = 16;
  double eps = 1e-12;
  int nstep = 0;
  double zin[13];
  double znext[13];
  double diff = 1;
  int i;

  for(i = 1; i< 13; i++)
    zin[i] = 0.0;
  
  while(diff >= eps && nstep < stepMax){

    fixed_point_step(jin, znext, zin, dt);

    diff = 0.0;
    for(i = 1; i < 13; i++){
      diff += sqrt(pow(zin[i] - znext[i], 2)); /* compute the difference between steps*/
      zin[i] = znext[i]; /* and copy the array bits around */
    }
    nstep++;
  }
  
  for(i = 1; i < 13; i++){
    jnext[i] = 2*znext[i] + jin[i];
  }
}
