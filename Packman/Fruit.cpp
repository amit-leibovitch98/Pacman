#include "Fruit.h"

Fruit::Fruit(Location _location, int _character) :Creature(_character, _location)
{
	//the char of the fruit
	srand(time(NULL));
	int randomDigit = rand() % 5 + 53;
	getCharacter() = randomDigit;
}

void Fruit::move()
{
	//ganarate random number for the position of the fruit:
		// 1 for left, 2 for right, 3 for up, 4 for down
	srand(time(NULL));
	int randomMove = rand() % 4 + 1;

	if (randomMove == 1)
	{
		getCurrLocation().moveLeft();
		setCurrDiraction(LEFT);
	}
	else if (randomMove == 2)
	{
		getCurrLocation().moveRight();
		setCurrDiraction(RIGHT);

	}
	else if (randomMove == 3)
	{
		getCurrLocation().moveUp();
		setCurrDiraction(UP);
	}
	else
	{
		getCurrLocation().moveDown();
		setCurrDiraction(DOWN);
	}
}

void Fruit::setMeetGhost(bool ans)
{
	meetGhost = ans;
}

void Fruit::setMeetPacman(bool ans)
{
	meetPacman = ans;
}

bool Fruit::getMeetGhost()
{
	return meetGhost;
}

bool Fruit::getMeetPacman()
{
	return meetPacman;
}



