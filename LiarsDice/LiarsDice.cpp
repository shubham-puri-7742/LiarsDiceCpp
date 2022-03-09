#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Die.h"
#include "Player.h"
#include "Guess.h"
#include "Game.h"

using namespace std;

int main() {

    srand(time(nullptr));

    int n; // Number of players
    string in;
    Game gameInstance;

    gameInstance.viewRules();

    do {
        cout << "Let the game begin!\nEnter the number of players (0 to exit): ";
        getline(cin, in);
        stringstream linestream(in);
        linestream >> n;
        
        if (n > 1) {
            gameInstance.play(n); // Play with n players
        }
        else if (n == 1) {
            cout << "\nERROR: At least 2 players required to play. Enter again: ";
        }
        else {
            break; // Quit
        }

    } while (n >= 0); // At least 2 players

    return 0;
}

