#include <string>
#include "Game.h"
#include "Silent.h"

//Amit Leibovitch : 318659745
//Maayan Mashhadi : 318702230



int main(int argc, char* argv[])
{
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	int input;
	cin >> colors;
	//if()
	Game game(colors);
	vector<string> screen_files;

	if (strcmp(argv[1], "save") == 0)
	{
		screen_files = game.loadFiles();
		input = game.printMenu();

		if (input != 2)
		{
			for (int i = 0; i < 3; i++)
			{
				game.run(screen_files[i], input);
				game.createResultFile(i);
				 
				if (game.getPacman().getLives() == 0)
				{
					game.restart();
					input = game.printMenu();
					i = -1;
				}
			}
		}
		else
		{
			game.choseBoard(screen_files);

		}
	}
	else
	{
		Load loadMode(colors, 2);
		loadMode.loadFiles();

		for (int i = 0; i < 3; i++)
		{
			loadMode.run(i);
			if (loadMode.getPacman().getLives() == 0) 
			{
				loadMode.restart();
				i = -1;
			}
		}
	}
	return 0;
}
