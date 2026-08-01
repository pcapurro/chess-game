#include "VisualGame.hpp"

VisualGame::~VisualGame()
{
	if (_normalCursor != nullptr && _normalCursor != NULL)
		SDL_FreeCursor(_normalCursor);
	if (_playCursor != nullptr && _playCursor != NULL)
		SDL_FreeCursor(_playCursor);

	if (_mainRenderer != nullptr && _mainRenderer != NULL)
		SDL_DestroyRenderer(_mainRenderer);
	if (_mainWindow != nullptr && _mainWindow != NULL)
		SDL_DestroyWindow(_mainWindow);

	SDL_Quit();
}
