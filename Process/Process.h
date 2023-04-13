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

#include "../Network/Network.h"

class Process {
public:
	// Kolejka priorytetowa która sortuje w zależności od czasu
	typedef std::priority_queue<Process*, std::vector<Process*>, std::function<bool(Process*, Process*)>> Agenda;

	// Zdefiniowane procesy
	enum class State { GENERATE_USER, START_HANDOVER, REMOVE_USER, REPORT_POWER, CHANGE_STATION };

	Process(size_t time, Network* network, Agenda* agenda);
	virtual ~Process();

	virtual void execute () = 0;
	void activate (size_t, bool = false);
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

