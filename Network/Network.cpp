//
// Created by Pawel Biniak on 23/03/2023.
//

#include "Network.h"

Network::Network(char** argv) : argv_(argv) {
	handleFiles();
};

Network::~Network() {
	currentUsersNumberInBuffersFile.close();
	currentUsersDisconnectReportFile.close();
	currentUsersChangeStationReportFile.close();
}

void Network::addUserToNetwork(User *user) {
	++allUsers;
	if(get_buffer_size() < Constants::n) {
		buffer_.push(user);
		user->setUserJoinTime(user->get_time());
	}
	else {
		++waitingBuffer_;
	}
}

void Network::removeUserFromNetwork(User *user) {
	// +1 number of handled users
	++numbersOfHandledUsers;

	//std::stoi(argv_[2])
	if(numbersOfHandledUsers == std::stoi(argv_[2])) {
		isUsersLimitReached = true;
	}

	// set user leave time
	user->setUserLeaveTime(user->get_time());

	// send user report
	if(numbersOfHandledUsers > 25) {
		sendCurrentUserDisconnectReport(user);
	}

	std::queue<User*> tempBuffer;
	while (!buffer_.empty()) {
		User* currentUser = buffer_.front();
		buffer_.pop();

		if (currentUser->get_id() != user->get_id()) {
			tempBuffer.push(currentUser);
		}
	}

	buffer_ = std::move(tempBuffer);

	if(numbersOfHandledUsers > 25) {
		//sendCurrentUsersNumberInBuffersReport(user->get_time(), user->get_id());
	}
}

void Network::decrementWaitingBuffer() {
	if (waitingBuffer_ != 0) {
		--waitingBuffer_;
	}
}

size_t Network::get_buffer_size() {
	return buffer_.size();
}

void Network::sendCurrentUsersNumberInBuffersReport(double currentSystemTime, int id) {
	std::stringstream csvLine;

	if (currentUsersNumberInBuffersFile.tellg() == 0) {
		currentUsersNumberInBuffersFile << "Id,Time,BufferSize,WaitingBuffer,HandledUsers\n";
	}

	csvLine << id << ',' << currentSystemTime << ',' << get_buffer_size() << ','
					<< waitingBuffer_ << ',' << numbersOfHandledUsers << '\n';

	currentUsersNumberInBuffersFile << csvLine.str();
}

void Network::sendCurrentUserDisconnectReport(User *user) {
	std::stringstream csvLine;

	if (currentUsersDisconnectReportFile.tellg() == 0) {
		currentUsersDisconnectReportFile << "Id,Time,CurrentLocation,HowManyTimesBaseChanged,ByDelta,ByDistance,TimeInNetwork,userSpeed\n";
	}

	csvLine << user->get_id() << ',' << user->get_time() << ','
					<< user->get_current_location() << ',' << user->get_how_many_times_base_changed() << ','
					<< user->get_delta_disc() << "," << user->get_distance_disc() << ',' << user->get_user_time_in_network() << "," << user->get_user_speed() << std::endl;

	currentUsersDisconnectReportFile << csvLine.str();
}

void Network::sendCurrentUserChangeStationReport(User *user) {
	std::stringstream csvLine;

	if (currentUsersChangeStationReportFile.tellg() == 0) {
		currentUsersChangeStationReportFile << "Id,Time,CurrentLocation,HowManyTimesBaseChanged,CurrentTimeInNetWorkWhenBaseChanged\n";
	}

	csvLine << user->get_id() << ',' << user->get_time() << ','
					<< user->get_current_location() << ',' << user->get_how_many_times_base_changed() << ','
					<< (user->get_time() - user->get_user_join_time()) << std::endl;

	currentUsersChangeStationReportFile << csvLine.str();
}

void Network::handleFiles() {
	std::string usersInBufferFileName = "../FinalData/usersInBuffer/Seed-" + std::to_string(std::stoi(argv_[1])) +
																				"/result_lambda-" + std::to_string(std::stod(argv_[3])) + "-TTT-" +
																				std::to_string(std::stoi(argv_[4])) + ".csv";

	std::string disconnectFileName = "../FinalData/disconnect/Seed-" + std::to_string(std::stoi(argv_[1])) +
																			"/result_lambda-" + std::to_string(std::stod(argv_[3])) + "-TTT-" +
																			std::to_string(std::stoi(argv_[4])) + ".csv";

	std::string changeFileName = "../FinalData/change/Seed-" + std::to_string(std::stoi(argv_[1])) +
																			"/result_lambda-" + std::to_string(std::stod(argv_[3])) + "-TTT-" +
																			std::to_string(std::stoi(argv_[4])) + ".csv";

	currentUsersNumberInBuffersFile.open(usersInBufferFileName, std::ios::out);
	currentUsersDisconnectReportFile.open(disconnectFileName, std::ios::out);
	currentUsersChangeStationReportFile.open(changeFileName, std::ios::out);

	if (!currentUsersNumberInBuffersFile.is_open() or !currentUsersDisconnectReportFile.is_open() or !currentUsersChangeStationReportFile.is_open()) {
		std::cout << "Error opening file to save results: " << std::endl;
		return;
	}
}
