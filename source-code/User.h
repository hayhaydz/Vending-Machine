#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <Windows.h>

#include "Load.h"
#include "UserCart.h"

/*
	Class: User
	Description: This is the User class, this handles all of the users details whilst using the vending machine such as their cart, balance but is also used to display the items within their cart and allow them to update their balance,
	also allowing the user to checkout their items.
*/


#pragma once
class User {
	public:
		void setup();
		void displayCart(std::vector<Category> _categoryData);
		void checkout();
		void increaseBalance();
		void clearCart();
		void pushItemCart(int _categoryID, int _itemID);
		
		static User* getInstance();
		float getBalance();
		std::vector<UserCart> getCartData();

	protected:
		float balance;
		UserCart CartClass;
		std::vector<UserCart> cartData;


	private:
		// Singleton instance - https://www.oreilly.com/library/view/c-cookbook/0596007612/ch08s10.html
		static User* inst_;
		//User(const User&);
		User();
		User& operator=(const User&);

		std::vector<Category> categoryData;

		bool activeState;
		bool inputError;
		bool checkoutPossible;
		bool checkoutComplete;
		bool checkoutError;

		int inputValue;
		float balanceInput;
		float orderPrice;
		int optionsRange;

};

#endif

