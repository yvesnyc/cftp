/*
 *  MCTristate.h
 *  Simulation
 *
 *  Created by yves on 5/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "CFTP.h"

class MCTristate : public CFTP {
protected:
	int updateFunction(double randVarX, int state);
	
	double P(int s, int t); // not used

public:
	MCTristate(int stateSize) : CFTP(stateSize) {}
	
};
