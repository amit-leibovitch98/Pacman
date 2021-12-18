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

void Board::initBoard(ifstream &board_file)
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

char& Board::getSquareChar(int x, int y)
{
	return board[x][y];
}

void Board::setBoardWidth(ifstream& board_file)
{
	board_file.clear();
	board_file.seekg(0, ios::beg);
	char* firstLine = new char[MAX_BOARD_WIDTH + 1];
	board_file.getline(firstLine, sizeof(char) * (MAX_BOARD_WIDTH + 1));
	actual_board_width = strlen(firstLine);
}

void Board::setBoardHight(ifstream& board_file)
{
	board_file.clear();
	board_file.seekg(0, ios::beg);
	int ampersand_j;
	string line;
	actual_board_hight = 1;
	char* curr_line = new char[MAX_BOARD_HIGHT + 1];

	board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));

	ampersand_j = line.find('&');

	while (ampersand_j == -1)
	{
		actual_board_hight++;
		board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));

		line = curr_line;
		ampersand_j = line.find('&');
	}

	ampersand_loc.setX(actual_board_hight - 1);
	ampersand_loc.setY(ampersand_j);
	board_file.seekg(2 * actual_board_width, ios::cur);
	actual_board_hight += 3;

	board_file.getline(curr_line, sizeof(char) * (actual_board_width + 1));
	line = curr_line;

	while (line.find('#') != -1 || line.find('%') != -1 || line.find('@') != -1 || line.find('$') != -1)
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

void Board::fileToMatrix(ifstream &board_file, char ghost_character, Pacman& pacman, vector<Ghost>& ghosts)
{
	initBoard(board_file);
	board_file.clear();
	board_file.seekg(0, ios::beg);

	char* line = new char[actual_board_width + 1];
	string sline;

	for (int i = 0; i < actual_board_hight; i++)
	{
		board_file.getline(line, sizeof(char) * (actual_board_width + 1));

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
}

void Board::printGhost(Ghost ghost, bool COLORS)
{
	Location next_loc;

	if (COLORS)
		cout << "\033[3;104;97m" << ghost.getCharacter() << "\033[0m\t\t";
	else
		cout << ghost.getCharacter();

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
		cout << "\x1B[95m" << fruit.getCharacter() << "\033[0m\t\t";
	else
		cout << fruit.getCharacter();
}

void Board::printBoardEndLine(Pacman pacman, bool COLORS)
{
	if (COLORS)
		cout << "\x1B[91mLives: " << pacman.getLives() << "\033[0m\t" << "\x1B[92m" << "                                                   Score: " << score << "\033[0m\t" << endl;
	else
		cout << "Lives: " << pacman.getLives() << "                                                   Score: " << score << endl;
}

void Board::printBoard(Pacman pacman, vector<Ghost>& ghosts, bool COLORS)
{
	int ghost_counter = 0;
	cout.flush();
	system("cls");

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == '#')
				cout << wall_caracter;
			else if (board[i][j] == '%')
				cout << empty_spot;
			else if (board[i][j] == '&')
			{
				printBoardEndLine(pacman, COLORS);
				i += 3;
			}
			else if (board[i][j] == '|')
			{
				cout << magic_tunnel_character;

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

//----------------------------------------------------------------------------------------------------------

void Board::moveGhost(Ghost& ghosts, Pacman pacman, bool COLORS)
{

	gotoxy(ghosts.getLastLocation());

	if (getSquareChar(ghosts.getLastLocation().getX(), ghosts.getLastLocation().getY()) == '.')
	{
		cout << breadcramp_character;
	}
	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == '#')
	{

		ghosts.setCurrLocation(ghosts.getLastLocation());

	}
	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == '|') 
	{
		ghosts.setCurrLocation(ghosts.getLastLocation());
	}

	else if (getSquareChar(ghosts.getCurrLocation().getX(), ghosts.getCurrLocation().getY()) == ' ')
	{
		cout << empty_spot;
	}

	int y = ghosts.getCurrLocation().getY();
	int x = ghosts.getCurrLocation().getX();

	ghosts.setRunOverBreadcramp(board[x][y] == '.'); //if the ghost is supposed to run over a breadcramp, ghage the falg to true, alse to false

	gotoxy(ghosts.getCurrLocation()); //print current location
	printGhost(ghosts, COLORS);
}

void Board::movePacman(Pacman& pacman, bool COLORS)
{

	gotoxy(pacman.getLastLocation());

	if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == '.')
	{
		score++;
		getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) = ' ';
		cout << empty_spot;
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman, COLORS);


	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == '#')
	{

		pacman.setCurrLocation(pacman.getLastLocation());
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman, COLORS);


	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == ' ')
	{
		cout << ' ';
		gotoxy(pacman.getCurrLocation());
		printPacman(pacman, COLORS);
	}
	else if (getSquareChar(pacman.getCurrLocation().getX(), pacman.getCurrLocation().getY()) == '|')
	{
		gotoxy(pacman.getLastLocation());
		gotoxy(pacman.getCurrLocation());
		cout << empty_spot;

		magicTunnelCase(pacman);

		gotoxy(pacman.getCurrLocation());
		printPacman(pacman, COLORS);

	}

	gotoxy(ampersand_loc);
	printBoardEndLine(pacman, COLORS);
	Sleep(150);
}

void Board::moveFruit(Fruit& fruit, vector<Ghost> ghosts, Location pacmanLocation, bool COLORS)
{
	bool specialCases = false;

	gotoxy(fruit.getLastLocation());
	

	for (int i = 0; i < ghosts.size() && !specialCases; i++)
	{
		if (fruit.getLastLocation() == ghosts[i].getCurrLocation())
		{
			specialCases = true;
			fruit.setMeetGhost(true);
			//cout << ghosts[i].getCharacter();
		}
	}
	if (!specialCases)
	{
		if (pacmanLocation == fruit.getLastLocation())
		{
			specialCases = true;
			fruit.setMeetPacman(true);
			score = score + (fruit.getCharacter() - '0');
			cout << empty_spot;
		}
		else if (getSquareChar(fruit.getCurrLocation().getX(), fruit.getCurrLocation().getY()) == '#')
		{
			fruit.setCurrLocation(fruit.getLastLocation());

		}
		else if (getSquareChar(fruit.getCurrLocation().getX(), fruit.getCurrLocation().getY()) == '|')
		{
			fruit.setCurrLocation(fruit.getLastLocation());
		}

		if (!specialCases)
		{
			cout << getSquareChar(fruit.getLastLocation().getX(), fruit.getLastLocation().getY());
			gotoxy(fruit.getCurrLocation());
			printFruit(fruit, COLORS);

		}
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