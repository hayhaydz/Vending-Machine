#include "Home.h"

Home::Home() {
	setup();
}

void Home::setup() {
	activeState = true;
	inputError = false;
	// Making decimals always have 2 decimal points.
	std::cout << std::setprecision(2) << std::fixed;
	display();
}

void Home::display() {
	while (activeState) {
		system("cls");

		std::cout << "  Balance: \x9C" << userBalance << "  |  ";
		std::cout << "Location: Home" << "  |  ";
		std::cout << "Order Count: " << cartData.size() << std::endl;
		std::cout << "\n\n";

		std::cout << "Categories: \n";
		std::cout << "-------------- \n\n";

		// Displaying categories to user.
		for (int i = 0; i < categoryData.size(); i++) {
			std::cout << categoryData[i].id + 1 << ". ";
			std::cout << categoryData[i].name << std::endl;
		}

		std::cout << "\n-------------- \n";
		std::cout << categoryData.size() + 1 << ". ";
		std::cout << "view cart / checkout\n";
		std::cout << categoryData.size() + 2 << ". ";
		std::cout << "options / help \n";
		std::cout << categoryData.size() + 3 << ". ";
		std::cout << "exit";
		optionsRange = categoryData.size() + 3;

		std::cout << "\n\n";

		// Handling invalid inputs.
		if (std::cin.fail() || inputError) {
			std::cin.clear();
			std::cin.ignore(254, '\n');
			std::cout << "Ooops. Looks like you entered an invalid input. Please try again!" << std::endl;
		}

		std::cout << "Please enter a number from 1-" << categoryData.size() << " to view a category \nor enter a number from " << categoryData.size() + 1 << "-" << optionsRange << " for one of the options: ";
		std::cin >> inputValue;

		// Handling inputs and checking they're not invalid.
		if (!std::cin.fail()) {
			if (inputValue > 0 && inputValue <= optionsRange) {
				if (inputValue <= optionsRange - 3) {
					// Category selected
					BuyItem.setup(categoryData, inputValue - 1, userBalance, cartData);
					cartData = BuyItem.getCartData();
					userBalance = BuyItem.getUserBalance();
					User -> clearCart();
					for (int i = 0; i < cartData.size(); i++) {
						User -> pushItemCart(cartData[i].categoryID, cartData[i].itemID);
					}
					cartData.clear();
					cartData = User -> getCartData();
					inputError = false;
				} else if (inputValue == optionsRange - 2) {
					// View cart selected
					User -> displayCart(categoryData);
					userBalance = User -> getBalance();
					cartData = User -> getCartData();
					inputError = false;
				} else if (inputValue == optionsRange - 1) {
					// Options selected
					Options.setup(userBalance, cartData);
					inputError = false;
				} else if (inputValue == optionsRange) {
					// Exit selected
					inputError = false;
					activeState = false;
				}
			} else {
				inputError = true;
			}
		}

		Sleep(100);
	}
}