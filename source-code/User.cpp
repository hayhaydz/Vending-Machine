#include "User.h"

User* User::inst_ = NULL;

User* User::getInstance() {
	if (inst_ == NULL) {
		inst_ = new User();
	}

	return inst_;
}

User::User() {
	setup();
}

void User::setup() {
	balance = 0.0f;
	orderPrice = 0.0f;
	checkoutPossible = false;
	activeState = true;
}

void User::displayCart(std::vector<Category> _categoryData) {
	checkoutPossible = false;
	activeState = true;
	categoryData = _categoryData;
	while (activeState) {
		system("cls");
		orderPrice = 0.0f;

		// Working out price of all items in the cart.
		for (int i = 0; i < cartData.size(); i++) {
			orderPrice += categoryData[cartData[i].categoryID].itemData[cartData[i].itemID].price;
		}

		// Displaying users details.
		std::cout << "  Balance: \x9C" << balance << "  |  ";
		std::cout << "Location: Home << View Cart "<< "  |  ";
		std::cout << "Order Count: " << cartData.size() << std::endl;
		std::cout << "\n\n";

		std::cout << "Items in cart: \n";
		std::cout << "-------------- \n\n";

		// Displaying items that are in the users cart.
		for (int i = 0; i < cartData.size(); i++) {
			std::cout << i + 1 << ". ";
			std::cout << "Item Name: " << categoryData[cartData[i].categoryID].itemData[cartData[i].itemID].name << std::endl;
			if (i < 9) {
				std::cout << "   ";
			} else {
				std::cout << "    ";
			}
			std::cout << "Item Price: \x9C" << categoryData[cartData[i].categoryID].itemData[cartData[i].itemID].price << std::endl;
			if (cartData.size() > 1 && i != cartData.size() - 1) {
				std::cout << "-------------- \n";
			}
		}

		std::cout << "\n-------------- \n\n";
		std::cout << "Order Price: \x9C" << orderPrice << "\n\n";
		std::cout << "-------------- \n";

		// Working out if the checkout option should be displayed.
		if (cartData.size() > 0 && balance > orderPrice) {
			checkoutPossible = true;
		}
		if (checkoutPossible) {
			std::cout << cartData.size() + 1 << ". checkout \n";
			std::cout << cartData.size() + 2 << ". increase balance \n";
			std::cout << cartData.size() + 3 << ". back";
			optionsRange = cartData.size() + 3;
		} else {
			std::cout << "In order to checkout please make sure that you have items in your cart and that your balance is higher than the order price. \n";
			std::cout << cartData.size() + 1 << ". increase balance \n";
			std::cout << cartData.size() + 2 << ". back";
			optionsRange = cartData.size() + 2;
		}
		std::cout << "\n\n";

		// Handling input errors and invalid inputs.
		if (std::cin.fail() || inputError) {
			std::cin.clear();
			std::cin.ignore(254, '\n');
			std::cout << "Ooops. Looks like you entered an invalid input. Please try again!" << std::endl;
		}
		if (cartData.size() > 0) {
			std::cout << "Please enter a number from 1-" << cartData.size() << " to remove an item \n";
		}
		std::cout << "Enter a number from " << cartData.size() + 1 << "-" << optionsRange << " for one of the options: ";
		std::cin >> inputValue;

		// Handling inputs and any invalid inptuts.
		if (!std::cin.fail()) {
			if (inputValue > 0 && inputValue <= optionsRange) {
				if (checkoutPossible) {
					if (inputValue <= optionsRange - 3) {
						// remove item selected
						cartData.erase(cartData.begin() + (inputValue - 1));
						checkoutPossible = false;
					}
					if (inputValue == optionsRange - 2) {
						// checkout selected
						checkout();
						break;
					}
				}
				if (inputValue <= optionsRange - 2) {
					// remove item selected
					cartData.erase(cartData.begin() + (inputValue - 1));
					checkoutPossible = false;
				}
				if (inputValue == optionsRange - 1) {
					// increase balance selected
					increaseBalance();
				} else if (inputValue == optionsRange) {
					// back selected
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

void User::increaseBalance() {
	while (activeState) {
		system("cls");
		orderPrice = 0.0f;

		std::cout << "  Location: Home << View Cart << Increase Balance" << "  |  ";
		std::cout << "Order Count: " << cartData.size() << std::endl;
		std::cout << "\n\n";

		for (int i = 0; i < cartData.size(); i++) {
			orderPrice += categoryData[cartData[i].categoryID].itemData[cartData[i].itemID].price;
		}
		std::cout << "Order Price: \x9C" << orderPrice << "\n\n";

		std::cout << "Current Balance: \x9C" << balance << std::endl;
		std::cout << "\n\n-------------- \n";

		if (std::cin.fail() || inputError) {
			std::cin.clear();
			std::cin.ignore(254, '\n');
			std::cout << "Ooops. Looks like you entered an invalid input. Please try again!" << std::endl;
		}
		std::cout << "Please enter a how much you would like to add to your current balance. MAX  \x9C" << "25: \x9C";
		std::cin >> balanceInput;

		// Increasing the users balance so long as the value that they enter is less than £25
		if (!std::cin.fail()) {
			if (balanceInput <= 25) {
				balance += balanceInput;
				inputError = false;
				break;
			} else {
				inputError = true;
			}
		}

		Sleep(100);
	}
}

void User::checkout() {
	while (activeState) {
		system("cls");
		if (!checkoutComplete) {
			orderPrice = 0.0f;
			std::cout << "  Balance: \x9C" << balance << "  |  ";
			std::cout << "Location: Home << View Cart << Checkout";
			std::cout << "\n\n-------------- \n";
			std::cout << "\n";

			std::cout << "Checkout - Order count: " << cartData.size() << "\n\n";
			for (int i = 0; i < cartData.size(); i++) {
				orderPrice += categoryData[cartData[i].categoryID].itemData[cartData[i].itemID].price;
			}
			std::cout << "Checkout - Order Price: \x9C" << orderPrice << "\n";
			std::cout << "\n--------------\n";
			std::cout << "1: yes \n";
			std::cout << "2: no \n";
			std::cout << "\n\n";
			optionsRange = 2;

			if (std::cin.fail() || inputError) {
				std::cin.clear();
				std::cin.ignore(254, '\n');
				std::cout << "Ooops. Looks like you entered an invalid input. Please try again!" << std::endl;
			}
			std::cout << "Please confirm that you would like to checkout: ";
			std::cin >> inputValue;

			if (!std::cin.fail()) {
				if (inputValue > 0 && inputValue <= optionsRange) {
					if (inputValue <= optionsRange - 1) {
						// yes selected
						if (balance >= orderPrice) {
							checkoutComplete = true;
							inputError = false;
						}
					} else if (inputValue == optionsRange) {
						// no selected
						inputError = false;
						break;
					}
				} else {
					inputError = true;
				}
			}
		} else {
			balance -= orderPrice;
			cartData.clear();
			checkoutComplete = false;
			std::cout << "Items have been dispensed. Thank you for using this vending machine! \n";
			system("pause");
			break;
		}
		Sleep(100);
	}
}

void User::clearCart() {
	cartData.clear();
}

void User::pushItemCart(int _categoryID, int _itemID) {
	CartClass.categoryID = _categoryID;
	CartClass.itemID = _itemID;

	cartData.push_back(CartClass);
}

float User::getBalance() {
	return balance;
}

std::vector<UserCart> User::getCartData() {
	return cartData;
}