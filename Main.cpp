// SFML header
#include <SFML/Graphics.hpp>

// importing main window header file with main game loop
#include "MainWindow.h"

int main()
{
	// defining window object (with fixed size) on which the game is working
	MainWindow mainWindow;
	mainWindow.RunGameLoop();

	return 0;
}
