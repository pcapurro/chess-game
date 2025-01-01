#include "chessBoard.hpp"

chessBoard::chessBoard(void)
{
    _gameInfo._turn = 0;
    _allocated = true;
    _free = true;
    _gameInfo._color = "white";

    _gameInfo._moveFailed = false;

    _gameInfo._whiteCastle = true;
    _gameInfo._blackCastle = true;

    _gameInfo._whiteCastled = false;
    _gameInfo._blackCastled = false;
    
    _gameInfo._draw = false;
    _gameInfo._checkmate = false;

    _gameInfo._enPassant = false;
    _gameInfo._enPassantDest = "";

    _boardCount.whiteMaterial = 39;
    _boardCount.blackMaterial = 39;

    initBoard();
    if (checkBoardAllocation() == false)
        _allocated = false;
}

chessBoard::chessBoard(const chessBoard *originalBoard)
{
    _free = false;

    _gameInfo._turn = originalBoard->_gameInfo._turn;
    _gameInfo._color = originalBoard->_gameInfo._color;

    _gameInfo._whiteCastle = originalBoard->_gameInfo._whiteCastle;
    _gameInfo._blackCastle = originalBoard->_gameInfo._blackCastle;

    _gameInfo._whiteCastled = originalBoard->_gameInfo._whiteCastled;
    _gameInfo._blackCastled = originalBoard->_gameInfo._blackCastled;

    _gameInfo._enPassant = originalBoard->_gameInfo._enPassant;
    _gameInfo._enPassantDest = originalBoard->_gameInfo._enPassantDest;

    _gameInfo._check = originalBoard->_gameInfo._check;
    _gameInfo._draw = originalBoard->_gameInfo._draw;
    _gameInfo._checkmate = originalBoard->_gameInfo._checkmate;

    for (int i = 0; i != 64; i++)
        _board.push_back(originalBoard->_board.at(i));
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
                _board.push_back({nullptr, coord});
        }
    }
    initRooksKnights();
    initBishops();
    initQueensKings();
}
