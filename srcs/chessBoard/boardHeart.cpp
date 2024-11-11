#include "chessBoard.hpp"

void    chessBoard::enableDisableEnPassant(void)
{
    char    obj = _gameInfo._lastMove.obj;
    string  src = _gameInfo._lastMove.src;
    string  dest = _gameInfo._lastMove.dest;

    if (obj == 'P')
    {
        if ((_gameInfo._color == "white" && dest[1] == src[1] + 2 && dest[1] == '4') || (_gameInfo._color == "black" 
            && dest[1] == src[1] - 2 && dest[1] == '5'))
        {
            _gameInfo._enPassant = true;
            _gameInfo._enPassantDest = dest;

            if (_gameInfo._color == "white")
                _gameInfo._enPassantDest[1] = _gameInfo._enPassantDest[1] - 1;
            else
                _gameInfo._enPassantDest[1] = _gameInfo._enPassantDest[1] + 1;
        }
        else
            _gameInfo._enPassant = false, _gameInfo._enPassantDest.clear();
    }
}

void    chessBoard::priseEnPassant(const bool free)
{
    chessPiece  *piece;
    size_t      atValue;
    string      newCoordUpdated;

    atValue = getAtValue(_gameInfo._lastMove.src); 
    piece = _board.at(atValue).piece;
    _board.at(atValue).piece = NULL;

    atValue = getAtValue(_gameInfo._lastMove.dest);
    _board.at(atValue).piece = piece;
    _board.at(atValue).piece->move();
    _board.at(atValue).piece->updatePos(_gameInfo._lastMove.dest);

    newCoordUpdated = _gameInfo._lastMove.dest;
    if (_gameInfo._color == "white")
        newCoordUpdated[1] = newCoordUpdated[1] - 1;
    if (_gameInfo._color == "black")
        newCoordUpdated[1] = newCoordUpdated[1] + 1;

    removePiece(newCoordUpdated, free);
}

void    chessBoard::removePiece(const string coord, const bool free)
{
    size_t  atValue = getAtValue(coord);
    if (_board.at(atValue).piece != NULL)
    {
        if (free == true)
            delete _board.at(atValue).piece;
        _board.at(atValue).piece = NULL;
    }
}

void    chessBoard::promotePiece(const string initialCoord, char pieceType, const bool free)
{
    string  initialCoordUpdated;
    string  color;
    size_t  atValue;

    initialCoordUpdated = initialCoord;
    initialCoordUpdated[2] = '\0';
    atValue = getAtValue(initialCoordUpdated);
    color = _board.at(atValue).piece->getColor();
    
    removePiece(initialCoord, free);
    if (pieceType == 'Q')
        _board.at(atValue).piece = new (nothrow) Queen(color, initialCoordUpdated);
    if (pieceType == 'N')
        _board.at(atValue).piece = new (nothrow) Knight(color, initialCoordUpdated);
    if (pieceType == 'B')
        _board.at(atValue).piece = new (nothrow) Bishop(color, initialCoordUpdated);
    if (pieceType == 'R')
        _board.at(atValue).piece = new (nothrow) Rook(color, initialCoordUpdated);
    
    if (_board.at(atValue).piece == nullptr)
        _allocated = false, _board.at(atValue).piece = NULL;
}

void    chessBoard::movePiece(const string initialCoord, const string newCoord, const bool free)
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
    
    removePiece(newCoordUpdated, free);
    atValue = getAtValue(newCoordUpdated);
    _board.at(atValue).piece = piece;

    _board.at(atValue).piece->move();
    _board.at(atValue).piece->updatePos(newCoord);

    if (_board.at(atValue).piece->getType() == 'K' || _board.at(atValue).piece->getType() == 'R')
    {
        if (_board.at(atValue).piece->getOriginalCoord() == "a1" || _board.at(atValue).piece->getOriginalCoord() == "h1"
            || _board.at(atValue).piece->getOriginalCoord() == "e1")
            _gameInfo._whiteShortCastle = false, _gameInfo._whiteLongCastle = false;
        
        if (_board.at(atValue).piece->getOriginalCoord() == "a8" || _board.at(atValue).piece->getOriginalCoord() == "h8"
            || _board.at(atValue).piece->getOriginalCoord() == "e8")
            _gameInfo._blackShortCastle = false, _gameInfo._blackLongCastle = false;
    }
}


void    chessBoard::whiteCastles(void)
{
    if (_gameInfo._lastMove.dest == "O-O")
    {
        movePiece("h1", "f1");
        movePiece("e1", "g1");
    }
    if (_gameInfo._lastMove.dest == "O-O-O")
    {
        movePiece("e1", "c1");
        movePiece("a1", "d1");
    }
    _gameInfo._whiteShortCastle = false, _gameInfo._whiteLongCastle = false;
}

void    chessBoard::blackCastles(void)
{
    if (_gameInfo._lastMove.dest == "O-O")
    {
        movePiece("e8", "g8");
        movePiece("h8", "f8");
    }
    if (_gameInfo._lastMove.dest == "O-O-O")
    {
        movePiece("e8", "c8");
        movePiece("a8", "d8");
    }
    _gameInfo._blackShortCastle = false, _gameInfo._blackLongCastle = false;
}

void    chessBoard::addToHistory(void)
{
    char    action = _gameInfo._lastMove.action;
    char    obj = _gameInfo._lastMove.obj;
    string  src = _gameInfo._lastMove.src;
    string  dest = _gameInfo._lastMove.dest;

    if (dest == "O-O" || dest == "O-O-O")
        _history.push_back(dest);
    else
    {
        if (action == 'x')
        {
            if (obj != 'P')
                _history.push_back(obj + src + "x" + dest);
            else
                _history.push_back(src + "x" + dest);
        }
        else
        {
            if (obj != 'P')
                _history.push_back(obj + src + "-" + dest);
            else
                _history.push_back(dest);
        }
    }
}

int chessBoard::playMove(t_move move, const bool free)
{
    _gameInfo._lastMove = move;
    if (isLegal() == false)
    {
        _gameInfo._moveFailed = true;
        return (FAIL);
    }
    else
    {
        _gameInfo._moveFailed = false;

        string  src = _gameInfo._lastMove.src;
        string  dest = _gameInfo._lastMove.dest;
        char    action = _gameInfo._lastMove.action;

        if (_gameInfo._lastMove.dest == "O-O"
            || _gameInfo._lastMove.dest == "O-O-O")
        {
            if (_gameInfo._color == "white")
                whiteCastles();
            if (_gameInfo._color == "black")
                blackCastles();
        }
        else
        {
            if ((_gameInfo._lastMove.action == 'x' || _gameInfo._lastMove.action == '-')
                && isThereSomething(dest) == false
                && _gameInfo._enPassant == true && _gameInfo._enPassantDest == dest)
                priseEnPassant(free);
            else
            {
                movePiece(src, dest, free);
                if (algebraParser::isChessPiece(dest.at(dest.length() - 1)) == true)
                    promotePiece(dest, dest[dest.length() - 1], free);
                
                if (_allocated == false)
                    return (ERR);
            }
        }
        enableDisableEnPassant();
        addToHistory();

        ++_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";
    }
    return (SUCCESS);
}
