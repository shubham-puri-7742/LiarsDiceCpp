#pragma once
#include <string>
#include "Die.h"
#define MAXDICE 5 // Allows easy creation of variant games

class Player {
	std::string name;
	Die dice[MAXDICE];
	int diceInPlay = MAXDICE;

public:
	Player();
	Player(std::string playerName);
	std::string getName();
	void setName(std::string playerName);
	void rollDice(); // Rolls all the dice in play
	void showDice();
	void lose();
	bool inPlay();
	int count(int val); // The number of dice with a certain value in the player's roll
};