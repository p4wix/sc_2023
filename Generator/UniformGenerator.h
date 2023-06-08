//
// Created by Pawel Biniak on 27/04/2023.
//

#ifndef SC_2023_UNIFORMGENERATOR_H
#define SC_2023_UNIFORMGENERATOR_H

#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <utility>

class UniformGenerator {
	int kernel_;
	const double kM = 2147483647.0;
	static const int kA = 16807;
	static const int kQ = 127773;
	static const int kR = 2836;

public:
	UniformGenerator(int);
	virtual ~UniformGenerator();

	// Draws number between <0,1>
	int get_kernel() const;
	void generateSeedsData();
	static std::vector<double> generateDataBasedOnSeed(int);

	double Rand(); // równomierny ale od [0,1]
	double RandScaled();
	double RandExp(double); // wykładniczy
	std::pair<double, double> RandGauss(double, double);
};


#endif //SC_2023_UNIFORMGENERATOR_H
