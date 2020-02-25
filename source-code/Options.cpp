#include "Options.h"

void Options::setup(float _userBalance, std::vector<UserCart> _cartData) {
	userBalance = _userBalance;
	cartData = _cartData;
	activeState = true;
	optionsRange = 1;
	display();
}

void Options::display() {
	while (activeState) {
		system("cls");

		// Displaying users details.
		std::cout << "  Balance: \x9C" << userBalance << "  |  ";
		std::cout << "Location: Home << Options" << "  |  ";
		std::cout << "Order Count: " << cartData.size() << std::endl;

		// Displaying help information.
		std::cout << "\n\n\nOptions / Help: \n";
		std::cout << "-------------- \n";
		std::cout << "\n";
		std::cout << "In order to use the vending machine enter one of the corresponding ID's of the item that you wish to add to your cart. \n";
		std::cout << "The available options include back and exit, there will be a corresponding number next to either of these, entering that number will perform that option. \n";
		std::cout << "In order to remove items from your cart enter the number that corresponds to that item in your cart and it will be removed. \n";
		std::cout << "Before you can checkout you must first have a balance that is higher than your checkout price. \n";
		std::cout << "\n\n-------------- \n";

		// Handling input errors
		if (std::cin.fail() || inputError) {
			std::cin.clear();
			std::cin.ignore(254, '\n');
			std::cout << "Ooops. Looks like you entered an invalid input. Please try again!" << std::endl;
		}

		std::cout << "Please enter 1 to go back: ";
		std::cin >> inputValue;

		// Handling inputs
		if (!std::cin.fail()) {
			if (inputValue > 0 && inputValue <= optionsRange) {
				if (inputValue == optionsRange) {
					// yes selected
					activeState = false;
					inputError = false;
				}
			} else {
				inputError = true;
			}
		}
		Sleep(100);
	}
}
