#include "BuyItem.h"

void BuyItem::setup(std::vector<Category> _categoryData, int _categoryIndex, float _userBalance,std::vector<UserCart> _cartData) {
	categoryData = _categoryData;
	categoryIndex = _categoryIndex;
	userBalance = _userBalance;
	cartData = _cartData;
	itemAdded = false;
	inputError = false;
	activeState = true;
	longestNameLength = 0;
	nameLengthDifference = 0;
	nameSpacer = "";
	display();
}

void BuyItem::display() {
	while (activeState) {
		system("cls");

		// Displaying the details of the user, their balance, location within the vending machine and total count of their cart.
		std::cout << "  Balance: \x9C" << userBalance << "  |  ";
		std::cout << "Location: Home << " << categoryData[categoryIndex].name << "  |  ";
		std::cout << "Order Count: " << cartData.size() << std::endl;
		std::cout << "\n\n";

		// This works out the length of the longest name within the category of items.
		calculateLongestName();

		std::cout << "Items: \n";
		std::cout << "-------------- \n\n";
		std::cout << "  ID";
		// Different amount of spacing depending on whether there is more than 10 items or not.
		if (categoryData[categoryIndex].itemData.size() > 10) {
			std::cout << "  |";
		} else {
			std::cout << " |";
		}
		std::cout << " Name";
		// Working out how much spacing is needed for each items name;
		nameLengthDifference = longestNameLength - 4;
		for (int i = 0; i < nameLengthDifference; i++) {
			nameSpacer += " ";
		}
		std::cout << nameSpacer << " |";
		std::cout << " Price";
		std::cout << "\n\n";
		nameSpacer = "";

		// Displaying all of the items in the category to the user.
		for (int i = 0; i < categoryData[categoryIndex].itemData.size(); i++) {
	
			std::cout << "  " << categoryData[categoryIndex].itemData[i].id + 1;
			if (categoryData[categoryIndex].itemData.size() > 10 && i < 9) {
				std::cout << " ";
			}
			std::cout<< "  | ";

			if (categoryData[categoryIndex].itemData[i].name.length() < longestNameLength) {
				nameLengthDifference = longestNameLength - categoryData[categoryIndex].itemData[i].name.length();
				for (int x = 0; x < nameLengthDifference; x++) {
					nameSpacer += " ";
				}
			}
			std::cout << categoryData[categoryIndex].itemData[i].name << nameSpacer << " | \x9C" << categoryData[categoryIndex].itemData[i].price << std::endl;
			nameSpacer = "";
		}
		std::cout << "\n-------------- \n";
		std::cout << categoryData[categoryIndex].itemData.size() + 1 << ". ";
		std::cout << "back";
		optionsRange = categoryData[categoryIndex].itemData.size() + 1;

		std::cout << "\n\n";

		// Handling any invalid inputs that are made.
		if (std::cin.fail() || inputError) {
			std::cin.clear();
			std::cin.ignore(254, '\n');
			std::cout << "Ooops. Looks like you entered an invalid input. Please try again!" << std::endl;
		}
		if (itemAdded) {
			std::cout << "ITEM WAS ADDED TO YOUR CART SUCESSFULY! \n";
			itemAdded = false;
		}
		std::cout << "Please enter a number from 1-" << categoryData[categoryIndex].itemData.size() << " to add an item to your cart \nor enter a number from " << categoryData[categoryIndex].itemData.size() + 1 << "-" << optionsRange << " for one of the options: ";
		std::cin >> inputValue;

		// Handling the input that is made so long as it is valid.
		if (!std::cin.fail()) {
			if (inputValue > 0 && inputValue <= optionsRange) {
				if (inputValue <= optionsRange - 1) {
					// Item selected
					itemAdded = true;
					inputError = false;
					cartClass.categoryID = categoryIndex;
					cartClass.itemID = inputValue - 1;
					cartData.push_back(cartClass);

				} else if (inputValue == optionsRange) {
					// Exit selected
					inputError = false;
					activeState = false;
				}
			}
			else {
				inputError = true;
			}
		}

		Sleep(100);
	}
}

std::vector<UserCart> BuyItem::getCartData() {
	return cartData;
}

float BuyItem::getUserBalance() {
	return userBalance;
}

void BuyItem::calculateLongestName() {
	for (int i = 0; i < categoryData[categoryIndex].itemData.size(); i++) {
		if (categoryData[categoryIndex].itemData[i].name.length() > longestNameLength) {
			longestNameLength = categoryData[categoryIndex].itemData[i].name.length();
		}	
	}
}