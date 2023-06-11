//
// Created by Pawel Biniak on 29/03/2023.
//

#ifndef SC_2023_PROCESS_H
#define SC_2023_PROCESS_H

#endif //SC_2023_PROCESS_H

#include <cstdint>
#include <functional>
#include <vector>
#include <queue>

class Network;

class Process {
public:
	// priority queue that holds the processes to be executed, sorted in the order of their activation time
	typedef std::priority_queue<Process*, std::vector<Process*>, std::function<bool(Process*, Process*)>> Agenda;

	// defined user process state
	enum class State { GENERATE_USER, REPORT_POWER, REMOVE_USER };

	Process(double time, Network* network, Agenda* agenda);
	virtual ~Process() = 0;

	virtual void execute () = 0;
	virtual int userId () = 0;
	void activate (double, bool = true); // relative false sets the direct time, true increments current process time
	void setTerminated();

	[[nodiscard]] double get_time() const;
	[[nodiscard]] bool isTerminated() const;
	[[nodiscard]] bool getEndSimulationCondition() const;

protected:
	bool waiting{};
	bool terminated_{};
	bool endSimulation{};
	double time_{};
	State state_ = State::GENERATE_USER;
	Network* network_ = nullptr;
	Agenda* agenda_ = nullptr;
};

