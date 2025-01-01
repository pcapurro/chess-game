#include "../chessBoard.hpp"

int chessBoard::checkPawnDest(void) const
{
    string  src = _gameInfo._lastMove.src;
    string  dest = _gameInfo._lastMove.dest;
    int     atValue;

    atValue = getAtValue(dest);

    if ((_board.at(atValue).coord[1] == '8' || _board.at(atValue).coord[1] == '1')
        && (dest.length() != 3 || algebraParser::isChessPiece(dest[2]) == false
        || dest[2] == 'K'))
        return (FAIL);

    if (_board.at(atValue).coord[0] != src[0])
    {
        if (_board.at(atValue).coord[0] - 1 != src[0]
            && _board.at(atValue).coord[0] + 1 != src[0])
            return (FAIL);

        if (_board.at(atValue).piece == nullptr)
        {
            if ((_gameInfo._enPassant == false || _gameInfo._enPassantDest != dest))
                return (FAIL);
        }
        else
        {
            if (_gameInfo._color == "white" && src[1] != dest[1] - 1)
                return (FAIL);
            if (_gameInfo._color == "black" && src[1] != dest[1] + 1)
                return (FAIL);
        }
    }

    if (_board.at(atValue).coord[0] == src[0])
    {
        if (isThereSomething(dest) == true)
            return (FAIL);

        if (_gameInfo._color == "white" 
            && dest[1] - src[1] != 2
            && dest[1] - src[1] != 1)
            return (FAIL);

        if (_gameInfo._color == "black" 
            && src[1] - dest[1] != 2
            && src[1] - dest[1] != 1)
            return (FAIL);

        if (_gameInfo._color == "white" 
            && dest[1] - src[1] == 2
            && src[1] != '2')
            return (FAIL);

        if (_gameInfo._color == "black" 
            && src[1] - dest[1] == 2
            && src[1] != '7')
            return (FAIL);

        string  newDest = dest;
        if (_board.at(atValue).coord[1] == dest[1] + 2)
        {
            newDest[1] = newDest[1] + 1;
            if (isThereSomething(newDest) == true)
                return (FAIL);
        }
        if (_board.at(atValue).coord[1] == dest[1] - 2)
        {
            newDest[1] = newDest[1] - 1;
            if (isThereSomething(newDest) == true)
                return (FAIL);
        }
    }

    return (SUCCESS);
}

int chessBoard::checkPawnSource(void)
{
    int     atValue;
    string  source;

    string  *src = &_gameInfo._lastMove.src;
    string  *dest = &_gameInfo._lastMove.dest;

    atValue = getAtValue(*dest);
    if (_board.at(atValue).piece != nullptr)
        return (FAIL);
    for (size_t i = 0; i != src->length(); i++)
    {
        source = source + src->at(i);
        if (source.length() == 2)
        {
            if (_board.at(getAtValue(source)).piece != nullptr
                && _board.at(getAtValue(source)).piece->getType() == 'P')
            {
                if (source[1] == (*dest)[1] - 2 && _board.at(getAtValue(source)).piece->getMoves() != 0)
                    return (FAIL);
                if (source[1] == (*dest)[1] + 2 && _board.at(getAtValue(source)).piece->getMoves() != 0)
                    return (FAIL);
                *src = source;
                return (SUCCESS);
            }
            else
                source.clear();
        }
    }
    return (FAIL);
}

int chessBoard::checkNormalSource(void)
{
    vector<string>  boardCoords;
    string          source;

    string          *src = &_gameInfo._lastMove.src;
    string          *dest = &_gameInfo._lastMove.dest;
    
    boardCoords = getPiecesCoords();
    source = *src;
    src->clear();
    for (int i = 0; i != 64; i++)
    {
        if (source.find(_board.at(i).coord) != string::npos && _board.at(i).piece != nullptr)
        {
            if (_board.at(i).piece->getColor() == _gameInfo._color && _board.at(i).piece->getType() == _gameInfo._lastMove.obj)
            {
                if (_board.at(i).piece->isOnMyWay(*dest, boardCoords) == true)
                    *src = *src + _board.at(i).coord;
            }
        }
    }

    if (src->length() != 2)
        return (FAIL);
    return (SUCCESS);
}

