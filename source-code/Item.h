#ifndef ITEM_H
#define ITEM_H

/*
	Class: Item
	Description: This is the Item class, this class is used as an object to store all of the necessary details of each item such as it's price, name and ID.
*/

#pragma once
class Item {
	public:
		Item();
		int id;
		std::string name;
		float price;
		int categoryID;

	private:
};

#endif

