#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <conio.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <future>
#include <thread>
#include <Windows.h>

#include "Category.h"
#include "RandomIndex.h"


/*
	Class: Load
	Description: This is the Load class, this class holds the ability to encrypt and decrypt the vending machines stored data text file, it is currently however setup to only decrypt the already encrypted file,
	once it has decrypted the file it will then read the txt file and push the data as objects into the necessary either category class or item class.
*/


#pragma once
class Load {
	public:
		void setup();
		void encrypt();
		void decrypt();
		void loadData();
		void display();
		bool dataLoaded;

		static Load* getInstance();
		std::vector<Category> getData();

	protected:
		Category CategoryClass;
		std::vector<Category> categoryData;

	private:
		// Singleton instance - https://www.oreilly.com/library/view/c-cookbook/0596007612/ch08s10.html
		static Load* inst_;
		//Load(const Load&);
		Load();
		Load& operator=(const Load&);

		// File Data Handling
		std::string fileData;
		std::ifstream infile;
		std::string substr;

		// File Data Managing
		int counter;
		std::string currentStage;
		int currentCategoryIndex;

		// File Data Encryption and Decryption
		int key, n;
		std::string fileName;
		std::string encFileName;
		std::string decFileName;
		std::ifstream OutputData;
		std::ofstream InputData;

		// File Loading
		float loadingProgress;
		int barWidth;
		int loadingPos;
		int sleepTime;
};

#endif

