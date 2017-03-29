/*
 *  MCTristate.cpp
 *  Simulation
 *
 *  Created by yves on 5/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MCTristate.h"

int MCTristate::updateFunction(double randVarX, int state) {
	// Map probability sum range to state space 
	
	double probSum = 0.0;
		
	double transProb = 0.0;
	
	transProb = 1.0/3.0;
	
	if (randVarX < probSum + transProb) {
		// condition 0
		if (state+1 < stateSpaceSize)
			return state+1; 
		else
			return stateSpaceSize-1;
	}
	
	probSum += transProb;
	
	transProb = 1.0/3.0;
	
	if (randVarX < probSum + transProb) {
		// condition 1
		if (state-1 > 0)
			return state-1;
		else 
			return 0;
	}
	
	// 
	return state;
}

/*
 This is a local Markov chain. At any state there is a 1/3 chance to go to
 the same or adjacent states.  No transitions between end states 0 and N-1 */
double MCTristate::P(int s,int t) { // from state s -> t
	/*
	if (s==0 && t == stateSpaceSize-1 || s==stateSpaceSize-1 && t==0)
		return 0.0;
	*/
	
	if (s == 0 && t == 0) // Same state transition is special
		return 2/3.0;
	
	if (s == stateSpaceSize-1 && t == stateSpaceSize-1) // Same state transition is special
		return 2/3.0;
	
	if (s >= 0 && s < stateSpaceSize)
		if (t == s || (t == s+1 && t < stateSpaceSize) || (t == s-1 && t >= 0))
			return 1/3.0;
		else
			return 0.0;
	else 
		return 0.0;

}
