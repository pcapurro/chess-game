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
                _boardCount.whiteKing++;
            if (_board.at(i).piece->getType() == 'Q'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.whiteKing++;

            if (_board.at(i).piece->getType() == 'N'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteKing++;
            if (_board.at(i).piece->getType() == 'N'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.whiteKing++;

            if (_board.at(i).piece->getType() == 'R'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteKing++;
            if (_board.at(i).piece->getType() == 'R'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.whiteKing++;

            if (_board.at(i).piece->getType() == 'B'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteKing++;
            if (_board.at(i).piece->getType() == 'B'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.whiteKing++;

            if (_board.at(i).piece->getType() == 'P'
                && _board.at(i).piece->getColor() == "white")
                _boardCount.whiteKing++;
            if (_board.at(i).piece->getType() == 'P'
                && _board.at(i).piece->getColor() == "black")
                _boardCount.whiteKing++;
            
            _boardCount.total++;
        }
    }
}
