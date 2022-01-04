#include "Board.h"

char Board::getEmptyspot()
{
	return empty_spot;
}

char Board::getBreadcrampCharacter()
{
	return breadcramp_character;
}

char Board::getMagicTunnelCharacter()
{
	return magic_tunnel_character;
}

char Board::getWallCharacter()
{
	return wall_caracter;
}

int Board::getBREADCRAMPS_NUM()
{
	return BREADCRAMPS_NUM;
}

Location Board::getAmpersandLocation()
{
	return ampersand_loc;
}

void Board::initBoard(ifstream& board_file)
{
	setBoardWidth(board_file);
	setBoardHight(board_file);
}

int Board::getScore()
{
	return score;
}

void Board::setScore(int _score)
{
	score = _score;
}

void Board::setBoardWidth(ifstream& board_file)
{
	board_file.clear();
	board_file.seekg(0, ios::beg);
	char* firstLine = new char[MAX_BOARD_WIDTH + 1];
	board_file.getline(firstLine, MAX_BOARD_WIDTH + 1);
	actual_board_width = strlen(firstLine);
}

void Board::setBoardHight(ifstream& board_file)
{
	board_file.clear();
	board_file.seekg(0, ios::beg);
	int ampersand_j;
	string line;
	actual_board_hight = 1;
	char* curr_line = new char[(actual_board_width + 1)];

	board_file.getline(curr_line, (actual_board_width + 1));

	line = curr_line;
	ampersand_j = line.find('&');

	while (ampersand_j == -1)
	{
		actual_board_hight++;
		board_file.getline(curr_line, (actual_board_width + 1));

		line = curr_line;
		ampersand_j = line.find('&');
	}

	ampersand_loc.setX(actual_board_hight - 1);
	ampersand_loc.setY(ampersand_j);
	board_file.getline(curr_line, actual_board_width);
	board_file.getline(curr_line, actual_board_width);
	actual_board_hight += 3;

	board_file.getline(curr_line, actual_board_width);
	line = curr_line;

	while (line.find('#') != -1 || line.find('%') != -1 || line.find('@') != -1 || line.find('$') != -1)
	{
		actual_board_hight++;
		board_file.getline(curr_line, actual_board_width);
	}

}

int Board::getBoardWidth()
{
	return actual_board_width;
}

int Board::getBoardHight()
{
	return actual_board_hight;
}

void Board::setBreadCrampsNum()
{
	BREADCRAMPS_NUM = 0;
	for (int i = 0; i < actual_board_hight - 4; i++)
	{
		for (int j = 0; j < actual_board_width; j++)
		{
			if (board[i][j] == breadcramp_character)
				BREADCRAMPS_NUM++;
		}
	}
}

//----------------------------------------------------------------------------------------------------------

void Board::fileToMatrix(ifstream& board_file, char ghost_character, Pacman& pacman, vector<Ghost>& ghosts)
{
	initBoard(board_file);
	board_file.clear();
	board_file.seekg(0, ios::beg);

	char* line = new char[(actual_board_width + 1)];
	string sline;

	for (int i = 0; i < actual_board_hight; i++)
	{
		board_file.getline(line, actual_board_width + 1);

		for (int j = 0; j < actual_board_width; j++)
		{
			if (line[j] == '$')
			{
				ghosts.push_back({ { i,j } });
				line[j] = ' ';
			}
			else if (line[j] == '@')
			{
				pacman.initLocations({ i,j });
				line[j] = ' ';
			}
			else if (line[j] == '%')
				line[j] = ' ';
			else if (line[j] == ' ')
			{
				if (i == 0 || j == 0 || i == actual_board_hight - 1 || j == actual_board_width - 1)
					line[j] = '|';
				else
					line[j] = '.';
			}
		}
		sline = line;
		board.push_back(sline);

	}

	setBreadCrampsNum();
}

void Board::printGhost(Ghost ghost, bool COLORS)
{
	Location next_loc;

	if (COLORS)
		cout << "\033[3;104;97m" << ghost.getCharacter() << "\033[0m\t\t";
	else
		cout << (char)234;

	next_loc = { ghost.getCurrLocation().getX() , ghost.getCurrLocation().getY() + 1 };
	gotoxy(next_loc);
}

