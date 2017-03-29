/*
 *  MMcc.h
 *  Simulation
 *
 *  Created by yves on 7/28/10.
 *  Copyright 2010 Yves' Code. All rights reserved.
 *
 */

#ifndef GAURD_MMCCFUNCTIONS
#define GAURD_MMCCFUNCTIONS

#include "CFTP.h"

class MMcc : public  CFTP {
	
protected:
	double lambda;
	double mu;

	int updateFunction(double randVarX, int state);
	
public:
	MMcc(int _stateSize, double _lambda, double _mu):CFTP(_stateSize),
	lambda(_lambda), mu(_mu){
		
	}
	
	
};

#endif
