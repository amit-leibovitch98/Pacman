#include "Game.h"

int main() {
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	cin >> colors;
	Game game(colors);
	game.run();
	return 0;
}