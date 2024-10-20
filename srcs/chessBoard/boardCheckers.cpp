#include "../../include/header.hpp"

void    chessBoard::printIllegal(void) const
{
    // cout << "\033[2A" << ERASE_LINE;
    // cerr << YELLOW << "Illegal move. " << COLOR_E;
}

bool    chessBoard::fail(void) const
{
    return (_moveFailed);
}

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
                if (_board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords) == true)
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

    if (_boardCount.whiteRook == 0 && _boardCount.blackRook == 0
        && _boardCount.whiteKnight == 0 && _boardCount.blackKnight == 0
        && _boardCount.whiteBishop == 0 && _boardCount.blackBishop == 0
        && _boardCount.whiteQueen == 0 && _boardCount.blackQueen == 0)
    {
        if (canAnyAllyPieceMove() == false)
        {
            changeColor();
            if (canAnyAllyPieceMove() == false)
            {
                changeColor();
                return (true);
            }
            changeColor();
        }
    }

    cout << "checkmate possible" << endl;

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
        {
            cout << "draw" << endl;
            return (true);
        }
    }
    return (false);
}

bool    chessBoard::doesItResolveCheck(const string srcdest)
{
    int         atValueSrc;
    int         atValueDest;
    
    string      src;
    string      dest;
    chessPiece  *savedPiece;

    src = string(1, srcdest[0]) + string(1, srcdest[1]);
    dest = srcdest.c_str() + 2;

    atValueSrc = getAtValue(src);
    atValueDest = getAtValue(dest);
    if (_board.at(atValueDest).piece != NULL)
    {
        savedPiece = _board.at(atValueDest).piece;
        _board.at(atValueDest).piece = NULL;
    }
    else
        savedPiece = NULL;

    _board.at(atValueDest).piece = _board.at(atValueSrc).piece;
    _board.at(atValueDest).piece->updatePos(_board.at(atValueDest).coord);
    _board.at(atValueSrc).piece = NULL;

    if (isCheck() == true)
    {
        _board.at(atValueSrc).piece = _board.at(atValueDest).piece;
        _board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);
        _board.at(atValueDest).piece = savedPiece;
        return (false);
    }
    _board.at(atValueSrc).piece = _board.at(atValueDest).piece;
    _board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);
    _board.at(atValueDest).piece = savedPiece;
    
    return (true);
}

vector<string>  chessBoard::getPossibleMoves(const string coord)
{
    int             atValue;
    vector<string>  moves;
    vector<string>  boardCoords;
    string          actualCoords;

    atValue = getAtValue(coord);
    boardCoords = getPiecesCoords();
    actualCoords = "a0";
    for (int i = 0; i != 64; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            actualCoords[1] = actualCoords[1] + 1;
            if (_board.at(atValue).piece->isOnMyWay(actualCoords, boardCoords) == true
                && (_board.at(getAtValue(actualCoords)).piece == NULL 
                || _board.at(getAtValue(actualCoords)).piece->getColor() != _color))
                moves.push_back(coord + actualCoords);
        }
        actualCoords[0] = actualCoords[0] + 1;
        actualCoords[1] = '0';
    }
    return (moves);
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
                for (int k = 0; k != sources.size(); k++)
                {
                    if (doesItResolveCheck(sources.at(k)) == true)
                    {
                        cout << "not checkmate if " << sources.at(k) << endl;
                        return (false);
                    }
                }
            }
            sources.clear();
        }
        cout << "checkmate" << endl;
        return (true);
    }
    return (false);
}

