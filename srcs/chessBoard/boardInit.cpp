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
    // if (checkBoardAllocation() == false)
    //     _allocated = false;
}

void    chessBoard::initBishops(void)
{
    _board.push_back({new (std::nothrow) Bishop("white", "c1"), "c1"});
    _board.push_back({new (std::nothrow) Bishop("white", "f1"), "f1"});
    _board.push_back({new (std::nothrow) Bishop("black", "c8"), "c8"});
    _board.push_back({new (std::nothrow) Bishop("black", "f8"), "f8"});
}

void    chessBoard::initRooksKnights(void)
{
    _board.push_back({new (std::nothrow) Knight("white", "g1"), "g1"});
    _board.push_back({new (std::nothrow) Knight("white", "b1"), "b1"});
    _board.push_back({new (std::nothrow) Knight("black", "g8"), "g8"});
    _board.push_back({new (std::nothrow) Knight("black", "b8"), "b8"});

    _board.push_back({new (std::nothrow) Rook("white", "a1"), "a1"});
    _board.push_back({new (std::nothrow) Rook("white", "h1"), "h1"});
    _board.push_back({new (std::nothrow) Rook("black", "a8"), "a8"});
    _board.push_back({new (std::nothrow) Rook("black", "h8"), "h8"});
}

void    chessBoard::initQueensKings(void)
{
    _board.push_back({new (std::nothrow) Queen("white", "d1"), "d1"});
    _board.push_back({new (std::nothrow) Queen("black", "d8"), "d8"});

    _board.push_back({new (std::nothrow) King("white", "e1"), "e1"});
    _board.push_back({new (std::nothrow) King("black", "e8"), "e8"});
}

void    chessBoard::initBoard(void)
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);            
            if (coord != "h5" && coord != "h7" && coord != "h6")
                _board.push_back({NULL, coord});
        }
    }
    _board.push_back({new King("white", "h5"), "h5"});
    _board.push_back({new King("black", "h7"), "h7"});

    _board.push_back({new Pawn("white", "h6"), "h6"});
}
