#include "Silent.h"

void Silent::start() {
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
			for (int i = 0; i < ghosts.size(); i++) {
				ghosts[i].initLocations(ghosts[i].getinitLocation());
				ghosts[i].setHowManySteps(0);
			}
			collision = false;
		}
		if (!collision) {
			if (pacman.getHowManySteps() == 0) {
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
					if (ghosts[i].getHowManySteps() == 0) {
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