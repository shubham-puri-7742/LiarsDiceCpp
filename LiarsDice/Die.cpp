#include "Die.h"
#include <cstdlib>

Die::Die() {
	faceVal = -1;
}

void Die::roll() {
	faceVal = (rand() % 6 + 1); // Random int in the range 1 to 6 (inclusive)
}

int Die::getFaceVal() {
	return faceVal;
}