//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Process.h"

Process::Process(double time, Network* network, Agenda *agenda) : time_(time), network_(network), agenda_(agenda) {}

Process::~Process() { };

void Process::activate(double time, bool relative) {
	if (relative) {
		time_ += time;
	}
	else {
		time_ = time;
	}
	if(!waiting) {
		agenda_->push(this);
	}
}

void Process::sleep() {
	waiting = true;
}

double Process::get_time() const { return time_; }

bool Process::isTerminated() const { return terminated_; }

void Process::setTerminated() {
	terminated_ = true;

	if(agenda_->empty()) {
		// means all users from the buffer and waiting buffer served
		endSimulation = true;
	}
}

void Process::setWaitingFalseAndActive(double time) {
	waiting = false;
	activate(time, false);
}

bool Process::getEndSimulationCondition() const {
	return endSimulation;
}

/*

Metoda activate w klasie Process służy do umieszczenia obiektu Process w kolejce procesów, które mają być wykonane w symulacji.
Metoda ta przyjmuje dwa argumenty: czas aktywacji i flagę relative, która określa,
czy podany czas jest bezwzględny czy względny wobec czasu aktualnego procesu.

Gdy flaga relative ma wartość true (domyślna wartość), czas aktywacji jest dodawany do czasu aktualnego procesu,
a wynikowy czas jest ustawiany jako czas aktywacji dla danego procesu.
Następnie proces jest dodawany do kolejki agenda_ w klasie Process za pomocą metody push().

Jeśli flaga relative ma wartość false, to czas aktywacji jest ustawiany bezpośrednio jako czas aktywacji dla danego procesu,
a proces jest dodawany do kolejki agenda_ w klasie Process za pomocą metody push().

Metoda activate jest wywoływana w kodzie symulatora, gdy tworzony jest pierwszy proces użytkownika (User) i gdy ten proces jest gotowy do uruchomienia,
czyli jego czas aktywacji wynosi 0. W tym przypadku metoda activate jest wywoływana z czasem aktywacji równej 0,
a flaga relative ma wartość domyślną (true), co oznacza,
że czas aktywacji procesu User zostanie ustawiony na czas aktualny (czyli 0) plus 0, czyli na 0.
Proces User jest następnie dodawany do kolejki agenda_, aby mógł zostać wykonany w kolejce.

Metoda activate jest również wywoływana w implementacji poszczególnych procesów,
aby dodać do kolejki nowe procesy lub ustawić czas aktywacji dla już istniejących procesów.
Metoda ta umożliwia zdefiniowanie kolejności wykonywania procesów w symulacji,
co jest istotne w przypadku modelowania systemów wieloprocesorowych lub sieci komputerowych,
gdzie wiele procesów działa jednocześnie i wzajemnie się wpływa na siebie.

*/