//
// Created by Pawel Biniak on 22/03/2023.
//

#ifndef SC_2023_CONSTANTS_H
#define SC_2023_CONSTANTS_H

#include <iostream>
#include <random>

class Constants {
public:
	static const double l; // (l) Distance from  BS 1 and BS 2
	static const double x; // Distance from the BS 1, where users appear
	static const double t; // Time in ms, how often the user receives power from BS1 and BS2
	static const double delta; // difference the power received from BS1 and BS2 by the user (less then)
	static const int n; // max number of handled user at once
	static const double alfa;
	static const int timeToTriggerStartValue;

	static double v(); // user speed, [5-50]
	static double s(); // random value added to received power
	static std::exponential_distribution<double> tau_distribution;
};


#endif //SC_2023_CONSTANTS_H
