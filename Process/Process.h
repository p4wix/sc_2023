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
	// Zdefiniowane procesy
	enum class State { GENERATE_USER, START_HANDOVER, REMOVE_USER, REPORT_POWER, CHANGE_STATION };
	// Kolejka priorytetowa która sortuje w zależności od czasu
	typedef std::priority_queue<Process*, std::vector<Process*>, std::function<bool(Process*, Process*)>> Agenda;

	Process(size_t, Network*, Agenda*);
	virtual ~Process();

	void virtual execute () = 0;
	//void activate (double);
	size_t get_time();

protected:
	bool terminated_{};
	size_t time_{};
	State state_;
	Network* network_ = nullptr;
	Agenda* agenda_ = nullptr;

};

