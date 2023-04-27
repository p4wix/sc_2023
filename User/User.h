//
// Created by Pawel Biniak on 18/03/2023.
//

#ifndef SC_2023_USER_H
#define SC_2023_USER_H

#include <iostream>
#include <random>

#include "../Constants/Constants.h"
#include "../Process/Process.h"
#include "../Network/Network.h"

enum class BaseStation { BS1 = 'BS1', BS2 = 'BS2' };

class User : public Process {
protected:
	size_t id_{}; // const user id
	double currentLocation_{}; // user position along the x axis
	BaseStation currentBaseStation{};
	double speed_{}; // User speed
	double powerReceivedBS1_{}; // power received from station BS1
	double powerReceivedBS2_{}; // power received from station BS2
	bool connected_{}; // is user connected to any of the base stations
	int timeToTrigger_{}; // Optimisation of the parameter TTT

public:
	User(size_t, Network*, Agenda*, size_t, double, double);
	~User() override;

	void execute() override;
	void setPowerReceived(); // the power received by the base station user
	bool alphaCondition() const;
	bool deltaCondition() const;
	bool distanceCondition() const;

	void move();
	size_t getId() const;
};


#endif //SC_2023_USER_H
