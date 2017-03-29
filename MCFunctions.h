/*
 *  MCFunctions.h
 *  Simulation
 *
 *  Created by yves on 5/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAURD_MCFUNCTIONS
#define GAURD_MCFUNCTIONS
class MCFunctions  {
public:
	MCFunctions(int spaceSize) {stateSpaceSize = spaceSize;}
	
	virtual double  P(int row, int col) = 0;  // Markov state transition probability function
	
	int stateSpaceSize; // Absolute maximum number of states
};

#endif
