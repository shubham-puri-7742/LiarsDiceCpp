#pragma once
#include <vector>

class Guess { // Basically an ordered pair
	std::pair<int, int> g; // num-val pair. 2,5 = two fives (2 is num, 5 is val)
	void parseInput(std::string input); // To parse the guess

	static const std::string val[7];
	static const std::string vals[7];

	// for generating number names
	static const std::string ones[20];
	static const std::string tens[10];

	std::string numInWords(int num);

	bool isAValidGuess(Guess lastGuess); // Checks validity against the last guess

	template<typename T>
	T fromString(const std::string& str);

public:
	Guess();
	Guess(int num, int val);
	Guess(const Guess& other);
	void collectGuess(Guess& lastGuess);
	void display();
	int getNum();
	int getVal();
	bool empty();
	void clear();
};

template<typename T>
inline T Guess::fromString(const std::string& str) {
	std::istringstream ss(str);
	T result;
	ss >> result;
	return result;
}