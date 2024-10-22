#include "../../include/header.hpp"

string  chessBoard::getOppositeColor(void)
{
    if (_color == "white")
        return (string("black"));
    return (string("white"));
}

void    chessBoard::setTurn(void)
{
    _turn++;
    if (_turn % 2 == 0)
        _color = "white";
    else
        _color = "black";
}

void    chessBoard::enableDisableEnPassant(void)
{
    if (_lastMove.obj == 'P')
    {
        if ((_color == "white" && (_lastMove.dest[1] == (_lastMove.dest[1] + 2)))
            || (_color == "black" && (_lastMove.dest[1] == (_lastMove.src[1] - 2))))
        {
            _enPassant = true;
            _enPassantDest = _lastMove.dest;
            if (_color == "white")
                _enPassantDest[1] = _enPassantDest[1] - 1;
            else
                _enPassantDest[1] = _enPassantDest[1] + 1;
        }
        else
            _enPassant = false, _enPassantDest.clear();
    }
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
        setTurn();
    }
    return (SUCCESS);
}
