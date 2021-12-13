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

void Board::openBoardFile(string file_name)
{
	board_file.open(file_name);
	if (!board_file) 
	{
		cout << "Error with infile" << endl;
		exit(-1);
	}
}

void Board::initBoard()
{
	setBoardWidth();
	setBoardHight(); 
}

int Board::getScore()
{
	return score;
}

void Board::setScore(int _score)
{
	score = _score;
}

char& Board::getSquareChar(int x, int y)
{
	return board[x][y];
}

ifstream Board::getFile()
{
	return ifstream();
}

void Board::setBoardWidth()
{
	board_file.seekg(0, ios::beg);
	char* firstLine = new char[MAX_BOARD_WIDTH];
	board_file >> firstLine;
	actual_board_width = strlen(firstLine);
}

void Board::setBoardHight()
{
	board_file.seekg(0, ios::beg);
	int ampersand_j;
	string line;
	actual_board_hight = 1;
	char* curr_line = new char[MAX_BOARD_HIGHT];

	board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));

	ampersand_j = line.find('&');

	while (ampersand_j == -1)
	{
		actual_board_hight++;
		board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));

		line = curr_line;
		ampersand_j = line.find('&');
	}

	ampersand_loc.setX(actual_board_hight);
	ampersand_loc.setY(ampersand_j);
	board_file.seekg(2 * actual_board_width, ios::cur);
	actual_board_hight += 3;
	
	board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));
	line = curr_line;

	while (line.find('#' || '$' || '@') != -1)
	{
		actual_board_hight++;
		board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));
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

//----------------------------------------------------------------------------------------------------------

void Board::fileToMatrix(char ghost_character, Pacman pacman, vector<Ghost> ghosts)
{

	initBoard();
	board_file.seekg(0, ios::beg);
	char temp;

	for (int i = 0; i < actual_board_width; i++)
	{
		for (int j = 0; j < actual_board_hight; j++)
		{
			temp = board_file.get();
			board[i].push_back(temp);

			if (temp == ghost_character)
				ghosts.push_back({ { i,j } });
			if (temp == '@')
				pacman.initLocations({ i,j });
		}
	}


}

void Board::printGhost(char ghost_character, bool COLORS)
{
	if (COLORS)
		cout << "\033[3;104;97m" << ghost_character << "\033[0m\t\t";
	else
		cout << ghost_character;
}

void Board::printPacman(char pacman_character, bool COLORS)
{
	if (COLORS)
		cout << "\x1B[93m" << pacman_character << "\033[0m\t\t";
	else
		cout << pacman_character;
}

void Board::printBoardEndLine(Pacman pacman, bool COLORS)
{
	if (COLORS)
		cout << "\x1B[91mLives: " << pacman.getLives() << "\033[0m\t" << "\x1B[92m" << "                                                   Score: " << score << "\033[0m\t" << endl;
	else
		cout << "Lives: " << pacman.getLives() << "                                                   Score: " << score << endl;
}

void Board::printBoard(Pacman pacman, vector<Ghost> ghosts, bool COLORS)
{
	cout.flush();
	system("cls");

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == '#')
				cout << wall_caracter;
			else if (board[i][j] == '@')
			{
				printPacman(pacman.getCharacter(), COLORS);
				pacman.setCurrLocation({ i,j }); //init!!
			}
			else if (board[i][j] == '$')
			{
				printGhost(ghosts[0].getCharacter(), COLORS);
			}
			else if (board[i][j] == '%')
				cout << empty_spot;
			else if (board[i][j] == '&')
				printBoardEndLine(pacman, COLORS);
			else if (board[i][j] == ' ')
				cout << breadcramp_character;
		}

	}


}

//----------------------------------------------------------------------------------------------------------

void Board::moveGhost(Ghost& ghosts, Pacman pacman, bool COLORS)
{

	gotoxy(ghosts.getLastLocation());
	if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == breadcramp_character) {
		cout << breadcramp_character;
	}
	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == wall_caracter) {

		ghosts.setCurrLocation(ghosts.getLastLocation());

	}
	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == magic_tunnel_character) {
		ghosts.setCurrLocation(ghosts.getLastLocation());
	}

	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == empty_spot) {
		cout << empty_spot;
	}

	int y = ghosts.getCurrLocation().getY();
	int x = ghosts.getCurrLocation().getX();

	ghosts.setRunOverBreadcramp(board[x][y] == breadcramp_character); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false

	gotoxy(ghosts.getCurrLocation()); //print current location
	printGhost(ghosts.getCharacter(), COLORS);
}

void Board::movePacman(Pacman& pacman, diraction _diraction, bool COLORS)
{

	gotoxy(pacman.getLastLocation());

	if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == breadcramp_character)
	{
		score++;
		getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) = empty_spot;
		cout << empty_spot;
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);


	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == wall_caracter)
	{

		pacman.setCurrLocation(pacman.getLastLocation());
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);


	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == empty_spot)
	{
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);

		gotoxy(pacman.getLastLocation());
		cout << empty_spot;
	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == magic_tunnel_character)
	{
		gotoxy(pacman.getLastLocation());
		cout << empty_spot;

		magicTunnelCase(pacman);

		gotoxy(pacman.getCurrLocation());
		printPacman(pacman.getCharacter(), COLORS);

	}

	gotoxy((MAX_BOARD_WIDTH, MAX_BOARD_HIGHT));
	printBoardEndLine(pacman, COLORS);
	Sleep(150);
}

void Board::moveFruit(Fruit& fruit, vector<Ghost> ghosts, Location pacmanLocation) 
{
	bool specialCases = false;
	gotoxy(fruit.getLastLocation());
	if (pacmanLocation == fruit.getCurrLocation()) 
	{
		specialCases = true;
		fruit.setMeetPacman(true);
		cout << empty_spot;
		score = score + fruit.getCharacter();
	}
	else if (getSquareChar(fruit.getCurrLocation().getX(), fruit.getCurrLocation().getY()) == wall_caracter) 
	{
		fruit.setCurrLocation(fruit.getLastLocation());


	}
	else if (getSquareChar(fruit.getCurrLocation().getX(), fruit.getCurrLocation().getY()) == magic_tunnel_character) 
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
				cout << empty_spot;
				cout << ghosts[i].getCharacter();
			}
		}
	}
	if (!specialCases) {
		cout << getSquareChar(fruit.getLastLocation().getX(), fruit.getLastLocation().getY());
		gotoxy(fruit.getCurrLocation());
		cout << fruit.getCharacter();

	}



}

void Board::magicTunnelCase(Pacman& pacman)
{
	int x = pacman.getCurrLocation().getX();
	int y = pacman.getCurrLocation().getY();
	int newY;

	if (y == 0)
	{
		newY = MAX_BOARD_WIDTH - 4;
	}
	else
	{
		newY = 1;
	}
	Location newLocation(x, newY);
	pacman.setCurrLocation(newLocation);
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