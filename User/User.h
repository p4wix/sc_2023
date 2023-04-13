//
// Created by Pawel Biniak on 18/03/2023.
//

#ifndef SC_2023_USER_H
#define SC_2023_USER_H

#include <iostream>
#include <random>

#include "../Constants/Constants.h"
#include "../Process/Process.h"

class User : public Process {
protected:
	size_t id_ = 0; // const user id
	double currentLocation_; // user position along the x axis
	double speed_; // User speed
	double powerReceivedBS1_{}; // power received from station BS1
	double powerReceivedBS2_{}; // power received from station BS2
	bool connected_{}; // is user connected to any of the base stations
	int timeToTrigger_{}; // Optimisation of the parameter TTT

public:
	User(size_t, Network*, Agenda*, size_t, double, double);
	~User() override;

	void execute() override;
	void setPowerReceived(); // the power received by the base station user
	void move();
	void handleAlfaCondition(); // we check the condition if the hanover starts
	void handleHandover();
	void handleChangeStation();
	void disconnectByPoorConnection();
	void disconnectByDistanceReached();
	void disconnect();

	size_t getId() const;
};


#endif //SC_2023_USER_H
