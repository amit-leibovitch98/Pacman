#include "GhostMoveStrategy.h"

void GhostMoveStrategyA::moveAlghorithm(Ghost& ghost, int countPaces)
{
	BFS(pacmanLocation, board->getBoardHight(), board->getBoardWidth(), ghost);
}

void GhostMoveStrategy::BFS(Location& s, int i, int j, Ghost& ghost)
{
	vector<vector<bool>> visited(i, vector<bool>(j, false));
	int dir[4][2] = { { 0,1 }, { 0,-1 }, { 1,0 }, { -1,0 } };
	Location adj, cell;
	queue<Location> q;
	q.push(s);
	visited[s.getX()][s.getY()] = true;
	while (!q.empty()) 
	{
		cell = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) 
		{
			int a = cell.getX() + dir[k][0];
			int b = cell.getY() + dir[k][1];
			adj.setX(a);
			adj.setY(b);
			if (adj == ghost.getCurrLocation()) 
			{
				ghost.setCurrLocation(cell); 
				return;
			}
			else if (visited[a][b] != true && a < board->getBoardHight() && b < board->getBoardWidth() && a >= 0 && b >= 0)
			{
				if (isValidSquare(a, b)) 
				{
					q.push(adj);
					visited[adj.getX()][adj.getY()] = true;
				}
			}
		}
	}
	return;

}

bool GhostMoveStrategy::isValidSquare(int x, int y)
{
	if (board->getBoard()[x][y] == '#' || board->getBoard()[x][y] == '|') {
		return false;
	}
	return true;
}

void GhostMoveStrategyB::moveAlghorithm(Ghost& ghost, int countPaces)
{

	if (countPaces % 15 == 0) {
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
	else if (countPaces > 16 && countPaces < 26) {
		if (ghost.getCurrDiraction() == LEFT)
		{
			ghost.getCurrLocation().moveLeft();
			ghost.setCurrDiraction(LEFT);
		}
		else if (ghost.getCurrDiraction() == RIGHT)
		{
			ghost.getCurrLocation().moveRight();
			ghost.setCurrDiraction(RIGHT);

		}
		else if (ghost.getCurrDiraction() == UP)
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
	else
	{
		BFS(getPacmanLocation(), board->getBoardHight(), board->getBoardWidth(), ghost);
	}

}

void GhostMoveStrategyC::moveAlghorithm(Ghost& ghost, int countPaces)
{
	if (countPaces % 20 == 1)
	{
		srand(time(NULL));
		int randomMove = rand() % 4 + 1;

		if (randomMove == 1)
		{
			if (isValidSquare(ghost.getCurrLocation().getX(), ghost.getCurrLocation().getY() - 1))
			{
				ghost.getCurrLocation().moveLeft();
				ghost.setCurrDiraction(LEFT);
			}
			else {
				randomMove = rand() % 4 + 1;
			}

		}
		else if (randomMove == 2)
		{
			if (isValidSquare(ghost.getCurrLocation().getX(), ghost.getCurrLocation().getY() + 1))
			{
				ghost.getCurrLocation().moveRight();
				ghost.setCurrDiraction(RIGHT);
			}
			else {
				randomMove = rand() % 4 + 1;
			}

		}
		else if (randomMove == 3)
		{
			if (isValidSquare(ghost.getCurrLocation().getX() - 1, ghost.getCurrLocation().getY()))
			{
				ghost.getCurrLocation().moveUp();
				ghost.setCurrDiraction(UP);
			}
			else {
				randomMove = rand() % 4 + 1;
			}
		}
		else
		{
			if (isValidSquare(ghost.getCurrLocation().getX() + 1, ghost.getCurrLocation().getY()))
			{
				ghost.getCurrLocation().moveDown();
				ghost.setCurrDiraction(DOWN);
			}
			else {
				randomMove = rand() % 4 + 1;
			}
		}
	}
	else {
		if (ghost.getCurrDiraction() == LEFT)
		{
			ghost.getCurrLocation().moveLeft();
			ghost.setCurrDiraction(LEFT);
		}
		else if (ghost.getCurrDiraction() == RIGHT)
		{
			ghost.getCurrLocation().moveRight();
			ghost.setCurrDiraction(RIGHT);

		}
		else if (ghost.getCurrDiraction() == UP)
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



}