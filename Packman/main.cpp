#include <string>
#include <algorithm>
#include "Game.h"
#include "Silent.h"


//Amit Leibovitch : 318659745
//Maayan Mashhadi : 318702230

int main(int argc, char* argv[])
{
	bool colors, exit = false;
	int input, pacman_lives;
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
				for (int i = 0; i < 3 && !exit; i++)
				{
					screen_files = game->loadFiles();

					exit = game->run(screen_files[i], input, i);

					if (!exit)
					{
						pacman_lives = game->getPacman().getLives();

						if (pacman_lives == 0)
						{
							game->restart();
							input = game->printMenu();
							i = -1;
						}
						delete game;
						game = new Game(colors, pacman_lives);
					}
				}
			}
			else
			{
				char whichBoard = game->chooseBoard(screen_files);
			}
		}
		else if (strcmp(argv[1], "-load") == 0)
		{
		if (argc > 2)
		{
			if (strcmp(argv[2], "[-silent]") == 0)
			{
				Silent* silent = new Silent();

				for (int i = 0; i < 3; i++)
				{
					silent->loadFiles();
					silent->sRun(i);

					pacman_lives = silent->getPacman().getLives();

					if (pacman_lives == 0)
					{
						silent->restart();
						i = -1;
					}


					delete silent;
					silent = new Silent(pacman_lives);
				}
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

				pacman_lives = loadMode->getPacman().getLives();

				if (pacman_lives == 0)
				{
					loadMode->restart();
					i = -1;
				}
				delete loadMode;
				loadMode = new Load(colors, 2, pacman_lives);
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
			for (int i = 0; i < 3 && !exit; i++)
			{
				screen_files = game->loadFiles();
				exit = game->run(screen_files[i], input, i);

				if (!exit)
				{
					pacman_lives = game->getPacman().getLives();

					if (pacman_lives == 0)
					{
						game->restart();
						input = game->printMenu();
						i = -1;
					}
					delete game;
					game = new Game(colors, pacman_lives);
				}
			}
		}
		else
		{
			game->chooseBoard(screen_files);
		}
	}
	return 0;
}