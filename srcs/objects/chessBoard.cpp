#include "../../include/header.hpp"

chessBoard::chessBoard()
{
    _turn = 0;
    
    _board = new(nothrow) chessPiece**[8];
    if (_board == nullptr)
        systemError();
    else
    {
        for (int i = 0; i != 8; i++)
        {
            _board[i] = new (nothrow) chessPiece*[8];
            if (_board[i] == nullptr)
            {
                i = i - 1;
                while (i != -1)
                    delete (_board[i]), i--;
                systemError();
            }
        }

        _board[0][0] = new Rook("black", "a8");
        _board[0][1] = new Knight("black", "b8");
        _board[0][2] = new Bishop("black", "c8");
        _board[0][3] = new Queen("black", "d8");
        _board[0][4] = new King("black", "e8");
        _board[0][5] = new Bishop("black", "f8");
        _board[0][6] = new Knight("black", "g8");
        _board[0][7] = new Rook("black", "h8");

        for (int i = 0; i != 8; i++)
        {
            _board[2][i] = NULL; _board[3][i] = NULL;
            _board[4][i] = NULL; _board[5][i] = NULL;
        }

        _board[7][1] = new Rook("white", "a1");
        _board[7][2] = new Knight("white", "b1");
        _board[7][3] = new Bishop("white", "c1");
        _board[7][4] = new Queen("white", "d1");
        _board[7][5] = new King("white", "e1");
        _board[7][6] = new Bishop("white", "f1");
        _board[7][7] = new Knight("white", "g1");
        _board[7][8] = new Rook("white", "h1");
    }
}
chessBoard::~chessBoard()
{
    ;
}

bool    chessBoard::isCheck() const
{
    return (true);
}

bool    chessBoard::isCheckMate() const
{
    return (false);
}

bool    chessBoard::isLegal(const string move) const
{
    return (true);
}

bool    chessBoard::isValid(const string move) const
{
    return (true);
}

void    chessBoard::announceEvent(const int value, const bool fail, const string move)
{
    if (_turn % 2 == 0)
        _player = "White";
    else
        _player = "Black";

    if (value == 1)
    {
        if (fail != false)
            cout << _player << " to play." << endl;
        else
            cout << "\033[2K" << _player << " to play." << endl;
    }
    if (value == 2)
    {
        if (_turn != 0)
            cout << "\033[3A";
        else
            cout << "\033[2A";
        cout << "\033[2K";
        cout << _player << " played " << move << endl;
    }
    if (value == 3)
    {
        cout << "\033[1A";
        cout << "\033[2K";
        cout << _player << " won the game! 🎉" << endl;
    }
}

void    chessBoard::playMove(const string move)
{
    // ...
    announceEvent(2, false, move);
    _turn++;
}
