#include "chessBoard.hpp"

chessBoard::chessBoard(void)
{
    _turn = 0;
    _allocated = true;
    _color = "white";

    _moveFailed = false;

    _whiteCastle = true;
    _blackCastle = true;
    
    _draw = false;
    _checkmate = false;

    _enPassant = false;
    _enPassantDest = "";

    initBoard();
    if (checkBoardAllocation() == false)
        _allocated = false;
}

void    chessBoard::operator=(const chessBoard *originalBoard)
{
    this->_turn = originalBoard->_turn;
    this->_color = originalBoard->_color;

    this->_whiteCastle = originalBoard->_whiteCastle;
    this->_blackCastle = originalBoard->_blackCastle;

    this->_enPassant = originalBoard->_enPassant;
    this->_enPassantDest = originalBoard->_enPassantDest;

    for (int i = 0; i != 64; i++)
        this->_board.push_back(originalBoard->_board.at(i));
}

void    chessBoard::initBishops(void)
{
    _board.push_back({new (nothrow) Bishop("white", "c1"), "c1"});
    _board.push_back({new (nothrow) Bishop("white", "f1"), "f1"});
    _board.push_back({new (nothrow) Bishop("black", "c8"), "c8"});
    _board.push_back({new (nothrow) Bishop("black", "f8"), "f8"});
}

void    chessBoard::initRooksKnights(void)
{
    _board.push_back({new (nothrow) Knight("white", "g1"), "g1"});
    _board.push_back({new (nothrow) Knight("white", "b1"), "b1"});
    _board.push_back({new (nothrow) Knight("black", "g8"), "g8"});
    _board.push_back({new (nothrow) Knight("black", "b8"), "b8"});

    _board.push_back({new (nothrow) Rook("white", "a1"), "a1"});
    _board.push_back({new (nothrow) Rook("white", "h1"), "h1"});
    _board.push_back({new (nothrow) Rook("black", "a8"), "a8"});
    _board.push_back({new (nothrow) Rook("black", "h8"), "h8"});
}

void    chessBoard::initQueensKings(void)
{
    _board.push_back({new (nothrow) Queen("white", "d1"), "d1"});
    _board.push_back({new (nothrow) Queen("black", "d8"), "d8"});

    _board.push_back({new (nothrow) King("white", "e1"), "e1"});
    _board.push_back({new (nothrow) King("black", "e8"), "e8"});
}

void    chessBoard::initBoard(void)
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (k + 1 == 2)
                _board.push_back({new (nothrow) Pawn ("white", coord), coord});
            if (k + 1 == 7)
                _board.push_back({new (nothrow) Pawn ("black", coord), coord});
            
            if (k + 1 >= 3 && k + 1 <= 6)
                _board.push_back({NULL, coord});
        }
    }
    initRooksKnights();
    initBishops();
    initQueensKings();
}
