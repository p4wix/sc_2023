//
// Created by Pawel Biniak on 27/04/2023.
//

#include "SeedGenerator.h"

void generateSeedsData() {
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