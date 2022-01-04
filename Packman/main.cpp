#include <string>
#include <algorithm>
#include "Game.h"
#include "Silent.h"

//Amit Leibovitch : 318659745
//Maayan Mashhadi : 318702230

bool cmdOptionExists(char** begin, char** end, const std::string& option);

int main(int argc, char* argv[])
{
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	int input;
	cin >> colors;
	Game game(colors);
	vector<string> screen_files;
	if (argc != 1)
	{
		if (strcmp(argv[1], "-save") == 0)
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
				char whichBoard = game.choseBoard(screen_files);
				game.createResultFile(whichBoard - 'a');

			}
		}
		else if (strcmp(argv[1], "-load") == 0)
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
		else if (strcmp(argv[1], "-load [-silent]") == 0)
		{
			Silent loadMode(colors);
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
	}

	else {
		input = game.printMenu();
		if (input != 2)
		{
			screen_files = game.loadFiles();
			for (int i = 0; i < 3; i++)
			{
				game.run(screen_files[i], input);
				if (game.getPacman().getLives() == 0) {
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
	return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}