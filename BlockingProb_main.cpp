/*
 *  BlockingProb_main.cpp
 *  Simulation
 *
 *  Created by yves on 8/11/10.
 *  Copyright 2010 Yves' Code. All rights reserved.
 *
 */


#include <iostream>


int main (int argc, char * const argv[]) {

	std::cout << "Blocking probability recursive formula \n";
	
	double lambda;
	double mu;
	
	std::cout << "Enter lamda\n";
	std::cin >> lambda;
	
	std::cout << "Enter mu\n";
	std::cin>> mu;
	
	int stateSize;
	
	std::cout << "Enter target state size\n";
	std::cin >> stateSize;

	/*
	BetaC(rho) = rho*BetaC-1(rho)/(C + rho*BetaC-1(rho))  
	Beta0(rho) = 1
	 */
	
	double betaC = 1.0; // beta0(rho) = 1
	double C = 1.0;
	double rho = lambda/mu;
	
	while (C < stateSize) {
		betaC = rho*betaC/(C + rho*betaC);
		C++;
	}
	
	std::cout << "The probability of blocking at the state size is " << betaC;

}