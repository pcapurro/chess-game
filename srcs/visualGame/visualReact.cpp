#include "visualGame.hpp"

void	visualGame::reactKeyDown(const int key)
{
	if (_visualInfo._code == true)
	{
		_visualInfo._keyHistory.push_back(key);
		if (_visualInfo._keyHistory.size() > 11)
			_visualInfo._keyHistory.erase(_visualInfo._keyHistory.begin());

		if (isCodeDetected() == true)
			_visualInfo._code = false, cout << "You're pretty good!" << endl;
	}
}

void	visualGame::reactMouseMotion(void)
{
	int	x = _visualInfo._x;
	int	y = _visualInfo._y;

	if (isBoardTargetZone(_visualInfo._actualCoords, x, y) == true)
		SDL_SetCursor(_playCursor);
	else
		SDL_SetCursor(_normalCursor);
}

void	visualGame::reactMouseDown(const int key)
{
	int	x = _visualInfo._x;
	int	y = _visualInfo._y;

	if (isBoardTargetZone(_visualInfo._actualCoords, x, y) == true \
		&& _visualInfo._actualCoords != "none")
	{
		vector<string>	legalMoves;
		string			src, dest;

		_visualInfo._droppedSrc = _visualInfo._actualCoords;
		_visualInfo._droppedDests.clear();

		legalMoves = _board->getLegalMoves();
		for (size_t i = 0; i != legalMoves.size(); i++)
		{
			src = {legalMoves.at(i)[1], legalMoves.at(i)[2]};
			dest = {legalMoves.at(i)[3], legalMoves.at(i)[4]};

			if (src == _visualInfo._droppedSrc)
				_visualInfo._droppedDests.push_back(dest);
		}
	}

	if (key == SDL_BUTTON_RIGHT)
		_visualInfo._visualCoords = !_visualInfo._visualCoords;

	if (isColorTargetZone(x, y) == true)
		++_visualInfo._boardColor == COLOR_NB ? _visualInfo._boardColor = 0 : _visualInfo._boardColor;
	if (isEvaluationTargetZone(x, y) == true)
		_visualInfo._evaluation = !_visualInfo._evaluation;
}

void	visualGame::reactMouseUp(void)
{
	_visualInfo._droppedDest = _visualInfo._actualCoords;
	if (_visualInfo._droppedSrc == "")
	{
		_visualInfo._droppedSrc = _visualInfo._clickSrc;
		if (_board->isLegal(_board->getType(_visualInfo._droppedSrc) + \
			_visualInfo._droppedSrc + _visualInfo._droppedDest))
			displayMoveAnimation(_visualInfo._droppedSrc + _visualInfo._droppedDest);
	}

	if (isPromotion(_visualInfo._actualCoords) == true
		&& _board->isLegal(_board->getType(_visualInfo._droppedSrc) + \
			_visualInfo._droppedSrc + _visualInfo._droppedDest + 'Q') == true)
		_visualInfo._actualCoords = waitForPromotion();
}
