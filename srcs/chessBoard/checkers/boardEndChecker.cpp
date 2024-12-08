#include "../chessBoard.hpp"

bool    chessBoard::isCheck(void)
{
    string          kingPos;
    string          kingColor;
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getType() == 'K' && _board.at(i).piece->getColor() == _gameInfo._color)
            kingPos = _board.at(i).coord, kingColor = _board.at(i).piece->getColor();
    }
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != kingColor)
        {
            if (_board.at(i).piece->isOnMyWay(kingPos, boardCoords, 1) == true)
                return (true);
        }
    }
    return (false);
}

bool    chessBoard::canAnyAllyPieceMove(void)
{
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && _board.at(i).piece->getType() != 'K')
        {
            for (int k = 0; k != 64; k++)
            {
                if (_board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords, 0, _gameInfo._enPassantDest) == true
                    && doesItResolveCheck(_board.at(i).coord + _board.at(k).coord) == true)
                    return (true);
            }
        }
    }
    return (false);
}

bool    chessBoard::isCheckMateImpossible(void)
{
    countPiecesOnBoard();

    if (_boardCount.total == 2)
        return (true);

    if (_boardCount.whiteKing + _boardCount.blackKing
        + _boardCount.whiteKnight + _boardCount.blackKnight
        == 6 && 6 == _boardCount.total)
        return (true);

    if (_boardCount.whiteKing + _boardCount.blackKing
        + _boardCount.whiteKnight + _boardCount.blackKnight
        == 4 && 4 == _boardCount.total)
        return (true);

    if (_boardCount.whiteKing + _boardCount.blackKing
        + _boardCount.whiteKnight + _boardCount.blackKnight
        == 3 && 3 == _boardCount.total)
        return (true);

    if (_boardCount.whiteKing + _boardCount.blackKing
        + _boardCount.whiteBishop + _boardCount.blackBishop
        == 4 && 4 == _boardCount.total)
        return (true);

    if (_boardCount.whiteKing + _boardCount.blackKing
        + _boardCount.whiteBishop + _boardCount.blackBishop
        == 3 && 3 == _boardCount.total)
        return (true);

    if (_boardCount.whitePawn + _boardCount.blackPawn
        + _boardCount.whiteKing + _boardCount.blackKing
        == _boardCount.total)
    {
        if (canTheKingMove() == false && canAnyAllyPieceMove() == false)
            return (true);
    }

    return (false);
}

bool    chessBoard::canTheKingMove(void)
{
    int             kingPos;
    string          kingColor;
    vector<string>  boardCoords;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getType() == 'K' && _board.at(i).piece->getColor() == _gameInfo._color)
            kingPos = i, kingColor = _board.at(i).piece->getColor();
    }
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(kingPos).piece->isOnMyWay(_board.at(i).coord, boardCoords) == true)
        {
            boardCoords = getPiecesCoords();
            if ((_board.at(i).piece == NULL || _board.at(i).piece->getColor() != kingColor)
                && doesItResolveCheck(_board.at(kingPos).coord + _board.at(i).coord) == true)
                return (true);
        }
    }
    return (false);
}

bool    chessBoard::isDraw(void)
{
    if (isCheck() == false)
    {
        if (isCheckMateImpossible() == true || (canTheKingMove() == false && canAnyAllyPieceMove() == false))
            { _gameInfo._draw = true; return (true); }
    }
    return (false);
}

void    chessBoard::switchPlayers(void)
{
    ++_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";
}

void    chessBoard::unSwitchPlayers(void)
{
    --_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";
}

void    chessBoard::tryEnPassant(string srcdest)
{
    int         atValueSrc;
    int         atValueDestOne;
    int         atValueDestTwo;
    
    string      src;
    string      destOne;
    string      destTwo;

    src = string(1, srcdest[0]) + srcdest[1];
    destOne = string(1, srcdest[2]) + srcdest[3];
    destTwo = destOne, destTwo[1] = src[1];

    atValueSrc = getAtValue(src);
    atValueDestOne = getAtValue(destOne);
    atValueDestTwo = getAtValue(destTwo);

    _savedObjects.push(_board.at(atValueDestTwo).piece);
    _board.at(atValueDestTwo).piece = NULL;

    _board.at(atValueDestOne).piece = _board.at(atValueSrc).piece;
    _board.at(atValueDestOne).piece->updatePos(_board.at(atValueDestOne).coord);
    _board.at(atValueSrc).piece = NULL;

    _gameInfo._enPassant = false;
}

void    chessBoard::undoEnPassant(string srcdest)
{
    int         atValueSrc;
    int         atValueDestOne;
    int         atValueDestTwo;
    
    string      src;
    string      destOne;
    string      destTwo;

    src = string(1, srcdest[0]) + srcdest[1];
    destOne = string(1, srcdest[2]) + srcdest[3];
    destTwo = destOne, destTwo[1] = src[1];

    atValueSrc = getAtValue(src);
    atValueDestOne = getAtValue(destOne);
    atValueDestTwo = getAtValue(destTwo);

    _board.at(atValueSrc).piece = _board.at(atValueDestOne).piece;
    _board.at(atValueDestOne).piece = NULL;
    _board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);

    _board.at(atValueDestTwo).piece = _savedObjects.top();

    _savedObjects.pop();

    _gameInfo._enPassant = true;
}

