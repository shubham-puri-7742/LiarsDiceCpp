#include <iostream>
#include <fstream>
#include <sstream>
#include "Game.h"

int Game::count(int val) { // Count the number of dice with face = val in the pool
    int count = 0;
    
    for (int i = 0; i < totalPlayers; i++) {
        if (players[i].inPlay()) { // For each player still in play
            count += players[i].count(val); // Add the number of dice showing the given face
        }
    }
    
    return count;
}

void Game::callOut() { // Calling out a lie
    int num = guess.getNum();

    // Find out the liar; the winner starts next
    if (count(guess.getVal()) >= num) { // Lie wrongly called out
        players[currentPlayer].lose();
        next = lastPlayer - 1;
    }
    else { // The last player had lied
        players[lastPlayer].lose();
        next = currentPlayer - 1;
    }

    if (!(players[currentPlayer].inPlay())) { // If the current player is out of the game
        players.erase(players.begin() + currentPlayer);
        totalPlayers--;

        if (lastPlayer > currentPlayer) { // Because vector indices shift by 1
            next--;
        }
    }
    if (!(players[lastPlayer].inPlay())) { // If the last player is out of the game
        players.erase(players.begin() + lastPlayer);
        totalPlayers--;

        if (currentPlayer > lastPlayer) { // Because vector indices shift by 1
            next--;
        }
    }

    for (int i = 0; i < totalPlayers; i++) {
        players[i].rollDice(); // Roll each player's dice after a call is evaluated
    }

    lastGuess.clear(); // Reset the last guess
}

void Game::turn() { // Logic for each turn
    std::string line;
    int choice;
    bool validTurn = false; // Decides whether to repeat the same player's turn or pass on to the next

    do {
        std::cout << players[currentPlayer].getName() << "'s turn:\n1. View your dice\n2. Make your guess/Raise the guess\n";
        if (lastGuess.getNum() != -1) { // If a player has made a guess previously
            std::cout << "3. Call out the liar\n";
        }

        std::getline(std::cin, line); // Get the user's input
        std::stringstream linestream(line);
        linestream >> choice;

        switch (choice) {
        case 1: // View your dice
            players[currentPlayer].showDice();
            break;
        case 2: // Make a guess
            guess.collectGuess(lastGuess);
            lastPlayer = currentPlayer;
            validTurn = true;
            break;
        case 3: // Call out the liar
            if (lastGuess.getNum() == -1) { // If the last guess has not been set
                continue;
            }

            callOut(); // This should be allowed only if a guess has been made previously
            validTurn = true;
            break;
        }
    } while (!validTurn); // Repeat until the guess is raised or a liar is called out
}

void Game::round() { // Logic for each round, which ends on the last man standing condition
    bool canPlay;
    int playersInPlay = 0, lastPlayer = 0;

    do {
        ++next %= totalPlayers; // Wrap around the edges when giving the next turn

        if (!players[next].inPlay()) { // Skip players not in play
            next++;
        }

        currentPlayer = next;

        turn();
    } while (totalPlayers > 1);

    // Declaring the winner (because the loop breaks when there is only one player left)
    std::cout << "\n" << players[lastPlayer].getName() << " is the winner!\nThanks for playing.\n\n";
}

void Game::play(int n) { // Initialises the game with n players and starts the round
    totalPlayers = n;
    for (int i = 0; i < totalPlayers; i++) { // Create new players and make a vector of players
        std::string name;
        std::cout << "\nEnter your name, Player " << i + 1 << ": ";
        std::getline(std::cin, name);

        Player* player = new Player(name);
        players.push_back(*player);

        players[i].rollDice(); // First roll dice when initialising the players
    }

    round();
}

void Game::viewRules() {
    std::ifstream f("LiarsDiceRules.txt"); // Open the .txt in input mode

    if (!f) { // Check if the file exists
        std::cout << "ERROR: NO RULES FILE FOUND";
        return;
    }

    std::string line;

    while (std::getline(f, line)) { // Display each line
        std::cout << line << '\n';
    }

    std::cout << std::endl;

    f.close();
}
