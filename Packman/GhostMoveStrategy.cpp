#include "GhostMoveStrategy.h"

void GhostMoveStrategyA::moveAlghorithm(Ghost& ghost) 
{
	BFS(getPacmanLocation(), 22, 80, ghost);
}

bool GhostMoveStrategyA::BFS(Location& s, int i, int j, Ghost& ghost) {
	int** visited = new int* [22];
	for (int j = 0; j < 22; j++) {
		visited[j] = new int[80];
	}
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 80; j++) {
			if (getBoard()->getSquareChar(i, j) == '#' || getBoard()->getSquareChar(i, j) == '|') {
				visited[i][j] = -1;
			}
			else {
				visited[i][j] = 1;
			}

		}

	}
	//directions
	int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
	int countNeighbrhod = 0;
	//queue
	queue<Location> q;

	//insert the top right corner.
	q.push(s);
	//until queue is empty
	while (q.size() > 0)
	{
		Location p = q.front();
		q.pop();

		//mark as visited
		visited[p.getX()][p.getY()] = -1;

		//destination is reached.
		if (Location::Location(p.getX() + 1, p.getY()) == ghost.getCurrLocation()) {
			ghost.getCurrLocation() = p;
			delete[]visited;
			return true;
		}
		if (Location::Location(p.getX() - 1, p.getY()) == ghost.getCurrLocation()) {
			ghost.getCurrLocation() = p;
			delete[]visited;
			return true;
		}
		if (Location::Location(p.getX(), p.getY() + 1) == ghost.getCurrLocation()) {
			ghost.getCurrLocation() = p;
			delete[]visited;
			return true;
		}
		if (Location::Location(p.getX(), p.getY() - 1) == ghost.getCurrLocation()) {
			ghost.getCurrLocation() = p;
			delete[]visited;
			return true;
		}


		//check all four directions
		for (int i = 0; i < 4; i++)
		{

			//using the direction array
			int a = p.getX() + dir[i][0];
			int b = p.getY() + dir[i][1];

			//not blocked and valid
			if (visited[a][b] != -1 && a >= 0 && b >= 0
				&& a < 22 && b < 80)
			{

				q.push(Location::Location(a, b));


			}
		}

	}
	delete[]visited;
	return false;
}

void GhostMoveStrategyB::moveAlghorithm(Ghost& ghost) {
	//dont understand what is smart again after five moves.
}

void GhostMoveStrategyC::moveAlghorithm(Ghost& ghost) {

	srand(time(NULL));
	int randomMove = rand() % 4 + 1;
	if (randomMove == 1)
	{
		ghost.getCurrLocation().moveLeft();
		ghost.setCurrDiraction(LEFT);
	}
	else if (randomMove == 2)
	{
		ghost.getCurrLocation().moveRight();
		ghost.setCurrDiraction(RIGHT);

	}
	else if (randomMove == 3)
	{
		ghost.getCurrLocation().moveUp();
		ghost.setCurrDiraction(UP);
	}
	else
	{
		ghost.getCurrLocation().moveDown();
		ghost.setCurrDiraction(DOWN);
	}


}