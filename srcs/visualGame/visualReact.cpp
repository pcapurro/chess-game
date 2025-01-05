#include "visualGame.hpp"

void	visualGame::reactKeyDown(const int key)
{
	if (_visualInfo.code == true)
	{
		_visualInfo.keyHistory.push_back(key);
		if (_visualInfo.keyHistory.size() > 11)
			_visualInfo.keyHistory.erase(_visualInfo.keyHistory.begin());

		if (isCodeDetected() == true)
			_visualInfo.code = false, cout << "You're pretty good!" << endl;
	}
}

void	visualGame::reactMouseMotion(void)
{
	int	x = _visualInfo.x;
	int	y = _visualInfo.y;

	if (isBoardTargetZone(_visualInfo.actualCoords, x, y) == true)
		SDL_SetCursor(_playCursor);
	else
		SDL_SetCursor(_normalCursor);
}

void	visualGame::reactMouseDown(const int key)
{
	int	x = _visualInfo.x;
	int	y = _visualInfo.y;

	if (isBoardTargetZone(_visualInfo.actualCoords, x, y) == true \
		&& _visualInfo.actualCoords != "none")
	{
		vector<string>	legalMoves;
		string			src, dest;

		_visualInfo.droppedSrc = _visualInfo.actualCoords;
		_visualInfo.droppedDests.clear();

		legalMoves = _board->getLegalMoves();
		for (size_t i = 0; i != legalMoves.size(); i++)
		{
			src = {legalMoves.at(i)[1], legalMoves.at(i)[2]};
			dest = {legalMoves.at(i)[3], legalMoves.at(i)[4]};

			if (src == _visualInfo.droppedSrc)
				_visualInfo.droppedDests.push_back(dest);
		}
	}

	if (key == SDL_BUTTON_RIGHT)
		_visualInfo.visualCoords = !_visualInfo.visualCoords;

	if (isColorTargetZone(x, y) == true)
		++_visualInfo.boardColor == COLOR_NB ? _visualInfo.boardColor = 0 : _visualInfo.boardColor;
	if (isEvaluationTargetZone(x, y) == true)
		_visualInfo.evaluation = !_visualInfo.evaluation;
}

void	visualGame::reactMouseUp(void)
{
	_visualInfo.droppedDest = _visualInfo.actualCoords;
	if (_visualInfo.droppedSrc == "")
	{
		_visualInfo.droppedSrc = _visualInfo.clickSrc;
		if (_board->isLegal(_board->getType(_visualInfo.droppedSrc) + \
			_visualInfo.droppedSrc + _visualInfo.droppedDest))
			displayMoveAnimation(_visualInfo.droppedSrc + _visualInfo.droppedDest);
	}

	if (isPromotion(_visualInfo.actualCoords) == true
		&& _board->isLegal(_board->getType(_visualInfo.droppedSrc) + \
			_visualInfo.droppedSrc + _visualInfo.droppedDest + 'Q') == true)
		_visualInfo.actualCoords = waitForPromotion();
}
