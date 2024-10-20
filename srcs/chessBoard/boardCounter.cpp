#include "../../include/header.hpp"

void    chessBoard::countPiecesOnBoard(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getType() == 'K'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteKing++;
            if (_board.at(i).piece->getType() == 'K'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.whiteKing++;

            if (_board.at(i).piece->getType() == 'Q'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteQueen++;
            if (_board.at(i).piece->getType() == 'Q'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.blackQueen++;

            if (_board.at(i).piece->getType() == 'N'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteKnight++;
            if (_board.at(i).piece->getType() == 'N'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.blackKnight++;

            if (_board.at(i).piece->getType() == 'R'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteRook++;
            if (_board.at(i).piece->getType() == 'R'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.blackRook++;

            if (_board.at(i).piece->getType() == 'B'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteBishop++;
            if (_board.at(i).piece->getType() == 'B'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.blackBishop++;

            if (_board.at(i).piece->getType() == 'P'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whitePawn++;
            if (_board.at(i).piece->getType() == 'P'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.blackPawn++;
            
            _boardCount.total++;
        }
    }
}
