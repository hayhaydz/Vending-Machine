#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>

#include "User.h";

/*
	Class: Options
	Description: This is the Options class, this is used to display any possible helpful advice and guidance for the user when they are using the vending machine.
*/


#pragma once
class Options {
	public:
		void setup(float _userBalance, std::vector<UserCart> _cartData);
		void display();

	private:
		bool activeState;
		bool inputError;

		int inputValue;
		int optionsRange;

		std::vector<UserCart> cartData;

		float userBalance;

};

#endif

