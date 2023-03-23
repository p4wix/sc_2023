//
// Created by Pawel Biniak on 22/03/2023.
//

#include "Constants.h"

const double Constants::l = 5000; // meters
const double Constants::x = 2000; // meters
const double Constants::t = 0.02; // 20ms -> 0.02s
const double Constants::delta = 8;
const int Constants::n = 20;
const int Constants::alfa = 3;

double Constants::v() {
	std::uniform_real_distribution<double> dist(5.0, 50.0);
	static std::mt19937 rng(std::random_device{}());
	return dist(rng);
}

double Constants::s() {
	std::normal_distribution<double> dist(0.0, 4.0);
	static std::mt19937 rng(std::random_device{}());
	return dist(rng);
}

double Constants::tau() {
	std::exponential_distribution<double> dist(1.0);
	static std::mt19937 rng(std::random_device{}());
	return dist(rng);
}