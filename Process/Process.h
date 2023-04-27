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
	enum class State { GENERATE_USER, HANDOVER, REMOVE_USER, REPORT_POWER, CHANGE_STATION };

	Process(size_t time, Network* network, Agenda* agenda);
	virtual ~Process();

	virtual void execute () = 0;
	void activate (size_t, bool = true); // relative false sets the direct time, true increments current process time
	size_t get_time() const;
	bool isTerminated() const;
	void setTerminated();

protected:
	bool terminated_{};
	size_t time_{};
	State state_ = State::GENERATE_USER;
	Network* network_ = nullptr;
	Agenda* agenda_ = nullptr;
};

