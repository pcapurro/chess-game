#include "../../include/header.hpp"

void    chessBoard::enableDisableEnPassant(void)
{
    if (_lastMove.obj == 'P')
    {
        if ((_color == "white" && (_lastMove.dest[1] == (_lastMove.dest[1] + 2)))
            || (_color == "black" && (_lastMove.dest[1] == (_lastMove.src[1] - 2))))
        {
            _enPassant = true;
            _enPassantDest = _lastMove.dest;
            if (_color == "white")
                _enPassantDest[1] = _enPassantDest[1] - 1;
            else
                _enPassantDest[1] = _enPassantDest[1] + 1;
        }
        else
            _enPassant = false, _enPassantDest.clear();
    }
}

void    chessBoard::priseEnPassant(void)
{
    chessPiece  *piece;
    size_t      atValue;
    string      newCoordUpdated;

    atValue = getAtValue(_lastMove.src); 
    piece = _board.at(atValue).piece;
    _board.at(atValue).piece = NULL;

    atValue = getAtValue(_lastMove.dest);
    _board.at(atValue).piece = piece;
    _board.at(atValue).piece->move();
    _board.at(atValue).piece->updatePos(_lastMove.dest);

    newCoordUpdated = _lastMove.dest;
    if (_color == "white")
        newCoordUpdated[1] = newCoordUpdated[1] - 1;
    if (_color == "black")
        newCoordUpdated[1] = newCoordUpdated[1] + 1;

    removePiece(newCoordUpdated);
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
        _board.at(atValue).piece = new (std::nothrow) Queen('Q', color, initialCoordUpdated);
    if (pieceType == 'N')
        _board.at(atValue).piece = new (std::nothrow) Knight('N', color, initialCoordUpdated);
    if (pieceType == 'B')
        _board.at(atValue).piece = new (std::nothrow) Bishop('B', color, initialCoordUpdated);
    if (pieceType == 'R')
        _board.at(atValue).piece = new (std::nothrow) Rook('R', color, initialCoordUpdated);
    
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

    _board.at(atValue).piece->move();
    _board.at(atValue).piece->updatePos(newCoord);

    if (_board.at(atValue).piece->getType() == 'K')
    {
        if (_board.at(atValue).piece->getColor() == "white")
            _whiteCastle = false;
        if (_board.at(atValue).piece->getColor() == "black")
            _blackCastle = false;
    }
}


void    chessBoard::whiteCastles(void)
{
    if (_lastMove.move == "O-O")
    {
        movePiece("h1", "f1");
        movePiece("e1", "g1");
    }
    if (_lastMove.move == "O-O-O")
    {
        movePiece("e1", "c1");
        movePiece("a1", "d1");
    }
}

void    chessBoard::blackCastles(void)
{
    if (_lastMove.move == "O-O")
    {
        movePiece("e8", "g8");
        movePiece("h8", "f8");
    }
    if (_lastMove.move == "O-O-O")
    {
        movePiece("e8", "c8");
        movePiece("a8", "d8");
    }
}
