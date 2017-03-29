/*
 *  CFTP.h
 *  Simulation
 *
 *  Created by yves on 5/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef GAURD_CFTP
#define GAURD_CFTP

#include "CFTPTree.h"
// #include "MCMC.h"
#include <map>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>

// class CFTP : public MCMC {
class CFTP {

public:
//	CFTP(MCFunctions *chainData):MCMC(chainData) {}
	CFTP(int _stateSize):stateSpaceSize(_stateSize){}
	int removeChainLink(int time, int state);
	int removeChainLinkLoop(long time, int state);
	
	virtual int updateFunction(double randVarX, int state) = 0;
	virtual void updateChains( int prevTime, double randVarX, vector<int> &hanging);
	int couplingFromThePast(int prevTime);
	int couplingFromThePastLoop(void);

public:
	static gsl_rng * generator;

protected:
	int stateSpaceSize;

};

#endif