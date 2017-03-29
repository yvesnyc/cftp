/*
 *  MMcc.cpp
 *  Simulation
 *
 *  Created by yves on 7/28/10.
 *  Copyright 2010 Yves' Code. All rights reserved.
 *
 */

#include "MMcc.h"

// 
int MMcc::updateFunction(double randVarX, int state) {
	// Map probability sum range to state space 
	
	double probSum = 0.0;
	
	double c = stateSpaceSize;
	
	double transProb = 0.0;
	
	transProb = lambda/(lambda + c*mu);
	
	if (randVarX < probSum + transProb) {
		// condition 0, lambda arrivals
		if (state+1 < stateSpaceSize)
			return state+1; 
		else
			return stateSpaceSize-1;
	}
		
	probSum += transProb;
	
	transProb = (state + 1.0)*mu/(lambda + c*mu);
	
	if (randVarX < probSum + transProb) {
		// condition 1, service
		if (state-1 > 0)
			return state-1;
		else 
			return 0;
	}

	// 
	return state;
}