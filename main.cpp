#include <iostream>

#include "MMcc.h"
#include "MCTristate.h"

#define SSIZE 10
#define SIMREP 1000

int main (int argc, char * const argv[]) {
    // insert code here...
    std::cout << "Markov Simulator: " << SSIZE << " states and " << SIMREP << " repetitions\n";
	
	//CFTP *sim;
//	MCTristate * sim;
	MMcc *sim;
	
	int stateSize = SSIZE;
	int repetition = SIMREP;
	
	double  probDist[SSIZE] = {0.0};
//	double * probDist = new double[stateSize];
	
	//sim = new CFTP(new MCTristate(stateSize));
	
	//sim = new CFTP(stateSize, lambda, mu);
	//sim = new MCTristate(stateSize);
	double lambda, mu;
	lambda = 20;
	mu = 5;
	
	sim = new MMcc(stateSize, lambda, mu);
	
	for (int r = 0; r < repetition; r++) {
	//	std::cout << "Repetition " << r<<"\n"; 
		probDist[sim->couplingFromThePastLoop()] += 1.0;
	
	}
	
    return 0;
}
