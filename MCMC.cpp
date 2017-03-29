/*
 *  MCMC.cpp
 *  Simulation
 *
 *  Created by yves on 5/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MCMC.h"

int MCMC::updateFunction(double randVarX, int state) {
	double probSum = 0.0;
	
	int s;
	int numStates = chain->stateSpaceSize;
	
	for (s=0; s < numStates; s++) {
		double transProb = chain->P(state, s);
		
		if (randVarX < probSum + transProb)
			break;
		else
			probSum += transProb;
	}
	
	if (s == numStates) // because of roundoff error
		return numStates-1;
	else
		return s;
}