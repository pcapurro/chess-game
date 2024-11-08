#include "../chessBoard.hpp"

bool    chessBoard::isCheck(void)
{
    string          kingPos;
    string          kingColor;
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getType() == 'K' && _board.at(i).piece->getColor() == _color)
            kingPos = _board.at(i).coord, kingColor = _board.at(i).piece->getColor();
    }
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != kingColor)
        {
            if (_board.at(i).piece->isOnMyWay(kingPos, boardCoords) == true)
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
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _color
            && _board.at(i).piece->getType() != 'K')
        {
            for (int k = 0; k != 64; k++)
            {
                if (_board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords, 0, _enPassantDest) == true
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
        if (_board.at(i).piece != NULL && _board.at(i).piece->getType() == 'K' && _board.at(i).piece->getColor() == _color)
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
            { _draw = true; return (true); }
    }
    return (false);
}

void    chessBoard::tryMove(const string srcdest)
{
    int         atValueSrc;
    int         atValueDest;
    
    string      src;
    string      dest;

    src = string(1, srcdest[0]) + string(1, srcdest[1]);
    dest = srcdest.c_str() + 2;

    atValueSrc = getAtValue(src);
    atValueDest = getAtValue(dest);

    if (_board.at(atValueDest).piece != NULL)
    {
        _savedPiece = _board.at(atValueDest).piece;
        _board.at(atValueDest).piece = NULL;
    }
    else
        _savedPiece = NULL;

    _board.at(atValueDest).piece = _board.at(atValueSrc).piece;
    _board.at(atValueDest).piece->updatePos(_board.at(atValueDest).coord);
    _board.at(atValueSrc).piece = NULL;
}

void    chessBoard::undoMove(const string srcdest)
{
    int         atValueSrc;
    int         atValueDest;
    
    string      src;
    string      dest;

    src = string(1, srcdest[0]) + string(1, srcdest[1]);
    dest = srcdest.c_str() + 2;

    atValueSrc = getAtValue(src);
    atValueDest = getAtValue(dest);

    _board.at(atValueSrc).piece = _board.at(atValueDest).piece;
    _board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);
    _board.at(atValueDest).piece = _savedPiece;
}

bool    chessBoard::doesItResolveCheck(const string srcdest)
{
    tryMove(srcdest);

    if (isCheck() == true)
        { undoMove(srcdest); return (false); }
    undoMove(srcdest);

    return (true);
}

vector<string>  chessBoard::getPossibleMoves(const string coord, const bool reverse) const
{
    int             atValue;
    vector<string>  moves;
    vector<string>  boardCoords;
    string          actualCoords;
    string          color;

    atValue = getAtValue(coord);
    boardCoords = getPiecesCoords();
    actualCoords = "a0";

    if (reverse == false)
        color = _color;
    else
        _color == "white" ? color = "black" : color = "white";

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            actualCoords[1] = actualCoords[1] + 1;
            if (_board.at(atValue).piece->isOnMyWay(actualCoords, boardCoords, 0, _enPassantDest) == true)
            {
                if ((_board.at(getAtValue(actualCoords)).piece == NULL 
                    || _board.at(getAtValue(actualCoords)).piece->getColor() != color))
                    moves.push_back(coord + actualCoords);
            }
        }
        actualCoords[0] = actualCoords[0] + 1;
        actualCoords[1] = '0';
    }

    return (moves);
}

bool    chessBoard::isCheckMateNextMove(const bool reverse)
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL && _board.at(getAtValue(coord)).piece->getColor() != _color)
            {
                cout << "possibles moves for " << coord << endl;
                vector<string>  moves = getPossibleMoves(coord, reverse);
                for (int k = 0; k != moves.size(); k++)
                    cout << moves.at(k) << " ; ";
                cout << endl;
            }
        }
    }

    return (false);
}

bool    chessBoard::isCheckMate(void)
{
    if (isCheck() == true)
    {
        vector<string>      sources;

        for (int i = 0; i != 64; i++)
        {
            if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _color)
            {
                sources = getPossibleMoves(_board.at(i).coord);
                for (size_t k = 0; k != sources.size(); k++)
                {
                    if (doesItResolveCheck(sources.at(k)) == true)
                        return (false);
                }
            }
            sources.clear();
        }
        _checkmate = true;
        return (true);
    }
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
