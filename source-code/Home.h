#ifndef HOME_H
#define HOME_H

#include <iostream>
#include <iomanip>
#include <Windows.h>

#include "Load.h"
#include "User.h"
#include "BuyItem.h"
#include "Options.h"

/*
	Class: Home
	Description: This is the main displaying screen for the vending machine. This displays all of the categories that are available to the user.
	The loading of the vending machine data (Categories, Items, Prices and so on) is also done within the Home class, when the Load class is initialised in the classes header.
*/

#pragma once
class Home {
	public:
		Load* Load = Load::getInstance();
		User* User = User::getInstance();
		BuyItem BuyItem;
		Options Options;
		Home();
		void setup();
		void display();

	private:
		bool activeState;
		bool inputError;

		int inputValue;
		int optionsRange;

		std::vector<Category> categoryData = Load -> getData();
		std::vector<UserCart> cartData = User -> getCartData();

		float userBalance = User -> getBalance();

};

#endif

