#include "../../include/header.hpp"

bool    chessBoard::fail(void) const
{
    return (_moveFailed);
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

int chessBoard::playMove(t_move move)
{
    _lastMove = move;
    if (isLegal() == false)
    {
        _moveFailed = true;
        return (FAIL);
    }
    else
    {
        _moveFailed = false;

        if (_lastMove.dest == "O-O" || _lastMove.dest == "O-O-O")
        {
            if (_color == "white")
                whiteCastles();
            if (_color == "black")
                blackCastles();
        }
        else
        {
            if (_lastMove.action == 'x' && isThereSomething(_lastMove.dest) == false
                && _enPassant == true && _enPassantDest == _lastMove.dest)
                priseEnPassant();
            else
            {
                movePiece(_lastMove.src, _lastMove.dest);
                if (isChessPiece(_lastMove.dest.at(_lastMove.dest.length() - 1)) == true)
                    promotePiece(_lastMove.dest, _lastMove.dest[_lastMove.dest.length() - 1]);
                
                if (_allocated == false)
                    return (ERR);
            }
        }
        enableDisableEnPassant();
        addToHistory();

        ++_turn % 2 == 0 ? _color = "white" : _color = "black";
    }
    return (SUCCESS);
}
