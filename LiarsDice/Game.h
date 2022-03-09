#pragma once
#include "Guess.h"
#include "Player.h"
#include <vector>

class Game {
	Guess guess, lastGuess;
	std::vector<Player> players;
	int totalPlayers, currentPlayer, lastPlayer;
	int next = -1;

	int count(int val);
	void callOut();
	void turn();
	void round();

public:
	void play(int n);
	void viewRules();
};

