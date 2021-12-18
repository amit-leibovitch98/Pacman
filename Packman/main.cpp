#include <string>
#include "Game.h"


int main()
{
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	int input;
	cin >> colors;
	Game game(colors);

	vector<string> screen_files = game.loadFiles();

	game.printMenu();

	cin >> input;
	if (input != 2)
	{
		for (int i = 0; i < 3; i++)
		{
			game.run(screen_files[i], input);
		}
	}
	else
	{
		game.run(screen_files[0], input);
	}

	return 0;
}
