#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "Item.h"


/*
	Class: Category
	Description: This is the Category class, this class is used as an object to store the details of each category and a vector of the items within each category.
*/


#pragma once
class Category {
	public:
		Category();
		int id;
		std::string name;
		Item ItemClass;
		std::vector<Item> itemData;

	private:
};

#endif

