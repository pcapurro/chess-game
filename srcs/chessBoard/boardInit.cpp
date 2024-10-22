#include "../../include/shellChess.hpp"

chessBoard::chessBoard(void)
{
    _turn = 0;
    _allocated = false;
    _color = "white";

    _moveFailed = false;

    _whiteCastle = true;
    _blackCastle = true;

    _allocated = true;
    initBoard();
    if (checkBoardAllocation() == false)
        _allocated = false;
}

void    chessBoard::initBishops(void)
{
    _board.push_back({new (std::nothrow) Bishop('B', "white", "c1"), "c1"});
    _board.push_back({new (std::nothrow) Bishop('B', "white", "f1"), "f1"});
    _board.push_back({new (std::nothrow) Bishop('B', "black", "c8"), "c8"});
    _board.push_back({new (std::nothrow) Bishop('B', "black", "f8"), "f8"});
}

void    chessBoard::initRooksKnights(void)
{
    _board.push_back({new (std::nothrow) Knight('N', "white", "g1"), "g1"});
    _board.push_back({new (std::nothrow) Knight('N', "white", "b1"), "b1"});
    _board.push_back({new (std::nothrow) Knight('N', "black", "g8"), "g8"});
    _board.push_back({new (std::nothrow) Knight('N', "black", "b8"), "b8"});

    _board.push_back({new (std::nothrow) Rook('R', "white", "a1"), "a1"});
    _board.push_back({new (std::nothrow) Rook('R', "white", "h1"), "h1"});
    _board.push_back({new (std::nothrow) Rook('R', "black", "a8"), "a8"});
    _board.push_back({new (std::nothrow) Rook('R', "black", "h8"), "h8"});
}

void    chessBoard::initQueensKings(void)
{
    _board.push_back({new (std::nothrow) Queen('Q', "white", "d1"), "d1"});
    _board.push_back({new (std::nothrow) Queen('Q', "black", "d8"), "d8"});

    _board.push_back({new (std::nothrow) King('K', "white", "e1"), "e1"});
    _board.push_back({new (std::nothrow) King('K', "black", "e8"), "e8"});
}

void    chessBoard::initBoard(void)
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (k + 1 == 2)
                _board.push_back({new (std::nothrow) Pawn('P', "white", coord), coord});
            if (k + 1 == 7)
                _board.push_back({new (std::nothrow) Pawn('P', "black", coord), coord});
            
            if (k + 1 >= 3 && k + 1 <= 6)
                _board.push_back({NULL, coord});
        }
    }
    initRooksKnights();
    initBishops();
    initQueensKings();
}
