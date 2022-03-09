#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "Guess.h"

const std::string Guess::val[7] = { "", "one", "two", "three", "four", "five", "six" }; // Value names in the singular
const std::string Guess::vals[7] = { "", "ones", "twos", "threes", "fours", "fives", "sixes" }; // Value names in the plural

// for generating number names
const std::string Guess::ones[20] = { "", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine ", "ten ",
						"eleven ", "twelve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen " };
const std::string Guess::tens[10] = { "", "", "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety " };

void Guess::parseInput(std::string input) {
	std::stringstream ss(input);
	std::string substr;
	std::vector<std::string> v;

	while (ss.good()) {
		getline(ss, substr, ','); // parse on comma
		v.push_back(substr);
	}
	int num = fromString<int>(v[0]);
	int val = fromString<int>(v[1]);

	g = std::make_pair(num, val); // Store a pair of two ints
}

std::string Guess::numInWords(int num) { // Works for up to 99
	std::string name = "";

	if (num > 19) { // The 'regular' number names (20 onwards)
		name += tens[num / 10] + ones[num % 10];
	}
	else { // Up to the teens
		name += ones[num];
	}
	
	return name;
}

bool Guess::isAValidGuess(Guess lastGuess) {
	return ((g.first > -1) // At least zero
		&& (g.second > 0 && g.second < 7) // 1-6 on a dice
		&& (g.first > lastGuess.getNum())); // If the first number is increased from the last guess
}

Guess::Guess() { // Initialise to -1,-1 to allow all options
	g = std::make_pair(-1, -1);
}

Guess::Guess(int num, int val) { // Parametrised ctor
	g = std::make_pair(num, val);
}

Guess::Guess(const Guess& other) { // copy ctor
	g = other.g;
}

void Guess::collectGuess(Guess& lastGuess) {
	std::string input;
	std::regex pattern ("[0-9]+,[1-6]"); //x,y format where y is a dice face

	std::cout << "Enter your guess (e.g. 2,5 = 'two fives').";

	do{
		// Get the input
		std::cout << "\nYou MUST increase the first number; The second number MUST be a dice face (1-6): ";
		getline(std::cin, input);

		// Check if valud
		if (!std::regex_match(input, pattern)) { // If the user enters anything except two comma-separated numbers
			std::cout << "\nINVALID INPUT! Enter TWO comma-separated numbers (e.g. 2,5 = 'two fives').";
			continue;
		}

		// Parse as needed
		parseInput(input);
	} while (!isAValidGuess(lastGuess));

	lastGuess = *this;

	display();
}

void Guess::display() {
	if (getNum() > 1) {
		std::string number = numInWords(getNum());
		std::cout << "You say there are at least " << number << vals[getVal()] << ". (Press ENTER to continue)" << std::endl;
	}
	else if (getNum() == 1) { // At least one of the face
		std::cout << "You say there is at least one " << val[getVal()] << ". (Press ENTER to continue)" << std::endl;
	}
	else { // Zero; see do loop condition in collectGuess()
		std::cout << "You say there may be no " << vals[getVal()] << ". (Press ENTER to continue)" << std::endl;
	}
	std::cin.ignore();
}

int Guess::getNum() {
	return g.first;
}

int Guess::getVal() {
	return g.second;
}

bool Guess::empty() { // Because the default value is -1,-1; see clear()
	return (g.first == -1 || g.second == -1);
}

void Guess::clear() {
	g.first = g.second = -1;
}
