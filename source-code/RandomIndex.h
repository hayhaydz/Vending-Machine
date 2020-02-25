#ifndef RANDOMINDEX_H
#define RANDOMINDEX_H
#include <iostream>
#include <random>
#include <time.h>

/*
	Class: RandomIndex
	Description: This is the RandomIndex class, this class is used to generate a random number for the Load class loading bar.
*/


#pragma once
class RandomIndex {
private:
	std::random_device rd;
	int max_roll;
	typedef std::mt19937 MyRng;
	MyRng rng;
	std::uniform_int_distribution<int> dice;
public:
	RandomIndex(int LR, int MR) :max_roll(MR), rng(rd()), dice(std::uniform_int_distribution<>(LR, MR)) {
		rng.seed(::time(NULL));
	}

	int roll() {
		return dice(rng);
	}
};

#endif

