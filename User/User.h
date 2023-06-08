//
// Created by Pawel Biniak on 18/03/2023.
//

#ifndef SC_2023_USER_H
#define SC_2023_USER_H

#include <iostream>
#include <fstream>
#include <random>
#include <sstream>


#include "../Constants/Constants.h"
#include "../Process/Process.h"
#include "../Network/Network.h"

enum class BaseStation { BS1 = 'BS1', BS2 = 'BS2' };

class User : public Process {
protected:
	int id_{}; // const user id
	double currentLocation_{}; // user position along the x axis
	BaseStation currentBaseStation{};
	double speed_{}; // User speed
	double powerReceivedBS1_{}; // power received from station BS1
	double powerReceivedBS2_{}; // power received from station BS2
	int timeToTrigger_{}; // Optimisation of the parameter TTT
	double timeToNextRaport{};
	int howManyTimesUserChangedBaseStation{};

	UniformGenerator* speedGenerator; // rozkład równomierny przeskalowany o [5;50]
	UniformGenerator* spawnTimeGenerator; // rozkład wykładniczym o intensywności λ
	UniformGenerator* powerBaseStationGenerator; // rozkład Gaussa z średnią 0 i odchyleniem 4

public:
	User(double, Network*, Agenda*, int, double, double, UniformGenerator*, UniformGenerator*, UniformGenerator*);

	void execute() override;
	void sentUserReport(std::fstream&) override;
	void setPowerReceived(); // the power received by the base station user
	[[nodiscard]] bool alphaCondition() const;
	[[nodiscard]] bool deltaCondition() const;
	[[nodiscard]] bool distanceCondition() const;

	void move();
	[[nodiscard]] int get_id() const;
};

inline std::ostream& operator<<(std::ostream& os, const BaseStation& bs) {
	switch (bs) {
		case BaseStation::BS1:
			os << "BS1";
			break;
		case BaseStation::BS2:
			os << "BS2";
			break;
	}
	return os;
}

#endif //SC_2023_USER_H