void    chessBoard::tryMove(string srcdest)
{
    int         atValueSrc;
    int         atValueDest;
    
    string      src;
    string      dest;

    if (srcdest == "O-O" || srcdest == "O-O-O"
        || (string(1, srcdest[2]) + srcdest[3] == _gameInfo._enPassantDest
            && (getType(string(1, srcdest[0]) + srcdest[1]) == 'P' || getType(string(1, srcdest[2]) + srcdest[3]) == 'P')))
    {
        if (srcdest[0] == 'O')
        {
            vector<string>  castling;
        
            castling = getCastlingSrcsDests(srcdest);
            tryMove(castling.at(0));
            tryMove(castling.at(1));
        }
        else
            tryEnPassant(srcdest);
    }
    else
    {
        src = string(1, srcdest[0]) + string(1, srcdest[1]);
        dest = srcdest.c_str() + 2;

        atValueSrc = getAtValue(src);
        atValueDest = getAtValue(dest);

        if (_board.at(atValueSrc).piece->getType() == 'K')
        {
            if (_board.at(atValueSrc).piece->getColor() == "white"
                && _gameInfo._whiteCastle == true)
                _gameInfo._whiteCastleLost = srcdest, _gameInfo._whiteCastle = false;

            if (_board.at(atValueSrc).piece->getColor() == "black"
                && _gameInfo._blackCastle == true)
                _gameInfo._blackCastleLost = srcdest, _gameInfo._blackCastle = false;
        }

        if (_board.at(atValueDest).piece != NULL)
        {
            _savedObjects.push(_board.at(atValueDest).piece);
            _board.at(atValueDest).piece = NULL;
        }
        else
            _savedObjects.push(NULL);

        _board.at(atValueDest).piece = _board.at(atValueSrc).piece;
        _board.at(atValueDest).piece->updatePos(_board.at(atValueDest).coord);
        _board.at(atValueSrc).piece = NULL;
    }
}

void    chessBoard::undoMove(string srcdest)
{
    int         atValueSrc;
    int         atValueDest;
    
    string      src;
    string      dest;

    if (srcdest == "O-O" || srcdest == "O-O-O"
        || (string(1, srcdest[2]) + srcdest[3] == _gameInfo._enPassantDest
            && (getType(string(1, srcdest[0]) + srcdest[1]) == 'P' || getType(string(1, srcdest[2]) + srcdest[3]) == 'P')))
    {
        if (srcdest[0] == 'O')
        {
            vector<string>  castling;

            castling = getCastlingSrcsDests(srcdest);
            undoMove(castling.at(1));
            undoMove(castling.at(0));
        }
        else
            undoEnPassant(srcdest);
    }
    else
    {
        src = string(1, srcdest[0]) + string(1, srcdest[1]);
        dest = srcdest.c_str() + 2;

        atValueSrc = getAtValue(src);
        atValueDest = getAtValue(dest);

        if (_board.at(atValueDest).piece->getType() == 'K')
        {
            if (_board.at(atValueDest).piece->getColor() == "white"
                && _gameInfo._whiteCastleLost != "" && _gameInfo._whiteCastleLost == srcdest)
                _gameInfo._whiteCastleLost.clear(), _gameInfo._whiteCastle = true;

            if (_board.at(atValueDest).piece->getColor() == "black"
                && _gameInfo._blackCastleLost != "" && _gameInfo._blackCastleLost == srcdest)
                _gameInfo._blackCastleLost.clear(), _gameInfo._blackCastle = true;
        }

        _board.at(atValueSrc).piece = _board.at(atValueDest).piece;
        _board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);
        _board.at(atValueDest).piece = _savedObjects.top();

        _savedObjects.pop();
    }
}

bool    chessBoard::doesItResolveCheck(const string srcdest)
{
    tryMove(srcdest);

    if (isCheck() == true)
        { undoMove(srcdest); return (false); }
    undoMove(srcdest);

    return (true);
}

vector<string>  chessBoard::getPossibleTargets(const string coord) const
{
    int             atValue;
    string          coords;
    vector<string>  boardCoords;
    vector<string>  moves;

    atValue = getAtValue(coord);
    boardCoords = getPiecesCoords();

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(atValue).piece->isOnMyWay(coords, boardCoords, 0, _gameInfo._enPassantDest) == true)
            {
                if (_board.at(getAtValue(coords)).piece == NULL
                    || _board.at(getAtValue(coords)).piece->getColor() != _gameInfo._color)
                    moves.push_back(coord + coords);
            }
        }
    }

    return (moves);
}

bool    chessBoard::isCheckMate(const int value)
{
    if (isCheck() == true)
    {
        if (value == 0)
            _gameInfo._check = true;

        vector<string>      sources;

        for (int i = 0; i != 64; i++)
        {
            if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
            {
                sources = getPossibleTargets(_board.at(i).coord);
                for (size_t k = 0; k != sources.size(); k++)
                {
                    if (doesItResolveCheck(sources.at(k)) == true)
                        return (false);
                }
            }
            sources.clear();
        }
        if (value == 0)
            _gameInfo._checkmate = true;
        return (true);
    }
    else
        if (value == 0)
            _gameInfo._check = false;

    return (false);
}

bool    chessBoard::isGameOver(void)
{
    if (isAllocated() == false)
        return (true);
    if (isCheckMate() == true)
        return (true);
    if (isDraw() == true)
        return (true);
    return (false);
}
