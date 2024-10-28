#include "../chessBoard.hpp"

int chessBoard::checkPawnDest(void) const
{
    int atValue;

    atValue = getAtValue(_lastMove.dest);

    if ((_board.at(atValue).coord[1] == '8' || _board.at(atValue).coord[1] == '1')
        && (_lastMove.dest.length() != 3 || algebraParser::isChessPiece(_lastMove.dest[2]) == false
        || _lastMove.dest[2] == 'K'))
        return (FAIL);

    if (_board.at(atValue).coord[0] != _lastMove.src[0])
    {
        if (_board.at(atValue).piece == NULL)
        {
            if ((_enPassant == false || _enPassantDest != _lastMove.dest))
                return (FAIL);
        }
        else
        {
            if (_color == "white" && _lastMove.src[1] != _lastMove.dest[1] - 1)
                return (FAIL);
            if (_color == "black" && _lastMove.src[1] != _lastMove.dest[1] + 1)
                return (FAIL);
        }
    }

    if (_board.at(atValue).coord[0] == _lastMove.src[0])
    {
        if (isThereSomething(_lastMove.dest) == true)
            return (FAIL);

        if (_color == "white" 
            && _lastMove.dest[1] - _lastMove.src[1] != 2
            && _lastMove.dest[1] - _lastMove.src[1] != 1)
            return (FAIL);

        if (_color == "black" 
            && _lastMove.src[1] - _lastMove.dest[1] != 2
            && _lastMove.src[1] - _lastMove.dest[1] != 1)
            return (FAIL);

        string  newDest = _lastMove.dest;
        if (_board.at(atValue).coord[1] == _lastMove.dest[1] + 2)
        {
            newDest[1] = newDest[1] + 1;
            if (isThereSomething(newDest) == true)
                return (FAIL);
        }
        if (_board.at(atValue).coord[1] == _lastMove.dest[1] - 2)
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

    atValue = getAtValue(_lastMove.dest);
    if (_board.at(atValue).piece != NULL)
        return (FAIL);
    for (int i = 0; i != _lastMove.src.length(); i++)
    {
        source = source + _lastMove.src.at(i);
        if (source.length() == 2)
        {
            if (_board.at(getAtValue(source)).piece != NULL
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
    return (FAIL);
}

int chessBoard::checkNormalSource(void)
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

int chessBoard::checkNormalDest(void) const
{
    if (_lastMove.obj == 'Q')
    {
        Queen   queen("white", _lastMove.src);

        if (queen.isOnMyWay(_lastMove.dest) == false)
            return (FAIL);
    }
    if (_lastMove.obj == 'K')
    {
        King   king("white", _lastMove.src);

        if (king.isOnMyWay(_lastMove.dest) == false)
            return (FAIL);
    }
    if (_lastMove.obj == 'B')
    {
        Bishop   bishop("white", _lastMove.src);

        if (bishop.isOnMyWay(_lastMove.dest) == false)
            return (FAIL);
    }
    if (_lastMove.obj == 'N')
    {
        Knight   knight("white", _lastMove.src);

        if (knight.isOnMyWay(_lastMove.dest) == false)
            return (FAIL);
    }
    if (_lastMove.obj == 'R')
    {
        Rook   rook("white", _lastMove.src);

        if (rook.isOnMyWay(_lastMove.dest) == false)
            return (FAIL);
    }
    return (SUCCESS);
}

bool    chessBoard::isThereValidSource(void)
{
    if (_lastMove.obj == 'P')
    {
        if (checkPawnSource() == FAIL)
            return (false);
    }
    else if (checkNormalSource() == FAIL)
        return (false);
    return (true);
}

bool    chessBoard::isItValidSource(void) const
{
    int     atValue;

    atValue = getAtValue(_lastMove.src);
    if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getType() != _lastMove.obj)
        return (false);
    return (true);
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
            if (isThereValidSource() == false)
                return (false);
        }
        else if (isItValidSource() == false)
            return (false);

        if (_lastMove.obj == 'P')
        {
            if (checkPawnDest() == FAIL)
                return (false);
        }
        else
            if (checkNormalDest() == FAIL)
                return (false);

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
