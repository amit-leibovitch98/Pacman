#include <filesystem>
#include <string>
#include <set>
#include "Game.h"

namespace fs = std::filesystem;

bool suffixScreen(string file_name);

int main()
{
	
	cout << "If you want to play with colors enter 1, otherwise enter 0" << endl;
	bool colors;
	cin >> colors;
	Game game(colors);

	string prefix = ".\\";
	set<string> screen_files;
	for (const auto& file : fs::directory_iterator("."))
		if (suffixScreen(file.path().u8string()))
			screen_files.insert(file.path().u8string());

	for (set<string>::iterator i = screen_files.begin(); i != screen_files.end(); i++)
	{
		string file_name = i->substr(prefix.length());

		game.run(file_name);
		game.closeFile();
	}
	return 0;
}

bool suffixScreen(string file_name)
{
	string suffix = ".screen";
	return file_name.size() >= suffix.size() && 0 == file_name.compare(file_name.size() - suffix.size(), suffix.size(), suffix);

}