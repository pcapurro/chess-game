#include "visualGame.hpp"

void    visualGame::reactKeyDown(const int key)
{
    if (_code == true)
    {
        _keyHistory.push_back(key);
        if (_keyHistory.size() > 11)
            _keyHistory.erase(_keyHistory.begin());

        if (isCodeDetected() == true)
            _code = false, cout << "You're pretty good!" << endl;
    }
}

void    visualGame::reactMouseMotion(void)
{
    if (isBoardTargetZone(_actualCoords, _x, _y) == true)
        SDL_SetCursor(_playCursor);
    else
        SDL_SetCursor(_normalCursor);
}

void    visualGame::reactMouseDown(const int key)
{
    if (isBoardTargetZone(_actualCoords, _x, _y) == true
        && _actualCoords != "none")
        _droppedSrc = _actualCoords;

    if (key == SDL_BUTTON_RIGHT)
        _visualCoords = !_visualCoords;

    if (isColorTargetZone(_actualCoords, _x, _y) == true)
        ++_boardColor == COLOR_NB ? _boardColor = 0 : _boardColor;
    if (isEvaluationTargetZone(_actualCoords, _x, _y) == true)
        _evaluation = !_evaluation;
}

void    visualGame::reactMouseUp(void)
{
    _droppedDest = _actualCoords;
    if (_droppedSrc == "")
    {
        _droppedSrc = _clickSrc;
        if (_board->isLegal(_board->getType(_droppedSrc) + _droppedSrc + _droppedDest))
            displayMoveAnimation(_droppedSrc + _droppedDest);
    }

    if (isPromotion(_actualCoords) == true
        && _board->isLegal(_board->getType(_droppedSrc) + _droppedSrc + _droppedDest + 'Q') == true)
        _actualCoords = waitForPromotion();
}
