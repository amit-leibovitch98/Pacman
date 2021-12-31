#include "Load.h"

bool Load::endswith(string file_name, string suffix)
{

	return file_name.size() >= suffix.size() && 0 == file_name.compare(file_name.size() - suffix.size(), suffix.size(), suffix);

}

void Load::loadFiles()
{
	string prefix = "/.";
	

	for (const auto& file : fs::directory_iterator(".")) {
		if (endswith(file.path().string(), "screen")) {
			screen_files.push_back(file.path().string());
		}
		else if (endswith(file.path().string(), "steps")) {
			screen_files.push_back(file.path().string());
		}
		else if (endswith(file.path().string(), "result")) {
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
		if (input == 0) {
			steps(screen_files[1]);
		}
		else if (input == 1) {
			steps(screen_files[4]);
		}
		if (input == 2) {
			steps(screen_files[7]);
		}
		start();
	}

void Load::start()
{
	int till_fruit_appear = 0;
	int fruit_pace = 0;
	bool ghostPace = true;
	bool collision = false;
	while (inProgress) {
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
				pacman.setHowManySteps(decode(pacman, pacmanSteps[0]));
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
						ghosts[i].setHowManySteps(decode(ghosts[i], ghostSteps[0]));
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

	char ch='\0';
	bool pac=false, ghos=false, frui=false;
	while (ch != EOF) 
	{
		steps_file >> ch;
		if (ch != '\n')
		{
			if (ch == 'p')
			{
				pac = true;
				steps_file >> ch;
			}
			else if (ch == 'g')
			{
				ghos = true;
				steps_file >> ch;
			}
			else if (ch == 'f')
			{
				frui = true;
				steps_file >> ch;
			}

			if (pac)
			{
				pacmanSteps.push_back(ch);
			}
			else if (ghos)
			{
				ghostSteps.push_back(ch);
			}
			else if (frui)
			{
				fruitSteps.push_back(ch);
			}
		}
		else 
		{
			pac = ghos = frui = false;
		}
	}
	steps_file.close();
}
	

int Load::decode(Creature& creature,char ch)
{
	int output = 0;
	if (ch == 'r') 
	{
		creature.setCurrDiraction(RIGHT);
	}
	else if (ch == 'l') 
	{
		creature.setCurrDiraction(LEFT);
	}
	else if (ch == 'u') 
	{
		creature.setCurrDiraction(UP);
	}
	else if (ch == 'd') 
	{
		creature.setCurrDiraction(DOWN);
	}

	if (typeid(creature).name() == typeid(pacman).name()) 
	{
		
		pacmanSteps.erase(pacmanSteps.begin());
		 output = pacmanSteps[0];
		pacmanSteps.erase(pacmanSteps.begin());
		
	}
	else if (typeid(creature).name() == typeid(ghosts[0]).name()) 
	{
			
			ghostSteps.erase(ghostSteps.begin());
			output = ghostSteps[0];
			ghostSteps.erase(ghostSteps.begin());
		
	}
		

	else if (typeid(creature).name() == typeid(fruit).name())
	{
		fruitSteps.erase(fruitSteps.begin());
		 output = fruitSteps[0];
		fruitSteps.erase(fruitSteps.begin());
		fruitMode = true;
	}
	return output;
	
}

bool Load::caseCollisionPacman()
{
	bool ans = false;
	for (int i = 0; i < ghosts.size() && !ans; i++) {
		if (pacman.getCurrLocation() == (ghosts[i].getCurrLocation())) {
			ans = true;
			pacman.liveDedaction();
		}
	}
	
	return ans;
}

void Load::checkGameStatus()
{
	if (board.getScore() == board.getBREADCRAMPS_NUM())
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