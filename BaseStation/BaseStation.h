//
// Created by Pawel Biniak on 18/03/2023.
//

#ifndef SC_2023_BASESTATION_H
#define SC_2023_BASESTATION_H

#include <iostream>
#include <random>
#include "../User/User.h"

class BaseStation {
	double position;
	double alpha;
	double timeToTrigger;

public:
	BaseStation();
	BaseStation(double, double, double);
	~BaseStation();

	//double getReceivedPower(double) const; // A method that returns the received power from a user who is at a distance from the base station.


	double getPosition();
	double getAlpha();
	double getTimeToTrigger();
};


#endif //SC_2023_BASESTATION_H
