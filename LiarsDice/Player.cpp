#include "Player.h"
#include <iostream>

Player::Player() { // Default ctor
}

Player::Player(std::string playerName) { // Parametrised ctor
	name = playerName;
}

std::string Player::getName() {
	return name;
}

void Player::setName(std::string playerName) {
	name = playerName;
}

void Player::rollDice() {
	for (int i = 0; i < diceInPlay; i++) {
		dice[i].roll(); // roll each die in play
	}
}

void Player::showDice() { // Show the player's set of dice and hide them
	std::cout << "\nYour dice: ";
	for (int i = 0; i < diceInPlay; i++) { // Show all the dice
		std::cout << dice[i].getFaceVal();
		if (i != diceInPlay - 1) {
			std::cout << " ";
		}
		else {
			std::cout << '\r';
		}
	}

	std::cin.ignore();
	std::cout << "\x1b[A"; // ANSI escape sequence
	std::cout << "TOP SECRET CLEARANCE REQUIRED!\n"; // Hide the player's dice
}

void Player::lose() { // Processing when a player has lost
	std::cout << "\n" << name << " lost the round ";
	diceInPlay--;
	if (inPlay()) { // Will have at least one die left
		std::cout << "and will continue with one less die.\n";
	}
	else { // no dice left
		std::cout << "and is out of the game.\n";
	}
}

bool Player::inPlay() {
	return diceInPlay > 0; // The player is in play if s/he has nonzero dice
}

int Player::count(int val) {

	std::cout << name << "'s dice: ";
	for (int i = 0; i < diceInPlay; i++) { // Display the dice without hiding them when showing the result
		std::cout << dice[i].getFaceVal() << " ";
	}
	std::cout << std::endl;

	int count = 0;
	for (int i = 0; i < diceInPlay; i++) {
		if (dice[i].getFaceVal() == val) { // If the face value matches the given value, increment the count
			count++;
		}
	}
	return count;
}