void Board::printPacman(Pacman pacman, bool COLORS)
{
	Location next_loc;

	if (COLORS)
		cout << "\x1B[93m" << pacman.getCharacter() << "\033[0m\t\t";
	else
		cout << pacman.getCharacter();

	next_loc = { pacman.getCurrLocation().getX() , pacman.getCurrLocation().getY() + 1 };
	gotoxy(next_loc);
}

void Board::printFruit(Fruit fruit, bool COLORS)
{
	if (COLORS)
		cout << "\033[3;107;95m" << fruit.getCharacter() << "\033[0m\t\t";
	else
		cout << fruit.getCharacter();
}

void Board::printBoardEndLine(Pacman pacman, bool COLORS)
{

	if (COLORS)
		cout << "\x1B[91mLives: " << pacman.getLives() << "\033[0m\t" << "\x1B[92m" << "Score: " << score << "\033[0m\t" << endl;
	else
		cout << "Lives: " << pacman.getLives() << " Score: " << score << endl;

	for (int i = 0; i < 2; i++) //complete the 3X20 ampesend space
		for (int j = 0; j < 20; j++)
			cout << ' ';
}

void Board::printBoard(Pacman pacman, vector<Ghost>& ghosts, bool COLORS)
{
	if (kindOfGame != 3) {
		int ghost_counter = 0;
		cout.flush();
		system("cls");

		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j] == '#')
					cout << (char)178;
				else if (board[i][j] == '%')
					cout << empty_spot;
				else if (board[i][j] == '&')
				{
					printBoardEndLine(pacman, COLORS);
					i += 3;
				}
				else if (board[i][j] == '|')
				{
					cout << (char)176;

				}
				else if (board[i][j] == ' ')
					cout << ' ';
				else if (board[i][j] == '.')
					cout << '.';
			}
			cout << endl;
		}
		gotoxy(pacman.getinitLocation());
		printPacman(pacman, COLORS);

		for (int i = 0; i < ghosts.size(); i++)
		{
			gotoxy(ghosts[i].getinitLocation());
			printGhost(ghosts[i], COLORS);
		}
	}
	
}

//----------------------------------------------------------------------------------------------------------

void Board::moveGhost(Ghost& ghosts, Pacman pacman, bool COLORS)
{

	gotoxy(ghosts.getLastLocation());

	if (board[ghosts.getCurrLocation().getX()][ghosts.getCurrLocation().getY()] == breadcramp_character)
	{
		if (kindOfGame != 3) {
			//its not silent mode
			cout << breadcramp_character;
		}
		
	}
	else if (board[ghosts.getCurrLocation().getX()][ghosts.getCurrLocation().getY()] == wall_caracter)
	{
		ghosts.setCurrLocation(ghosts.getLastLocation());

	}
	else if (board[ghosts.getCurrLocation().getX()][ghosts.getCurrLocation().getY()] == magic_tunnel_character)
	{
		ghosts.setCurrLocation(ghosts.getLastLocation());
	}

	else if (board[ghosts.getCurrLocation().getX()][ghosts.getCurrLocation().getY()] == empty_spot)
	{
		if (kindOfGame != 3) {
			//its not silent mode
			cout << empty_spot;
		}
		
	}

	int y = ghosts.getCurrLocation().getY();
	int x = ghosts.getCurrLocation().getX();

	ghosts.setRunOverBreadcramp(board[x][y] == breadcramp_character); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false

	gotoxy(ghosts.getCurrLocation()); //print current location
	if (kindOfGame != 3) {
		//its not silent mode
		printGhost(ghosts, COLORS);
	}
	
}

