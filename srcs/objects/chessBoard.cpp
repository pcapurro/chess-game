#include "../../include/header.hpp"

chessBoard::chessBoard()
{
    _turn = 0;
    _allocated = false;
    _player = "white";

    initBoard();
    if (checkBoardAllocation() != true)
        _allocated = false;
    else
        _allocated = true;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
            cout << "[" << _board.at(i).coord << "]" << " ; ";
        cout << endl;
    }
    cout << endl;
}

chessBoard::~chessBoard()
{
    ;
}

void    chessBoard::initBishops()
{
    _board.push_back({new Bishop("white", "c1"), "c1"});
    _board.push_back({new Bishop("white", "f1"), "f1"});
    _board.push_back({new Bishop("black", "c8"), "c8"});
    _board.push_back({new Bishop("black", "f8"), "f8"});
}

void    chessBoard::initRooksKnights()
{
    _board.push_back({new Knight("white", "g1"), "g1"});
    _board.push_back({new Knight("white", "b1"), "b1"});
    _board.push_back({new Knight("black", "g8"), "g8"});
    _board.push_back({new Knight("black", "b8"), "b8"});

    _board.push_back({new Rook("white", "a1"), "a1"});
    _board.push_back({new Rook("white", "h1"), "h1"});
    _board.push_back({new Rook("black", "a8"), "a8"});
    _board.push_back({new Rook("black", "h8"), "h8"});
}

void    chessBoard::initQueensKings()
{
    _board.push_back({new Queen("white", "d1"), "d1"});
    _board.push_back({new Queen("black", "d8"), "d8"});

    _board.push_back({new King("white", "e1"), "e1"});
    _board.push_back({new King("black", "e8"), "e8"});
}

void    chessBoard::initBoard()
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[k] + to_string(k + 1);
            if (k + 1 == 2)
                _board.push_back({new Pawn("white", coord), coord});
            if (k + 1 == 7)
                _board.push_back({new Pawn("black", coord), coord});

            if (k + 1 >= 3 && k + 1 <= 6)
                _board.push_back({NULL, coord});
        }
    }
    initRooksKnights();
    initBishops();
    initQueensKings();
}

bool    chessBoard::checkBoardAllocation() const
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece == nullptr
            && (_board.at(i).coord[1] == '1' || _board.at(i).coord[1] == '2'
            || _board.at(i).coord[1] == '8' || _board.at(i).coord[1] == '7'))
            return (false);
    }
    return (true);
}

bool    chessBoard::isAllocated(void) const
{
    return (_allocated);
}

void    chessBoard::printBoard(void) const
{
    ;
}

bool    chessBoard::fail(void) const
{
    return (_moveFailed);
}

bool    chessBoard::isCheck() const
{
    return (true);
}

bool    chessBoard::isCheckMate() const
{
    return (false);
}

bool    chessBoard::isLegal(const string move)
{
    // if (1)
    // {
    //     cout << "\033[2A" << "\033[2K";
    //     cerr << YELLOW << "Illegal move. " << COLOR_E;
    //     _moveFailed = true;
    //     return (false);
    // }
    _moveFailed = false;
    return (true);
}

int chessBoard::getCoordinateToX(const char c) const
{
    for (int i = 0; "abcdefgh"[i] != '\0'; i++)
    {
        if ("abcdefgh"[i] == c)
            return (i);
    }
    return (0);
}

void    chessBoard::announceEvent(const int value, const bool cfail, const bool bfail, const string move)
{
    if (_turn % 2 == 0)
        _player = "White";
    else
        _player = "Black";

    if (value == 1)
    {
        if (cfail != false || bfail != false)
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
    int target_x = getCoordinateToX(move[0]) - 1;;
    int target_y = atoi(move.c_str() + 1) - 1;;

    if (move.length() == 2)
    {
        ;
    }
    else
    {
        ;
    }
    announceEvent(2, false, false, move);
    _turn++;
}
