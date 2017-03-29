/*
 *  CFTP.cpp
 *  Simulation
 *
 *  Created by yves on 5/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CFTP.h"
#include <gsl/gsl_math.h>
#include <iostream>
#include <vector>

gsl_rng * CFTP::generator = gsl_rng_alloc(gsl_rng_mt19937);

int CFTP::removeChainLink(int time, int state) {

	if (CFTPTree::timeLine[time].count(state) != 1) {
		std::cout << "Exception: removeChainLink found more than one state";
		return time;
	}
	
	// Erase one of the states in the time states
	CFTPTree::timeStates_type::iterator itr = CFTPTree::timeLine[time].find(state); // get a list of time states

	if (itr == CFTPTree::timeLine[time].end()) { // This should never be true, an expected state not found
		std::cout << "Exception: removeChainLink can't find expected state";
		return time;
	}
	
	
	int nodePrevState = itr->second.getParent();
	
	CFTPTree::timeLine[time].erase(itr);
	
	// if last T==0 time, return
	if (time == 0) return 0;
	
	// if parent has no more children, recurse
	if (CFTPTree::timeLine[time].count(state) == 0) {
		return removeChainLink(time-1, nodePrevState);
	}
	
	
	return time;
}

int CFTP::removeChainLinkLoop(long time, int state) {
	long timeWalk = time;
	int stateWalk = state;
	
	while (CFTPTree::timeLine[timeWalk].count(stateWalk) > 0) {
		
		// get state pointer as iterator
		CFTPTree::timeStates_type::iterator itr = CFTPTree::timeLine[timeWalk].find(stateWalk); 
		
		if (itr->second.getRefCount() != 0) {
			// Stop. This node has other children or incoming paths
			break;
		}
		
		// record parent
		int parentState = itr->second.getParent();
		
		// erase state from timeLine
		CFTPTree::timeLine[timeWalk].erase(itr);
		
		// if last T==0 time, return
		if (timeWalk == 0) 
			break;

		// decrement reference count on parent
		itr = CFTPTree::timeLine[timeWalk-1].find(parentState);
		itr->second.decrCount();
		
		// go to parent and redo
		timeWalk--;
		stateWalk = parentState;
			
	}
	
	return timeWalk;
}

void CFTP::updateChains(int prevTime, double randVarX, vector<int> &hangingStates) {

	int numStates = stateSpaceSize;
	
	bool *mappedRangeStates = new bool[stateSpaceSize]();
	
	// Simulate all state transitions from the domainState to the rangeState
	for (int domainState = 0; domainState < numStates; domainState++) {
		
		int rangeState = updateFunction(randVarX,domainState); 
		
		mappedRangeStates[rangeState] = true;
				
		if (prevTime == 0 && CFTPTree::timeLine[0].count(rangeState) == 0) { // rangeNode not exist yet in T==0
			// put a range state into T == 0 time line step   
			CFTPTree rangeNode(rangeState); // Make a T == 0 node
						
			CFTPTree::timeLine[0].insert(make_pair<int,CFTPTree>(rangeState, rangeNode)); // put into T == 0 timeList
		}

		// Increment reference count on range nodes
		CFTPTree::timeStates_type::iterator itr = CFTPTree::timeLine[prevTime].find(rangeState);
		itr->second.incrCount();

		// Make domain state node, remember that we use indices for pointers to parent Nodes
		CFTPTree domainNode(rangeState, domainState, prevTime+1);
		
		// add domain node to time states
		CFTPTree::timeLine[prevTime+1].insert(make_pair<int,CFTPTree>(domainState, domainNode));
		
	}
	
	
	for (int x=0; x < stateSpaceSize; x++)
		if (!mappedRangeStates[x])
			hangingStates.push_back(x);

	delete mappedRangeStates;
}
	
	
// Central method
int CFTP::couplingFromThePast(int prevTime) {
	// Generate a uniform random variable
	// One random variable used for all states
	double randVarX = gsl_rng_uniform(generator);
	
	if (prevTime == 0) { // Initialize chains, Make T == 0 timeStates
		CFTPTree::timeLine.clear(); // Make sure it is empty
		CFTPTree::timeLine.push_back(CFTPTree::timeStates_type()); // Add first time states (empty multimap) for time step T==0
	}
	
	// make a new timeStates for this T==-(prevTime+1) step
	CFTPTree::timeLine.push_back(CFTPTree::timeStates_type());
	
	vector<int> hangingStates;
	
	// Update all chains, get the list of hanging states
	updateChains(prevTime, randVarX, hangingStates);
	
	// To emulate a T == -N forward simulation, remove dead links at T == -N+1 or -(N-1) 
	// In this code prevTime is N-1
	// When removing dead links follow links along parent chains, stop when 
	// chain has siblings, return the timeList where stopped. The timeList can be checked
	// for T == 0 and for coalesce chains.
	
	int lastEditedTime = -1;
	
	// Get the -(N-1) states to check for hanging paths, disconnected from now, T= -N
	CFTPTree::timeStates_type prevTimeStates = CFTPTree::timeLine[prevTime];
	
	for (int s = 0 ; s < hangingStates.size(); s++) {
		lastEditedTime = removeChainLinkLoop(prevTime, hangingStates[s]);
		
		if (lastEditedTime == 0 && CFTPTree::timeLine[0].size() == 1)
			// single state left, we are done
			return CFTPTree::timeLine[0].begin()->first; // Done, return remaining state, Chains have coalesced
	}
	
	
	return couplingFromThePast(prevTime+1);
	
}

int CFTP::couplingFromThePastLoop(void) {
	
	long long prevTime = 0;
	double randVarX;
	
	while (true) { 
		
		// Generate a uniform random variable
		// One random variable used for all states
		randVarX = gsl_rng_uniform(generator);
		
		if (prevTime == 0) { // Initialize chains, Make T == 0 timeStates
			CFTPTree::timeLine.clear(); // Make sure it is empty
			CFTPTree::timeLine.push_back(CFTPTree::timeStates_type()); // Add first time states (empty multimap) for time step T==0
		}
		
		// make a new timeLine entry for this T==-(prevTime+1) step
		CFTPTree::timeLine.push_back(CFTPTree::timeStates_type());
		
		vector<int> hangingStates;
		
		// Update all chains, get the list of hanging states to remove
		updateChains(prevTime, randVarX, hangingStates);
		
		// To emulate a T == -N forward simulation, remove hanging states or dead links at T == -N+1 or -(N-1) 
		// In this code prevTime is N-1
		// When removing dead links follow links along parent chains, stop when 
		// chain has siblings, return the timeList where stopped. The timeList can be checked
		// for T == 0 and for coalesce chains.
						
		for (int s = 0 ; s < hangingStates.size(); s++) {
			long long lastEditedTime = removeChainLinkLoop(prevTime, hangingStates[s]);
			
			// Check for coalesce if T==0 was edited
			if (lastEditedTime == 0 && CFTPTree::timeLine[0].size() == 1)
				// single state left, we are done
				return CFTPTree::timeLine[0].begin()->first; // Done, return remaining state, Chains have coalesced
		}
	
	
		prevTime++;
	}
	
}