void Board::movePacman(Pacman& pacman, bool COLORS)
{

	gotoxy(pacman.getLastLocation());

	if (board[pacman.getCurrLocation().getX()][pacman.getCurrLocation().getY()] == breadcramp_character)
	{
		BREADCRAMPS_NUM--;
		score++;
		board[pacman.getCurrLocation().getX()][pacman.getCurrLocation().getY()] = empty_spot;
		if (kindOfGame != 3)
		{
			//its not silent mode
			cout << empty_spot;
			gotoxy(pacman.getCurrLocation());
			printPacman(pacman, COLORS);
		}

	}
	else if (board[pacman.getCurrLocation().getX()][pacman.getCurrLocation().getY()] == wall_caracter)
	{

		pacman.setCurrLocation(pacman.getLastLocation());
		gotoxy(pacman.getCurrLocation());
		if (kindOfGame != 3) {
			printPacman(pacman, COLORS);
		}

	}
	else if (board[pacman.getCurrLocation().getX()][pacman.getCurrLocation().getY()] == empty_spot)
	{
		if (kindOfGame != 3) {
			gotoxy(pacman.getCurrLocation());
			printPacman(pacman, COLORS);

			gotoxy(pacman.getLastLocation());
			cout << empty_spot;
		}
	}
	else if (board[pacman.getCurrLocation().getX()][pacman.getCurrLocation().getY()] == magic_tunnel_character)
	{
		gotoxy(pacman.getLastLocation());
		if (kindOfGame != 3) {
			cout << empty_spot;
		}
		magicTunnelCase(pacman);

		gotoxy(pacman.getCurrLocation());
		if (kindOfGame != 3) {
			printPacman(pacman, COLORS);
		}
		

	}
	if (kindOfGame != 3) {
		gotoxy(ampersand_loc);
		printBoardEndLine(pacman, COLORS);
		Sleep(100);
	}
	
}

void Board::moveFruit(Fruit& fruit, vector<Ghost> ghosts, Location pacmanLocation, bool COLORS)
{
	bool specialCases = false;
	gotoxy(fruit.getLastLocation());

	if (pacmanLocation == fruit.getCurrLocation())
	{
		specialCases = true;
		fruit.setMeetPacman(true);
		if (kindOfGame != 3) {
			cout << empty_spot;
		}
		score = score + (fruit.getCharacter() - '0');
	}
	else if (board[fruit.getCurrLocation().getX()][fruit.getCurrLocation().getY()] == wall_caracter)
	{
		fruit.setCurrLocation(fruit.getLastLocation());
	}
	else if (board[fruit.getCurrLocation().getX()][fruit.getCurrLocation().getY()] == magic_tunnel_character)
	{
		fruit.move();
	}
	else {
		bool collision = false;
		for (int i = 0; i < ghosts.size() && !collision; i++)
		{
			if (fruit.getCurrLocation() == ghosts[i].getCurrLocation())
			{
				specialCases = true;
				collision = true;
				fruit.setMeetGhost(true);
				if (kindOfGame != 3) {
					cout << empty_spot;
				}
				

			}
		}
	}
	if (!specialCases)
	{
		if (kindOfGame != 3) {
			cout << board[fruit.getLastLocation().getX()][fruit.getLastLocation().getY()];
			gotoxy(fruit.getCurrLocation());
			printFruit(fruit, COLORS);
		}
	}
}

void Board::magicTunnelCase(Pacman& pacman)
{
	int newX = pacman.getCurrLocation().getX();
	int newY = pacman.getCurrLocation().getY();

	if (pacman.getCurrDiraction() == RIGHT || pacman.getCurrDiraction() == LEFT)
	{
		if (newY == 0)
		{
			newY = actual_board_width - 4;
		}
		else
		{
			newY = 1;
		}
	}
	else
	{
		if (newX == 0)
		{
			newX = actual_board_hight - 4;
		}
		else
		{
			newX = 1;
		}
	}
	Location newLocation(newX, newY);
	pacman.setCurrLocation(newLocation);
}

bool Board::outOfRange(int x, int y)
{
	return (x == ampersand_loc.getX() || x == ampersand_loc.getX() + 1 || x == ampersand_loc.getX() + 2 || x > actual_board_hight - 5 || y > actual_board_width - 1);
}

void Board::gotoxy(Location location)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = location.getY();
	dwCursorPosition.Y = location.getX();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
