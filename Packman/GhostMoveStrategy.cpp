#include "GhostMoveStrategy.h"

void GhostMoveStrategyA::moveAlghorithm() 
{
	int compare = 0;
	if (ghost->getCurrLocation().getX() == pacmanLocation->getX()) {
		compare = ghost->getCurrLocation().getY() - pacmanLocation->getY();
		if (compare < 0) {

			ghost->setCurrLocation((ghost->getCurrLocation().getX(), ghost->getCurrLocation().getY() + 1));
			ghost->setCurrDiraction(RIGHT);
		}
		else {
			ghost->setCurrLocation((ghost->getCurrLocation().getX(), ghost->getCurrLocation().getY() - 1));
			ghost->setCurrDiraction(LEFT);
		}
	}
	else if (ghost->getCurrLocation().getY() == pacmanLocation->getY()) {
		compare = ghost->getCurrLocation().getX() - pacmanLocation->getX();
		if (compare < 0) {

			ghost->setCurrLocation((ghost->getCurrLocation().getX() + 1, ghost->getCurrLocation().getY()));
			ghost->setCurrDiraction(DOWN);
		}
		else {
			ghost->setCurrLocation((ghost->getCurrLocation().getX() - 1, ghost->getCurrLocation().getY()));
			ghost->setCurrDiraction(UP);
		}
	}
	else {
		compare = ghost->getCurrLocation().getY() - pacmanLocation->getY();
		if (compare < 0) {

			ghost->setCurrLocation((ghost->getCurrLocation().getX(), ghost->getCurrLocation().getY() + 1));
			ghost->setCurrDiraction(RIGHT);
		}
		else {
			ghost->setCurrLocation((ghost->getCurrLocation().getX(), ghost->getCurrLocation().getY() - 1));
			ghost->setCurrDiraction(LEFT);
		}
		compare = ghost->getCurrLocation().getX() - pacmanLocation->getX();
		if (compare < 0) {

			ghost->setCurrLocation((ghost->getCurrLocation().getX() + 1, ghost->getCurrLocation().getY()));
			ghost->setCurrDiraction(DOWN);
		}
		else {
			ghost->setCurrLocation((ghost->getCurrLocation().getX() - 1, ghost->getCurrLocation().getY()));
			ghost->setCurrDiraction(UP);
		}

	}
}

void GhostMoveStrategyB::moveAlghorithm() 
{
	//dont understand what is smart again after five moves.
}

void GhostMoveStrategyC::moveAlghorithm() 
{

	srand(time(NULL));
	int randomMove = rand() % 4 + 1;

	if (randomMove == 1)
	{
		ghost->getCurrLocation().moveLeft();
		ghost->setCurrDiraction(LEFT);
	}
	else if (randomMove == 2)
	{
		ghost->getCurrLocation().moveRight();
		ghost->setCurrDiraction(RIGHT);

	}
	else if (randomMove == 3)
	{
		ghost->getCurrLocation().moveUp();
		ghost->setCurrDiraction(UP);
	}
	else
	{
		ghost->getCurrLocation().moveDown();
		ghost->setCurrDiraction(DOWN);
	}
}