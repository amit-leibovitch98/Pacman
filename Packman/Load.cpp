#include "Load.h"

bool Load::endswith(string file_name, string suffix)
{

	return file_name.size() >= suffix.size() && 0 == file_name.compare(file_name.size() - suffix.size(), suffix.size(), suffix);

}

void Load::loadFiles()
{
	string prefix = "/.";


	for (const auto& file : fs::directory_iterator("."))
	{
		if (endswith(file.path().string(), "screen"))
		{
			screen_files.push_back(file.path().string());
		}
		else if (endswith(file.path().string(), "steps"))
		{
			screen_files.push_back(file.path().string());
		}
		else if (endswith(file.path().string(), "result"))
		{
			screen_files.push_back(file.path().string());
		}

	}

	if (screen_files.size() < 9)
		//throw exception
		cout << "There are not enough board files on diractory (less then 3)" << endl;
	else
	{
		for (auto i = screen_files.begin(); i != screen_files.end(); i++)
		{
			string file_name = i->substr(prefix.length());
		}
	}


}

void Load::run(int input)
{
	ifstream board_file;
	if (input == 0) {
		board_file.open(screen_files[0]);
	}
	if (input == 1) {
		board_file.open(screen_files[3]);
	}
	if (input == 2) {
		board_file.open(screen_files[6]);
	}

	if (!board_file)
	{
		//throw exception
		cout << "Error with infile" << endl;
		exit(-1);
	}

	board.fileToMatrix(board_file, '$', pacman, ghosts);

	board_file.close();

	board.printBoard(pacman, ghosts, COLORS);
	if (input == 0)
	{
		steps(screen_files[1]);
	}
	else if (input == 1)
	{
		steps(screen_files[4]);
	}
	if (input == 2)
	{
		steps(screen_files[7]);
	}
	start();
}

void Load::start()
{
	int till_fruit_appear = 0;
	bool ghostPace = true;
	bool collision = false;

	while (inProgress) 
	{
		if (collision)
		{
			//if the pacman meet ghost
			pacman.initLocations(pacman.getinitLocation());
			pacman.setHowManySteps(0);
			for (int i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].initLocations(ghosts[i].getinitLocation());
				ghosts[i].setHowManySteps(0);
			}
			board.printBoard(pacman, ghosts, COLORS);
			collision = false;
		}
		if (!collision)
		{
			if (pacman.getHowManySteps() == 0)
			{
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
					if (ghosts[i].getHowManySteps() == 0)
					{
						ghosts[i].setHowManySteps(decode(ghosts[i], ghostSteps[0].getDiraction()));
					}
					ghosts[i].setLastLocation(ghosts[i].getCurrLocation());
					ghosts[i].move();
					board.moveGhost(ghosts[i], pacman, COLORS);
					ghosts[i].setHowManySteps(ghosts[i].getHowManySteps() - 1);
				}
			}
			if (!collision)
			{
				collision = caseCollisionPacman();
			}
			if (till_fruit_appear == 0)
			{
				//the case that fruit appears on the board
				fruitMode = true;
				randomLocation();
				board.moveFruit(fruit, ghosts, pacman.getCurrLocation(), COLORS);
			}
			if (fruitMode && ghostPace)
			{
				fruit.setLastLocation(fruit.getCurrLocation());
				fruit.move();
				board.moveFruit(fruit, ghosts, pacman.getCurrLocation(), COLORS);
				Sleep(200);
			}
			if (till_fruit_appear == -5)
			{
				//the case that fruit disapperas
				fruitMode = false;
				till_fruit_appear = decode(fruit);
				board.gotoxy(fruit.getCurrLocation());
				cout << board.getBoard()[fruit.getCurrLocation().getX()][fruit.getCurrLocation().getY()];
			}
			if (fruit.getMeetGhost() || fruit.getMeetPacman())
				fruitMode = false;

			ghostPace = !ghostPace;
			checkGameStatus();
		}
		till_fruit_appear--;

	}
	ghostPace = !ghostPace;
	checkGameStatus();
	countPaces++;
}


void Load::steps(string file_name)
{
	ifstream steps_file;
	steps_file.open(file_name);

	steps_file.clear();

	if (!steps_file)
	{
		//throw exception
		cout << "Error with infile" << endl;
		exit(-1);
	}

	bool even = true;
	char ch = '/0';
	int steps_num;
	bool pac = false, ghos = false, frui = false;

	while (!steps_file.eof())
	{
		if (!frui)
		{
			steps_file >> ch;
		}

		if (ch != '\n')
		{
			if (ch == 'p')
			{
				pac = true;
				steps_file >> ch;
			}
			else if (ch == 'g')
			{
				pac = false;
				ghos = true;
				steps_file >> ch;
			}
			else if (ch == 'f')
			{
				ghos = false;
				frui = true;
				ch = '0';

			}

			steps_file >> steps_num;

			if (pac)
			{
				pacmanSteps.push_back({ caster(ch), steps_num });
			}
			else if (ghos)
			{
				ghostSteps.push_back({ caster(ch), steps_num });
			}
			else if (frui)
			{
				fruitSteps.push_back(steps_num);
			}
		}

	}


	steps_file.close();
}

