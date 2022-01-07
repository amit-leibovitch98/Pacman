#include "Silent.h"

void Silent::start()
{
	int till_fruit_appear = 0;
	int fruit_pace = 0;
	bool ghostPace = true;
	bool collision = false;
	while (inProgress) 
	{
		if (collision)
		{
			//if the pacman meet ghost
			pacman.initLocations(pacman.getinitLocation());
			pacman.setHowManySteps(0);
			for (int i = 0; i < ghosts.size(); i++) {
				ghosts[i].initLocations(ghosts[i].getinitLocation());
				ghosts[i].setHowManySteps(0);
			}
			collision = false;
		}
		if (!collision) {
			if (pacman.getHowManySteps() == 0) {
				pacman.setHowManySteps(decode(pacman, pacmanSteps[0].getDiraction()));
			}
			pacman.setLastLocation(pacman.getCurrLocation());
			pacman.move();
			board.movePacman(pacman, COLORS);
			pacman.setHowManySteps(pacman.getHowManySteps() - 1);
			collision = caseCollisionPacman();
			if (ghostPace == true)
			{
				for (int i = 0; i < ghosts.size(); i++)
				{
					if (ghosts[i].getHowManySteps() == 0) {
						ghosts[i].setHowManySteps(decode(ghosts[i], ghostSteps[0].getDiraction()));
					}
					ghosts[i].setLastLocation(ghosts[i].getCurrLocation());
					ghosts[i].move();
					board.moveGhost(ghosts[i], pacman, COLORS);
					ghosts[i].setHowManySteps(ghosts[i].getHowManySteps() - 1);
				}
				fruit_pace++;
			}
			if (!collision)
			{
				collision = caseCollisionPacman();
			}

		}
		ghostPace = !ghostPace;
		checkGameStatus();
		countPaces++;
	}
}

bool Silent::compareFiles(string file_name_1, string file_name_2)
{
	ifstream file1, file2;
	char* line1, * line2;

	line1 = new char[55];
	line2 = new char[55];

	file1.open(file_name_1);
	file2.open(file_name_2);
	bool res = true;

	while (res && !file1.eof())
	{
		file1.getline(line1, 55);
		file2.getline(line2, 55);

		if (strcmp(line1, line2))
			res = false;

	}
	return res;
}

void Silent::bigRun(int input)
{
	run(input);

	if (compareFiles(result_file_name, screen_files[(input + 1) * 3 + 1])) //      ,      4,7,10
	{
		cout << "Test succeeded! :)" << endl;
	}
	else
	{
		cout << "Test Faild! :(" << endl;
	}
}
