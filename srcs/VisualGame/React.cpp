#include "VisualGame.hpp"

void	VisualGame::reactKeyDown(const int key)
{
	if (key == SDLK_TAB)
		_visualInfo.visualDests = !_visualInfo.visualDests;

	if (_visualInfo.code == true)
	{
		_visualInfo.keyHistory.push_back(key);
		if (_visualInfo.keyHistory.size() > 11)
			_visualInfo.keyHistory.erase(_visualInfo.keyHistory.begin());

		if (isCodeDetected() == true)
			_visualInfo.code = false, cout << "You're pretty good!" << endl;
	}
}

void	VisualGame::reactMouseMotion(void)
{
	int	x = _visualInfo.x;
	int	y = _visualInfo.y;

	if (isBoardTargetZone(_visualInfo.actualCoords, x, y) == true)
		SDL_SetCursor(_playCursor);
	else
		SDL_SetCursor(_normalCursor);
}

void	VisualGame::reactMouseDown(const int key)
{
	int	x = _visualInfo.x;
	int	y = _visualInfo.y;

	if (isBoardTargetZone(_visualInfo.actualCoords, x, y) == true \
		&& _visualInfo.actualCoords != "none")
	{
		char			sign;
		string			src, dest;
		vector<string>	legalMoves;

		_visualInfo.droppedSrc = _visualInfo.actualCoords;
		_visualInfo.droppedDests.clear();

		_visualInfo.turn % 2 == 0 ? sign = '1' : sign = '8';

		legalMoves = _board->getLegalMoves();

		if (_visualInfo.droppedSrc == string{'e', sign} && _board->getType(string{'e', sign}) == 'K')
		{
			if (find(legalMoves.begin(), legalMoves.end(), "O-O") != legalMoves.end())
				_visualInfo.droppedDests.push_back({'g', sign});
			if (find(legalMoves.begin(), legalMoves.end(), "O-O-O") != legalMoves.end())
				_visualInfo.droppedDests.push_back({'c', sign});
		}

		for (size_t i = 0; i != legalMoves.size(); i++)
		{
			if (legalMoves.at(i) != "O-O" && legalMoves.at(i) != "O-O-O")
			{
				src = {legalMoves.at(i)[1], legalMoves.at(i)[2]};
				dest = {legalMoves.at(i)[3], legalMoves.at(i)[4]};

				if (src == _visualInfo.droppedSrc)
					_visualInfo.droppedDests.push_back(dest);
			}
		}
	}

	if (key == SDL_BUTTON_RIGHT)
		_visualInfo.visualCoords = !_visualInfo.visualCoords;

	if (isColorTargetZone(x, y) == true)
		++_visualInfo.boardColor == COLOR_NB ? _visualInfo.boardColor = 0 : _visualInfo.boardColor;
	if (isEvaluationTargetZone(x, y) == true)
		_visualInfo.evaluation = !_visualInfo.evaluation;
}

void	VisualGame::reactMouseUp(void)
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
	{
		_visualInfo.promotion = true;
		_visualInfo.actualCoords = waitForPromotion();
		_visualInfo.promotion = false;
	}

	_visualInfo.droppedDests.clear();
}
