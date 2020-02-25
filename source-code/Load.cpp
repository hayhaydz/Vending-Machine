#include "Load.h"

Load* Load::inst_ = NULL;

Load* Load::getInstance() {
	if (inst_ == NULL) {
		inst_ = new Load();
	}

	return inst_;
}

Load::Load() {
	// Asynchronously both loading the data and displaying a loading visual element.
	std::future<void> startloading = std::async(std::launch::async, [this] { display(); });
	setup();
	while (!dataLoaded) {
		// Waiting for loading to be completed;
	}
}

void Load::setup() {
	key = 1234;
	fileName = "data.txt";
	decrypt();
	loadData();
}

// Encryption and Decryption - https://gist.github.com/vatz88/750007588adf8c26a98ad428249351ba - https://codescracker.com/cpp/program/cpp-program-encrypt-file.htm
void Load::encrypt() {
	encFileName = "e_" + fileName;

	srand(key);

	OutputData.open(fileName);
	OutputData >> std::noskipws;

	char ch;

	InputData.open(encFileName);

	// Shifting character codes of data by random number based off of the key defined.
	while (OutputData.eof() == 0) {
		OutputData >> ch;
		n = 1 + rand() % 9;
		if (ch != ' ' && ch != '\n') {
			ch = ch + n;
		}

		InputData << ch;
	}

	OutputData.close();
	InputData.close();
}

void Load::decrypt() {
	decFileName = "d_" + fileName;
	srand(key);
	OutputData.open("e_"+fileName);
	OutputData >> std::noskipws;

	char ch;

	// Reversing the shifting character codes of data by random number based off of the key defined.
	InputData.open(decFileName);
	while (OutputData.eof() == 0) {
		OutputData >> ch;
		n = 1 + rand() % 9;
		if (ch != ' ' && ch != '\n') {
			ch = ch - n;
		}

		InputData << ch;
	}

	OutputData.close();
	InputData.close();
}

void Load::loadData() {
	// Loading data using the necessary structured classes.
	currentStage = "categories";
	currentCategoryIndex = 0;

	infile.open("d_" + fileName);
	for (std::string line; getline(infile, line);) {
		counter = 0;
		std::stringstream ss(line);
		while (ss.good()) {
			counter++;
			getline(ss, substr, ':');
			//std::cout << "substr: " << substr << std::endl;
			if (currentStage == "categories" && substr != "```") {
				switch (counter) {
					case 1:
						CategoryClass.id = std::stoi(substr);
						break;
					case 2:
						CategoryClass.name = substr;
						break;
				}
			}

			// Depending on different characters different data is placed into different classes.
			if (currentStage == "items" && substr != "===") {
				switch (counter) {
					case 1:
						CategoryClass.ItemClass.id = std::stoi(substr);
						break;
					case 2:
						CategoryClass.ItemClass.name = substr;
						break;
					case 3:
						CategoryClass.ItemClass.price = std::stof(substr);
						break;
					case 4:
						CategoryClass.ItemClass.categoryID = std::stoi(substr);
						break;
				}
			}
			if (substr == "```") {
				currentStage = "items";
				counter = 0;
			}
			if (substr == "===") {
				currentCategoryIndex++;
				counter = 0;
			}
		}

		if (currentStage == "categories" && CategoryClass.name != "") {
			ss.str("");
			categoryData.push_back(CategoryClass);
		}

		if (currentStage == "items" && CategoryClass.ItemClass.name != "") {
			ss.str("");
			categoryData[currentCategoryIndex].itemData.push_back(CategoryClass.ItemClass);
			CategoryClass.ItemClass.name = "";
		}
	}
	infile.close();

	if (remove("d_data.txt") != 0) {
		perror("Error deleting decrypted file.");
	}
}
// Loading Progress Bar - https://stackoverflow.com/questions/52750976/how-to-make-a-loading-bar-in-the-console-c/52750986
void Load::display() {
	// Displaying a visual loading progress bar.
	dataLoaded = false;
	RandomIndex RI(100, 500);
	loadingProgress = 0.0;

	while (loadingProgress < 1.1) {
		barWidth = 100;
		loadingPos = barWidth * loadingProgress;
		sleepTime = RI.roll();

		Sleep(sleepTime);

		std::cout << "[";
		for (int i = 0; i < barWidth; i++) {
			if(i < loadingPos) {
				std::cout << "=";
			} else if(i == loadingPos) {
				std::cout << ">";
			} else {
				std::cout << " ";
			}
		}

		std::cout << "]" << int(loadingProgress * 100) << " %\r";
		std::cout.flush();

		loadingProgress += 0.1;
	}

	std::cout << std::endl;
	dataLoaded = true;
}

std::vector<Category> Load::getData() {
	return categoryData;
}
