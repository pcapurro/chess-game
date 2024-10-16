#include "../../include/header.hpp"

size_t  chessBoard::getAtValue(const string coord)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).coord == coord)
            return (i);
    }
    return (0);
}

void    chessBoard::removePiece(const string coord)
{
    size_t  atValue = getAtValue(coord);
    if (_board.at(atValue).piece != NULL)
    {
        delete _board.at(atValue).piece;
        _board.at(atValue).piece = NULL;
    }
    cout << "removing piece at i => " << atValue << endl;
}

void    chessBoard::promoteMovePiece(const string initialCoord, const string newCoord, char pieceType)
{
    string  newCoordUpdated;

    newCoordUpdated = to_string(newCoord[0] + newCoord[1]);
}

void    chessBoard::movePiece(const string initialCoord, const string newCoord)
{
    chessPiece  *piece;
    size_t      atValue;
    
    atValue = getAtValue(initialCoord); 
    piece = _board.at(atValue).piece;
    _board.at(atValue).piece = NULL;

    removePiece(newCoord);
    atValue = getAtValue(newCoord);
    _board.at(atValue).piece = piece;
}
