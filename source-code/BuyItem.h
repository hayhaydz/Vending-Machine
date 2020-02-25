#ifndef BUYITEM_H
#define BUYITEM_H

#include <iostream>

#include "Load.h"
#include "User.h"

/*
	Class: BuyItem
	Description: This is the BuyItem class, this is used to display all of the items for each necessary category to the user, it also handles updating the users cart when the user decides to add an item to their cart.
*/


#pragma once
class BuyItem {
	public:
		void setup(std::vector<Category> _categoryData, int _categoryIndex, float _userBalance, std::vector<UserCart> _cartData);
		void display();
		std::vector<UserCart> getCartData();
		float getUserBalance();
		void calculateLongestName();

	private:
		bool activeState;
		bool inputError;
		bool itemAdded;

		int categoryIndex;
		int inputValue;
		int optionsRange;
		int longestNameLength;
		int nameLengthDifference;

		std::vector<Category> categoryData;
		UserCart cartClass;
		std::vector<UserCart> cartData;

		float userBalance;

		std::string nameSpacer;
};

#endif

