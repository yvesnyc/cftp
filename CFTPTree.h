/*
 *  CFTPTree.h
 *  Simulation
 *
 *  Created by yves on 5/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef GAURD_CFTPTREE
#define GAURD_CFTPTREE

#include <map>
#include <vector>

using namespace std;

class CFTPTree { // Recursive tree node
	
public:
//	typedef multimap<int,CFTPTree> timeStates_type; // Possible many states that map from -1 time step
	typedef multimap<int,CFTPTree> timeStates_type; // Possible many states that map from -1 time step
	typedef vector<timeStates_type> timeLine_type;// Time line, expands for each time step
	
	CFTPTree(int state);
	CFTPTree(int parentState, int state, int time);
	CFTPTree& operator=(const CFTPTree&);
	bool noKey(int state) {return timeLine[time-1].count(state)==0;}
	void removeChild(int time, int state);
	int getParent() {return parentState;}
	int getState() {return state;}
	int getTime() {return time;}
	void incrCount() {refCount++;}
	void decrCount() {refCount--;}
	int getRefCount() {return refCount;}
	bool equals(int state) {return this->state == state;}
	static timeLine_type timeLine; // Container of time containers, indexed by time

private:
	int parentState; // Markov chain along previous time and parent state
	//multimap<int,CFTPTree> *timeList; // Pointer to multimap holding all CTP nodes
	int state; 
	int time; // Negative numbers and zero
	int refCount; // number of incoming branches
	
};

#endif