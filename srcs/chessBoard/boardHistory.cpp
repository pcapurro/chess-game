#include "../../include/header.hpp"

void    chessBoard::printHistory(void)
{
    cout << ERASE_LINE << "Game summary: ";
    for (int i = 0; i != _history.size(); i++)
    {
        cout << i + 1 << "." << _history.at(i) << " ";
    }
    cout << endl;
}

void    chessBoard::addToHistory(void)
{
    if (_lastMove.action == 'x')
    {
        if (_lastMove.obj != 'P')
            _history.push_back(_lastMove.obj + _lastMove.src + "x" + _lastMove.dest);
        else
            _history.push_back(_lastMove.src + "x" + _lastMove.dest);
    }
    else
    {
        if (_lastMove.obj != 'P')
            _history.push_back(_lastMove.obj + _lastMove.src + "-" + _lastMove.dest);
        else
            _history.push_back(_lastMove.dest);
    }
}
