#include "../../include/header.hpp"

chessBoard::chessBoard()
{
    _turn = 0;
    _allocated = false;
    _player = "white";
    
    _board = new(nothrow) chessPiece*[64];
    if (_board == nullptr)
        systemError();
    else
    {
        for (int i = 0; i != 64; i++)
            _board[i] = NULL;

        _board[0] = new Rook("black", "a8");
        _board[1] = new Knight("black", "b8");
        _board[2] = new Bishop("black", "c8");
        _board[3] = new Queen("black", "d8");
        _board[4] = new King("black", "e8");
        _board[5] = new Bishop("black", "f8");
        _board[6] = new Knight("black", "g8");
        _board[7] = new Rook("black", "h8");

        for (int i = 8, k = 0; i != 16; i++)
            _board[i] = new Pawn("black", to_string('0') + "7");

        for (int i = 48, k = 0; i != 56; i++)
            _board[i] = new Pawn("white", to_string('0') + "7");

        _board[56] = new Rook("white", "a1");
        _board[57] = new Knight("white", "b1");
        _board[58] = new Bishop("white", "c1");
        _board[59] = new Queen("white", "d1");
        _board[60] = new King("white", "e1");
        _board[61] = new Bishop("white", "f1");
        _board[62] = new Knight("white", "g1");
        _board[63] = new Rook("white", "h1");

        for (int i = 0; i != 64; i++)
        {
            if (_board[i] == nullptr && (i < 16 || i > 47))
            {
                _allocated = false;
                return ;
            }
        }
        _allocated = true;
    }
}
chessBoard::~chessBoard()
{
    for (int i = 0; i != 64; i++)
    {
        if (_board[i] && _board[i] != nullptr
            && _board[i] != NULL)
            delete _board[i];
    }
    delete [] _board;
}

bool    chessBoard::isAllocated(void) const
{
    return (_allocated);
}

void    chessBoard::printBoard(void) const
{
    for (int i = 0, k = 0; i != 64; i++)
    {
        if (_board[i] != NULL && i > 32)
            cout << "[WP] ";
        else if (_board[i] != NULL && i < 32)
            cout << "[BP] ";
        else
            cout << "[  ] ";
        k++;
        if (k == 8)
            k = 0, cout << endl;
    }
    cout << endl;
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
    announceEvent(2, false, move);
    _turn++;
}
