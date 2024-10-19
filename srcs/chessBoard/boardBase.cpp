#include "../../include/header.hpp"

void    chessBoard::announceEvent(const int value, const bool cfail, const bool bfail, const string move)
{
    // if (value == 1)
    // {
    //     if (cfail == true || bfail == true)
    //         cout << _player << " to play." << endl;
    //     else
    //         cout << ERASE_LINE << _player << " to play." << endl;
    // }
    // if (value == 2)
    // {
    //     if (_turn != 0)
    //         cout << "\033[3A";
    //     else
    //         cout << "\033[2A";
    //     cout << ERASE_LINE;
    //     cout << _player << " played " << move << endl;
    // }
    // if (value == 5)
    // {
    //     cout << "\033[1A";
    //     cout << ERASE_LINE;
    //     cout << _player << " won the game! 🎉" << endl;
    // }
}

void    chessBoard::printBoard(void)
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL)
            {
                if (_board.at(getAtValue(coord)).piece->getType() == 'P')
                    cout << "[P] ; ";
                if (_board.at(getAtValue(coord)).piece->getType() == 'K')
                    cout << "[K] ; ";
                if (_board.at(getAtValue(coord)).piece->getType() == 'Q')
                    cout << "[Q] ; ";
                if (_board.at(getAtValue(coord)).piece->getType() == 'R')
                    cout << "[R] ; ";
                if (_board.at(getAtValue(coord)).piece->getType() == 'N')
                    cout << "[N] ; ";
                if (_board.at(getAtValue(coord)).piece->getType() == 'B')
                    cout << "[B] ; ";
            }
            else
                cout << "[ ] ; ";
        }
        cout << endl;
    }
    cout << endl;
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

void    chessBoard::setTurn(void)
{
    if (_turn % 2 == 0)
        _color = "white";
    else
        _color = "black";
}

int chessBoard::playMove(t_move move)
{
    _lastMove = move;
    setTurn();
    if (isLegal() != true)
    {
        _moveFailed = true;
        printIllegal();
        return (FAIL);
    }
    else
    {
        if (_lastMove.dest == "O-O" || _lastMove.dest == "O-O-O")
        {
            if (_color == "white")
                whiteCastles();
            if (_color == "black")
                blackCastles();
        }
        else
        {
            if (_lastMove.action == 'x' && isThereSomething(_lastMove.dest) != true
                && _enPassant == true && _enPassantDest == _lastMove.dest)
                priseEnPassant();
            else
            {
                movePiece(_lastMove.src, _lastMove.dest);
                if (isChessPiece(_lastMove.dest.at(_lastMove.dest.length() - 1)) == true)
                    promotePiece(_lastMove.dest, _lastMove.dest[_lastMove.dest.length() - 1]);
            }
        }
        enableDisableEnPassant();
        announceEvent(2, false, false, _lastMove.move);
        _turn++;
    }
    return (SUCCESS);
}
