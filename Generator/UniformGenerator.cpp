//
// Created by Pawel Biniak on 27/04/2023.
//

#include "UniformGenerator.h"

UniformGenerator::UniformGenerator(int kernel): kernel_(kernel)
{
	// empty
}

UniformGenerator::~UniformGenerator() = default;

double UniformGenerator::Rand()
{
	int h = kernel_ / kQ;
	kernel_ = kA * (kernel_ - kQ * h) - kR * h;
	if (kernel_ < 0)
		kernel_ = kernel_ + static_cast<int>(kM);
	return kernel_ / kM;
}

int UniformGenerator::get_kernel() const {
	return kernel_;
}
