/*
 *  CFTPTree.cpp
 *  Simulation
 *
 *  Created by yves on 5/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CFTPTree.h"

CFTPTree::timeLine_type CFTPTree::timeLine;

CFTPTree::CFTPTree(int parent, int state, int time) {
	this->parentState = parent;
	this->state = state;
	this->time = time;
	this->refCount = 0;	
}


CFTPTree::CFTPTree(int state) {
	this->state = state;
	time = 0;
	parentState = -1;
	this->refCount = 0;
}

CFTPTree& CFTPTree::operator=(const CFTPTree& t) {
	if (this != &t) {
		state = t.state;
		time = t.time;
		parentState = t.parentState;
	}
	
	return *this;
}

void CFTPTree::removeChild(int time, int state) {
	multimap<int,CFTPTree>::iterator it;
	it =  timeLine[time].find(state);
	timeLine[time].erase(it);
}



