#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

#include "Load.h"
#include "Home.h"
#include "User.h"

int main() {
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	Home Home;

	RandomIndex RI(100, 500);
	int sleepDelay = RI.roll();

	// If users balance is greater than 0 then show a change dispensing visual.
	if (Home.User->getBalance() > 0) {
		for (int y = 0; y < 3; y++) {
			for (int i = 0; i < 4; i++) {
				system("cls");
				std::cout << "Total Change: \x9C" << Home.User->getBalance() << std::endl;
				std::cout << "Dispensing your change";
				for (int x = 0; x < i; x++) {
					std::cout << ".";
				}

				Sleep(sleepDelay);
			}
		}

		system("cls");
		std::cout << "Change has been dispensed! \n";
		Sleep(1000);
	}

	// Always makesure to say thank you!
	system("cls");
	std::cout << "Thank you for using this vending machine! \n";
	Sleep(1000);

	return 0;
}