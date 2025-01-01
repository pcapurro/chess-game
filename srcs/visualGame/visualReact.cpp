#include "visualGame.hpp"

void	visualGame::reactKeyDown(const int key)
{
	if (visualInfo._code == true)
	{
		visualInfo._keyHistory.push_back(key);
		if (visualInfo._keyHistory.size() > 11)
			visualInfo._keyHistory.erase(visualInfo._keyHistory.begin());

		if (isCodeDetected() == true)
			visualInfo._code = false, cout << "You're pretty good!" << endl;
	}
}

void	visualGame::reactMouseMotion(void)
{
	int	x = visualInfo._x;
	int	y = visualInfo._y;

	if (isBoardTargetZone(visualInfo._actualCoords, x, y) == true)
		SDL_SetCursor(_playCursor);
	else
		SDL_SetCursor(_normalCursor);
}

void	visualGame::reactMouseDown(const int key)
{
	int	x = visualInfo._x;
	int	y = visualInfo._y;

	if (isBoardTargetZone(visualInfo._actualCoords, x, y) == true \
		&& visualInfo._actualCoords != "none")
		visualInfo._droppedSrc = visualInfo._actualCoords;

	if (key == SDL_BUTTON_RIGHT)
		visualInfo._visualCoords = !visualInfo._visualCoords;

	if (isColorTargetZone(x, y) == true)
		++visualInfo._boardColor == COLOR_NB ? visualInfo._boardColor = 0 : visualInfo._boardColor;
	if (isEvaluationTargetZone(x, y) == true)
		visualInfo._evaluation = !visualInfo._evaluation;
}

void	visualGame::reactMouseUp(void)
{
	visualInfo._droppedDest = visualInfo._actualCoords;
	if (visualInfo._droppedSrc == "")
	{
		visualInfo._droppedSrc = visualInfo._clickSrc;
		if (_board->isLegal(_board->getType(visualInfo._droppedSrc) + \
			visualInfo._droppedSrc + visualInfo._droppedDest))
			displayMoveAnimation(visualInfo._droppedSrc + visualInfo._droppedDest);
	}

	if (isPromotion(visualInfo._actualCoords) == true
		&& _board->isLegal(_board->getType(visualInfo._droppedSrc) + \
			visualInfo._droppedSrc + visualInfo._droppedDest + 'Q') == true)
		visualInfo._actualCoords = waitForPromotion();
}
