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

void    chessBoard::playMove(const char obj, const string src, const string dest, const string move)
{
    if (_turn % 2 == 0)
        _color = "white";
    else
        _color = "black";

    if (isLegal(obj, src, dest) != true)
        return ;
    else
    {
        if (dest == "O-O" || dest == "O-O-O")
        {
            if (_color == "white")
                whiteCastles(dest);
            if (_color == "black")
                blackCastles(dest);
        }
        else
        {
            movePiece(_src, dest);
            if (isChessPiece(dest.at(dest.length() - 1)) == true)
                promotePiece(dest, dest[dest.length() - 1]);
        }
        announceEvent(2, false, false, move);
        _turn++;
    }
}
