//
// Created by Pawel Biniak on 13/04/2023.
//

#include "Simulator.h"

Simulator::Simulator(Network* network) : network_(network), speedGenerator(144311), spawnTimeGenerator(197555725), powerBaseStationGenerator(756247811) {
	// setting up file to save every user's report
	handleResultsFile();
}

Simulator::~Simulator() {
	handleCollectNetworkDataToFile();
	resultsFile.close();
	delete network_;
}

void Simulator::run(int time) {
	std::cout << "Started Simulation method process interaction (M4): \n";
	// setting up time
	clock_ = 0;

	// function that compares the activation times of two processes and returns true if the activation time of the process on the right is less
	auto cmp = [](Process *left, Process *right) { return left->get_time() > right->get_time(); };
	Process::Agenda agenda(cmp);

	// setting up first user process
	int id = 0;
	auto user = new User(clock_, network_, &agenda, id, speedGenerator.RandScaled(), Constants::x, &speedGenerator,
											 &spawnTimeGenerator, &powerBaseStationGenerator);
	user->activate(0);

	// main loop
	while (clock_ < time) {
		// we take process from top, that have smallest activation time, so it will be next executed
		Process *process = agenda.top();

		if(process->getEndSimulationCondition()){
			std::cout << "Users from the buffer and waiting buffer served\nEND of the Simulation\n\n";
			break;
		}

		// remove it from queue
		agenda.pop();

		// Setting the simulation time to the current process activation time
		clock_ = process->get_time();

		std::cout << "Simulation Time:" << clock_ << std::endl;

		// save current report data to result

		process->sentUserReport(resultsFile);

		// execute current process first from agenda, that has the less activation time. (only those processes which are in the buffer)
		process->execute();

		// if it has been completed, release the memory
		if (process->isTerminated()) {
					if(agenda.top() != process){
						int a = 0;
					}
			//agenda.pop();
			delete process;
		}

	}
}

void Simulator::handleResultsFile() {
	std::string filename = "Simulator/SimulationData/results.csv";
	resultsFile.open(filename, std::ios::out);

	if (!resultsFile.is_open()) {
		std::cout << "Error opening file: " << filename << std::endl;
		return;
	}
}

void Simulator::handleCollectNetworkDataToFile() {
	resultsFile << "Handed users: " << network_->numbersOfHandledUsers.size() << std::endl;
}



/*
Sprawdzenie warunku clock_ < static_cast<size_t>(time). Jeśli warunek ten nie jest spełniony,
pętla zostanie przerwana, a wykonanie programu przejdzie do linii kodu poza pętlą.

Pobranie procesu z kolejki priorytetowej agenda. Proces ten zostaje pobrany z góry kolejki, ponieważ jest to proces z najmniejszym czasem aktywacji.
Pobranie procesu odbywa się poprzez wywołanie metody top() na obiekcie agenda, która zwraca proces znajdujący się na szczycie kolejki.
Następnie ten proces zostaje usunięty z kolejki, wywołując metodę pop().

Ustawienie czasu symulacji na czas aktywacji procesu. Czas symulacji jest przechowywany w zmiennej clock_,
a czas aktywacji procesu można odczytać poprzez wywołanie metody get_time() na obiekcie process.
Dzięki temu, wartość zmiennej clock_ zostaje zaktualizowana do czasu aktywacji procesu,
co oznacza, że symulacja osiągnęła moment, w którym ten proces ma zostać wykonany.

Wyświetlenie aktualnego czasu symulacji. Wartość zmiennej clock_ jest wyświetlana na ekranie,
aby użytkownik miał wgląd w to, w jakim momencie trwa symulacja.

Wykonanie procesu. Wywołana zostaje metoda execute() na obiekcie process,
co odpowiada za wykonanie kodu, który reprezentuje dany proces.

Sprawdzenie, czy proces został zakończony. Po wykonaniu metody execute(), sprawdzane jest, czy dany proces został zakończony.
Jeśli tak, to wywoływana jest metoda isTerminated(), która zwraca wartość true, jeśli proces został oznaczony jako zakończony.
W przypadku zakończenia procesu, jego pamięć zostaje zwolniona przez wywołanie operatora delete.
 */