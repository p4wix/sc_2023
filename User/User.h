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
	int id_{};
	double currentLocation_{};
	BaseStation currentBaseStation{};
	double speed_{};
	double powerReceivedBS1_{};
	double powerReceivedBS2_{};
	int timeToTrigger_{};
	int howManyTimesUserChangedBaseStation{};
	bool disconnectedByDelta{};
	bool disconnectedByDistance{};
	double userJoinTime{};
	double userLeaveTime{};
	bool sendReport{};


	UniformGenerator* speedGenerator; // rozkład równomierny przeskalowany o [5;50]
	UniformGenerator* spawnTimeGenerator; // rozkład wykładniczym o intensywności λ
	UniformGenerator* powerBaseStationGenerator; // rozkład Gaussa z średnią 0 i odchyleniem 4

public:
	char** argv_;

	User(double, Network*, Agenda*, int, double, double, UniformGenerator*, UniformGenerator*, UniformGenerator*, char**);

	void execute() override;
	int userId() override;
	void setPowerReceived();
	void move();
	void setUserJoinTime(double);
	void setUserLeaveTime(double);

	[[nodiscard]] bool alphaCondition() const;
	[[nodiscard]] bool deltaCondition() const;
	[[nodiscard]] bool distanceCondition() const;
	[[nodiscard]] int get_id() const;
	[[nodiscard]] double get_current_location() const;
	[[nodiscard]] double get_how_many_times_base_changed() const;
	[[nodiscard]] bool get_delta_disc() const;
	[[nodiscard]] bool get_distance_disc() const;
	[[nodiscard]] double get_user_time_in_network() const;
	[[nodiscard]] double get_user_join_time() const;
	[[nodiscard]] double get_user_speed() const;
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
