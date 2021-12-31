#include <string>
#include "Game.h"
#include "Load.h"
#include "Silent.h"

//Amit Leibovitch : 318659745
//Maayan Mashhadi : 318702230



int main(int argc, char* argv[])
{
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	int input;
	cin >> colors;
	//if()
	Game game(colors);
	vector<string> screen_files = game.loadFiles();
	//if this is the load mode- the place that divided by 3 is the board place in the vector.
	//send approproate input to run in load mode

	input=game.printMenu();

	if (input != 2)
	{
		for (int i = 2; i < 3; i++)
		{
			game.run(screen_files[i], input);
			if (game.getPacman().getLives() == 0) 
			{
				game.restart();
				input=game.printMenu();
				i = -1;
				
				
			}
		}
	}
	else
	{
		game.choseBoard(screen_files);
		
	}
	/*else{
	* Load loadMode(colors,2);
	* screen_files = loadMode.loadFiles();
	* for (int i = 0; i < 3; i++)
		{
			loadMode.run(i);
			if (loadMode.getPacman().getLives() == 0) {
				loadMode.restart();
				i = -1;
			}
		}
	*/

	return 0;
}
