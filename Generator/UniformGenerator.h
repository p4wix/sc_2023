//
// Created by Pawel Biniak on 27/04/2023.
//

#ifndef SC_2023_UNIFORMGENERATOR_H
#define SC_2023_UNIFORMGENERATOR_H

#include <string>
#include <cmath>

class UniformGenerator
{
public:
	UniformGenerator(int);
	virtual ~UniformGenerator();

	// Draws number between <0,1>
	double Rand();

	int get_kernel() const;
private:
	int kernel_;
	const double kM = 2147483647.0;
	static const int kA = 16807;
	static const int kQ = 127773;
	static const int kR = 2836;
};


#endif //SC_2023_UNIFORMGENERATOR_H
