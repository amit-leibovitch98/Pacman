#include "Fruit.h"

Fruit::Fruit(Location& _location) 
{
	//the char of the fruit
	srand(time(NULL));
	int randomDigit = rand() % 5 + 5;
	Creature(randomDigit, _location);

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


