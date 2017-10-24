#include "GameComponents\Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Create the system object.
	Game* game = new Game(L"D3D game");
	if (!game)
	{
		return 0;
	}

	// Initialize and run the system object.
	if (game->Initialize())
		game->Run();

	// Shutdown and release the system object.
	delete game;
	game = 0;

	return 0;
}