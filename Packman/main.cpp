#include <string>
#include <algorithm>
#include "Game.h"
#include "Silent.h"

//Amit Leibovitch : 318659745
//Maayan Mashhadi : 318702230

int main(int argc, char* argv[])
{
	bool colors;
	int input;
	
	vector<string> screen_files;

	//------------------------------------------------with argumants--------------------------------------------------------------
	if (argc != 1)
	{
		if (strcmp(argv[1], "-save") == 0)
		{
			cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
			cin >> colors;

			Game* game = new Game(colors);

			input = game->printMenu();

			if (input != 2)
			{
				for (int i = 0; i < 3; i++)
				{
					screen_files = game->loadFiles();

					game->run(screen_files[i], input);

					if (game->getPacman().getLives() == 0)
					{
						game->restart();
						input = game->printMenu();
						i = -1;
					}
					delete game;
					game = new Game(colors);
				}
			}
			else
			{
				char whichBoard = game->choseBoard(screen_files);
			}
		}
		else if (strcmp(argv[1], "-load") == 0)
		{
		if (strcmp(argv[2], "[-silent]") == 0)
		{
			Silent* silent = new Silent();

			for (int i = 0; i < 3; i++)
			{
				silent->bigRun(i);
				silent->loadFiles();

				if (silent->getPacman().getLives() == 0)
				{
					silent->restart();
					i = -1;
				}


				delete silent;
				silent = new Silent();
			}
		}
		else
		{
			cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
			cin >> colors;

			Load* loadMode = new Load(colors, 2);

			for (int i = 0; i < 3; i++)
			{
				loadMode->loadFiles();
				loadMode->run(i);

				if (loadMode->getPacman().getLives() == 0)
				{
					loadMode->restart();
					i = -1;
				}
				delete loadMode;
				loadMode = new Load(colors, 2);
			}
		}
		}
		
	}

	//------------------------------------------------no argumants - regulat game--------------------------------------------------------------

	else 
	{
		Game* game = new Game(colors);

		input = game->printMenu();
		if (input != 2)
		{
			for (int i = 0; i < 3; i++)
			{
				screen_files = game->loadFiles();
				game->run(screen_files[i], input);

				if (game->getPacman().getLives() == 0)
				{
					game->restart();
					input = game->printMenu();
					i = -1;
				}
				delete game;
				game = new Game(colors);
			}
		}
		else
		{
			game->choseBoard(screen_files);
		}
	}
	return 0;
}