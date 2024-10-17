#include "../../include/header.hpp"

size_t  chessBoard::getAtValue(const string coord) const
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
}

void    chessBoard::promotePiece(const string initialCoord, char pieceType)
{
    string  initialCoordUpdated;
    string  color;
    size_t  atValue;

    initialCoordUpdated = initialCoord;
    initialCoordUpdated[2] = '\0';
    atValue = getAtValue(initialCoordUpdated);
    color = _board.at(atValue).piece->getColor();
    
    removePiece(initialCoord);
    if (pieceType == 'Q')
        _board.at(atValue).piece = new Queen('Q', color, initialCoordUpdated);
    if (pieceType == 'N')
        _board.at(atValue).piece = new Knight('N', color, initialCoordUpdated);
    if (pieceType == 'B')
        _board.at(atValue).piece = new Bishop('B', color, initialCoordUpdated);
    if (pieceType == 'R')
        _board.at(atValue).piece = new Rook('R', color, initialCoordUpdated);
    
    if (_board.at(atValue).piece == nullptr)
        _allocated = false, _board.at(atValue).piece = NULL;
}

void    chessBoard::movePiece(const string initialCoord, const string newCoord)
{
    chessPiece  *piece;
    size_t      atValue;
    string      newCoordUpdated;
    
    atValue = getAtValue(initialCoord); 
    piece = _board.at(atValue).piece;
    _board.at(atValue).piece = NULL;

    newCoordUpdated = newCoord;
    if (newCoord.length() == 3)
        newCoordUpdated = newCoord, newCoordUpdated[2] = '\0';
    
    removePiece(newCoordUpdated);
    atValue = getAtValue(newCoordUpdated);
    _board.at(atValue).piece = piece;

    cout << "moving " << initialCoord << " to " << newCoord << endl;
}
