/*
 *  MCMC.h
 *  Simulation
 *
 *  Created by yves on 5/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MCFunctions.h"

class MCMC {

protected:
	
	MCFunctions *chain;
	
	int updateFunction(double randVarX, int state);

public:
	MCMC(MCFunctions *chainData) : chain(chainData) {
	}
};