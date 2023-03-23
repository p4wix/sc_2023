#include <iostream>
#include "User/User.h"
#include "BaseStation/BaseStation.h"
#include "Constants/Constants.h"

int main() {
	User u(Constants::x, Constants::v());

	std::cout << u.powerReceived() << std::endl;

	return 0;
}
