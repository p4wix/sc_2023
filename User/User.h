//
// Created by Pawel Biniak on 18/03/2023.
//

#ifndef SC_2023_USER_H
#define SC_2023_USER_H

#include <iostream>
#include <random>

class User {
	double currentLocation; // user position along the x axis
	double speed; // User speed
	double powerReceivedBS1; // power received from station BS1
	double powerReceivedBS2; // power received from station BS2
	bool connected; // is user connected to any of the base stations
	bool handOverActive;
	int timeToTrigger; // Optymalizacja parametru TTT

public:
	User();
	User(double, double);
	~User();

	double powerReceived(); // the power received by the base station user
	void checkAlfaCond(); //

	void updatePosition(double);

	bool isConnected() const;
	void connect();
	void disconnect();
};


#endif //SC_2023_USER_H
