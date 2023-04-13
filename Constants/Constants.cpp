//
// Created by Pawel Biniak on 22/03/2023.
//

#include "Constants.h"

const double Constants::l = 5000; // meters
const double Constants::x = 2000; // meters
const double Constants::t = 20; // 20ms -> 0.02s
const double Constants::delta = 8;
const int Constants::n = 20;
const double Constants::alfa = 3;
const int Constants::timeToTriggerStartValue = 80;

double Constants::v() {
	static std::random_device randDev;
	static std::mt19937 twister(randDev());
	static std::uniform_real_distribution<double> dist;

	dist.param(std::uniform_real_distribution<double>::param_type(5, 50));

	return std::round(dist(twister) * 100) / 100;
}

double Constants::s() {
	std::random_device randDev;
	std::mt19937 gen(randDev());
	std::normal_distribution<double> distribution(0.0, 4.0);

	return distribution(gen);
}