bool    chessBoard::isCastlingPossible(void) const
{
    int atValue;

    if (_color == "white")
    {
        if (_whiteCastle == false)
            return (false);

        if (_lastMove.move == "O-O")
        {
            atValue = getAtValue("h1");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("g1");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("f1");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
        if (_lastMove.move == "O-O-O")
        {
            atValue = getAtValue("a1");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("b1");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("c1");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
    }
    if (_color == "Black")
    {
        if (_blackCastle == false)
            return (false);

        if (_lastMove.move == "O-O")
        {
            atValue = getAtValue("h8");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("g8");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("f8");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
        if (_lastMove.move == "O-O-O")
        {
            atValue = getAtValue("a8");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("b8");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("c8");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
    }
    return (true);
}

bool    chessBoard::isTheDestinationSafe(void)
{
    vector<string>  coords;

    coords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _color)
        {
            if (_board.at(i).piece->isOnMyWay(_lastMove.dest, coords) == true)
                return (false);
        }
    }
    return (true);
}

bool    chessBoard::isRightSide(void)
{
    int     atValue;

    atValue = getAtValue(_lastMove.src);
    if (_board.at(atValue).piece == NULL
        || _board.at(atValue).piece->getColor() == _color)
        return (true);
    return (false);
}

bool    chessBoard::isThereSomething(const string dest) const
{
    int     atValue;

    atValue = getAtValue(dest);
    if (_board.at(atValue).piece != NULL)
        return (true);
    return (false);
}

bool    chessBoard::isThereAttacker(void)
{
    int     atValue;

    atValue = getAtValue(_lastMove.src);
    if (_board.at(atValue).piece != NULL && _board.at(atValue).piece->getType() == _lastMove.obj)
        return (true);
    return (false);
}

bool    chessBoard::isThereAlly(void)
{
    int     atValue;

    atValue = getAtValue(_lastMove.dest);
    if (_board.at(atValue).piece != NULL && _board.at(atValue).piece->getColor() == _color)
        return (true);
    return (false);
}

int chessBoard::checkPawnDestintation(void)
{
    int     atValue;
    string  source;

    atValue = getAtValue(_lastMove.dest);
    if (_board.at(atValue).piece == NULL)
    {
        for (int i = 0; i != _lastMove.src.length(); i++)
        {
            source = source + _lastMove.src.at(i);
            if (source.length() == 2)
            {
                if (source[0] == _lastMove.dest[0]
                    && _board.at(getAtValue(source)).piece != NULL
                    && _board.at(getAtValue(source)).piece->getType() == 'P')
                {
                    if (source[1] == _lastMove.dest[1] - 2 && _board.at(getAtValue(source)).piece->getMoves() != 0)
                        return (FAIL);
                    if (source[1] == _lastMove.dest[1] + 2 && _board.at(getAtValue(source)).piece->getMoves() != 0)
                        return (FAIL);
                    _lastMove.src = source;
                    return (SUCCESS);
                }
                else
                    source.clear();
            }
        }
    }
    return (FAIL);
}

int chessBoard::checkSource(void)
{
    vector<string>  boardCoords;
    string          source;
    
    boardCoords = getPiecesCoords();
    source = _lastMove.src;
    _lastMove.src.clear();
    for (int i = 0; i != 64; i++)
    {
        if (source.find(_board.at(i).coord) != string::npos && _board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getColor() == _color && _board.at(i).piece->getType() == _lastMove.obj)
            {
                int type = _lastMove.obj;
                if (_board.at(i).piece->isOnMyWay(_lastMove.dest, boardCoords) == true)
                    _lastMove.src = _lastMove.src + _board.at(i).coord;
            }
        }
    }

    if (_lastMove.src.length() != 2)
        return (FAIL);
    return (SUCCESS);
}

bool    chessBoard::isThereValidDestintation(void)
{
    if (_lastMove.obj == 'P')
    {
        if (checkPawnDestintation() == FAIL)
            return (false);
    }
    else if (checkSource() == FAIL)
    {
        return (false);
    }
    return (true);
}

bool    chessBoard::isItValidDestination(void)
{
    if (_lastMove.obj == 'P')
    {
        if (_lastMove.dest[1] == (_lastMove.src[1] - 2) || _lastMove.dest[1] == (_lastMove.src[1] + 2))
        {
            int atValue = getAtValue(_lastMove.dest);
            if (_enPassant == false || _enPassantDest != _lastMove.dest)
            {
                if (_board.at(atValue).piece == NULL)
                    return (false);
            }
        }
    }
    return (true);
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

bool    chessBoard::isLegal(void)
{
    if (_lastMove.dest == "O-O-O" || _lastMove.dest == "O-O")
    {
        if (isCastlingPossible() == false || isCheck() == true)
            return (false);
    }
    else
    {
        if (_lastMove.action == 'x' && isThereSomething(_lastMove.dest) == false)
        {
            if (_lastMove.obj != 'P' || _enPassant == false || _enPassantDest != _lastMove.dest)
                return (false);
        }

        if (_lastMove.src.length() != 2)
        {
            if (isThereValidDestintation() == false)
                return (false);
        }
        else
        {
            if (isItValidDestination() == false
                || isThereAttacker() == false)
                return (false);
        }
        if (isThereAlly() == true || isRightSide() == false
            || (_lastMove.obj == 'K' && isTheDestinationSafe() == false))
            return (false);

        if (isCheck() == false && doesItResolveCheck(_lastMove.src + _lastMove.dest) == false)
            return (false);

        if (isCheck() == true 
            && doesItResolveCheck(_lastMove.src + _lastMove.dest) == false)
            return (false);
    }
    return (true);
}
