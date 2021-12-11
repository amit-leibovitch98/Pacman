#include "Game.h"


int main(int argc, char* argv[])
{
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	cin >> colors;
	Game game(colors);
	for (int i = 1; i < argc; i++)
	{
		game.openFile(argv[i]);
		game.run();
		//close and delete file
	}
	return 0;
}