bool Load::caseCollisionPacman()
{
	bool ans = false;
	for (int i = 0; i < ghosts.size() && !ans; i++) {
		if (pacman.getCurrLocation() == (ghosts[i].getCurrLocation())) {
			ans = true;
			deaths[3 - pacman.getLives()] = steps_counter;
			pacman.liveDedaction();
		}
	}

	return ans;
}

void Load::checkGameStatus()
{
	if (board.getBREADCRAMPS_NUM() == 0)
	{
		cout.flush();
		system("cls");
		cout << "You Win :)" << endl;
		inProgress = false;
		cout << "To continue press any key" << endl;
		_getch();
		system("cls");
	}
	else if (pacman.getLives() == 0)
	{
		cout.flush();
		system("cls");
		cout << "You Lose :(" << endl;
		cout << "To continue press any key" << endl;
		inProgress = false;
		_getch();
		system("cls");
	}

}

int Load::decode(Creature& creature, diraction dir)
{
	int output = 0;
	if (typeid(creature).name() != typeid(fruit).name())
	{
		creature.setCurrDiraction(dir);

		if (typeid(creature).name() == typeid(pacman).name())
		{

			pacmanSteps.erase(pacmanSteps.begin());
			output = pacmanSteps[0].getStepsNum();
			pacmanSteps.erase(pacmanSteps.begin());

		}
		else if (typeid(creature).name() == typeid(ghosts[0]).name())
		{

			ghostSteps.erase(ghostSteps.begin());
			output = ghostSteps[0].getStepsNum();
			ghostSteps.erase(ghostSteps.begin());

		}

	}
	else
	{
		output = fruitSteps[0];
		fruitSteps.erase(fruitSteps.begin());
	}
	return output;

}

diraction Load::caster(char ch)
{
	diraction ans = ERR;

	if (ch == 'a' || ch == 'A') //left
	{
		ans = LEFT;
	}
	else if (ch == 'd' || ch == 'D') //right
	{
		ans = RIGHT;
	}
	else if (ch == 'w' || ch == 'W') //up
	{
		ans = UP;
	}
	else if (ch == 'x' || ch == 'X') //down
	{
		ans = DOWN;
	}
	else if (ch == 's' || ch == 'S') //stay
	{
		ans = STAY;
	}
	else if (ch == 27) //ESC
	{
		ans = ESC;
	}

	return ans;
}

Location& Load::randomLocation()
{

	int randomX = rand() % (board.getBoardHight() - 5) + 1;
	int randomY = rand() % (board.getBoardWidth() - 5) + 1;

	while (board.outOfRange(randomX, randomY) || (board.getBoard()[randomX][randomY] == '#' || board.getBoard()[randomX][randomY] == '|'))
	{
		randomX = rand() % (board.getBoardHight() - 5) + 1;
		randomY = rand() % (board.getBoardWidth() - 5) + 1;
	}

	Location fruitLoc(randomX, randomY);
	fruit.setCurrLocation(fruitLoc);
	int randomDigit = rand() % 5 + 53;
	fruit.getCharacter() = randomDigit;
	return fruitLoc;

}

void Load::restart()
{
	inProgress = true;
	res = true;
	board.setScore(0);
	pacman.setLives(3);
	while (!ghosts.empty())
	{
		ghosts.pop_back();
	}
	while (!board.getBoard().empty())
	{
		board.getBoard().pop_back();
	}
}

Pacman Load::getPacman()
{
	return pacman;
}


void Load::createResultFile(int screen)
{
	ofstream result;
	result.open(createFileName(screen));
	int i = 0;

	while (i < 3 && deaths[i] != 0)
	{
		result << "Point of time pacman died : " << deaths[i] << endl;
		i++;
	}

	result << "Point of time pacman finished the screen: " << steps_counter << endl;

	result.close();
}

string Load::createFileName(int screen)
{
	string file_name;

	if (screen == 0)
		file_name = "pacman_a.result";
	else if (screen == 1)
		file_name = "pacman_b.screen";
	else
		file_name = "pacman_c.screen";

	return file_name;
}

bool Load::compareFiles(string file_name_1, string file_name_2)
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