int chessBoard::checkNormalDest(void) const
{
    char            obj = _gameInfo._lastMove.obj;
    string          src = _gameInfo._lastMove.src;
    string          dest = _gameInfo._lastMove.dest;
    vector<string>  boardCoords = getPiecesCoords();

    if (obj == 'Q')
    {
        Queen   queen("white", src);

        if (queen.isOnMyWay(dest, boardCoords) == false)
            return (FAIL);
    }
    if (obj == 'K')
    {
        King   king("white", src);

        if (king.isOnMyWay(dest, boardCoords) == false)
            return (FAIL);
    }
    if (obj == 'B')
    {
        Bishop   bishop("white", src);

        if (bishop.isOnMyWay(dest, boardCoords) == false)
            return (FAIL);
    }
    if (obj == 'N')
    {
        Knight   knight("white", src);

        if (knight.isOnMyWay(dest, boardCoords) == false)
            return (FAIL);
    }
    if (obj == 'R')
    {
        Rook   rook("white", src);

        if (rook.isOnMyWay(dest, boardCoords) == false)
            return (FAIL);
    }
    return (SUCCESS);
}

bool    chessBoard::isThereValidSource(void)
{
    if (_gameInfo._lastMove.obj == 'P')
    {
        if (checkPawnSource() == FAIL)
            return (false);
    }
    else if (checkNormalSource() == FAIL)
        return (false);
    return (true);
}

bool    chessBoard::isValidEnPassant(void) const
{
    if (_gameInfo._lastMove.obj != 'P' || _gameInfo._enPassant == false 
        || _gameInfo._enPassantDest != _gameInfo._lastMove.dest)
        return (false);

    string  color, otherColor;
    string  dest;

    dest = _gameInfo._enPassantDest;
    dest[1] = _gameInfo._lastMove.src[1];
    
    color = _board.at(getAtValue(_gameInfo._lastMove.src)).piece->getColor();
    otherColor = _board.at(getAtValue(dest)).piece->getColor();

    if (color == otherColor)
        return (false);

    return (true);
}

bool    chessBoard::isItValidSource(void) const
{
    int     atValue;

    atValue = getAtValue(_gameInfo._lastMove.src);
    if (_board.at(atValue).piece == nullptr
        || _board.at(atValue).piece->getType() != _gameInfo._lastMove.obj)
        return (false);
    return (true);
}

bool    chessBoard::isLegal(const string move)
{
    char    *obj;
    string  *src;
    string  *dest;

    if (move != "")
        loadMove(move);

    obj = &_gameInfo._lastMove.obj;
    src = &_gameInfo._lastMove.src;
    dest = &_gameInfo._lastMove.dest;

    if (*dest == "O-O-O" || *dest == "O-O")
    {
        if (isCastlingPossible(*dest) == false || isCheck() == true)
            return (false);
    }
    else
    {
        if (_gameInfo._lastMove.action == 'x' && isThereSomething(*dest) == false)
        {
            if (isValidEnPassant() == false)
                return (false);
        }

        if (src->length() != 2)
        {
            if (isThereValidSource() == false)
                return (false);
        }
        else if (isItValidSource() == false)
            return (false);

        if (*obj == 'P')
        {
            if (checkPawnDest() == FAIL)
                return (false);
        }
        else
            if (checkNormalDest() == FAIL)
                return (false);

        if (isThereAlly() == true || isRightSide() == false
            || (*obj == 'K' && isTheDestinationSafe() == false))
            return (false);

        if (isCheck() == false && doesItResolveCheck(*src + *dest) == false)
            return (false);

        if (isCheck() == true 
            && doesItResolveCheck(*src + *dest) == false)
            return (false);
    }
    return (true);
}
