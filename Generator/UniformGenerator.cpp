//
// Created by Pawel Biniak on 27/04/2023.
//

#include "UniformGenerator.h"

UniformGenerator::UniformGenerator(int kernel): kernel_(kernel) { }

UniformGenerator::~UniformGenerator() = default;

double UniformGenerator::Rand() {
	int h = kernel_ / kQ;
	kernel_ = kA * (kernel_ - kQ * h) - kR * h;
	if (kernel_ < 0)
		kernel_ = kernel_ + static_cast<int>(kM);
	return kernel_ / kM;
}

int UniformGenerator::get_kernel() const {
	return kernel_;
}

void UniformGenerator::generateSeedsData() {
	int number_of_rands = 100000;
	int seed_per_simulation = 4;

	// Create random generator with arbitrary seed
	int start_seed = 144311;
	auto uniform_generator = UniformGenerator(start_seed);
	std::vector<double> numbers;
	std::vector<int> seeds;

	int numberOfFiles = 10;
	for (int i = 0; i < numberOfFiles; ++i) {
		for(int j = 0; j < seed_per_simulation; ++j){
			seeds.push_back(uniform_generator.get_kernel());
			for (int k = 0; k < number_of_rands; ++k) {
				numbers.push_back(uniform_generator.Rand());
			}
		}

		// Save data to file
		std::string file_name = "Generator/Seed/seed-" + std::to_string(i + 1) + ".txt";
		std::ofstream output_file(file_name);
		std::ostream_iterator<int> output_iterator(output_file, "\n");
		std::copy(seeds.begin(), seeds.end(), output_iterator);

		seeds.clear();
		numbers.clear();
	}
}

double UniformGenerator::RandExp(double lambda) {
	double k = Rand();
	return -(1.0/lambda) * log(k);
}

std::pair<double, double> UniformGenerator::RandGauss(double mu, double sigma) {
	constexpr double epsilon = std::numeric_limits<double>::epsilon();
	constexpr double two_pi = 2.0 * M_PI;

	//create two random numbers, make sure u1 is greater than epsilon
	double u1, u2;
	do
	{
		u1 = Rand();
	}
	while (u1 <= epsilon);
	u2 = Rand();

	//compute z0 and z1
	auto mag = sigma * sqrt(-2.0 * log(u1));
	auto z0  = mag * cos(two_pi * u2) + mu;
	auto z1  = mag * sin(two_pi * u2) + mu;

	return std::make_pair(z0, z1);
}

double UniformGenerator::RandScaled() {
	return Rand() * (50.0 - 5.0) + 5.0;
}

