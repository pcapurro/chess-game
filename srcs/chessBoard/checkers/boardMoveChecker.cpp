#include "../../../include/shellChess.hpp"

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
                && _board.at(getAtValue(source)).piece->getType() == 'P'
                && _board.at(getAtValue(source)).coord[0] == _lastMove.dest[0])
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

    if (_lastMove.obj == 'P')
    {
        if (_lastMove.dest[1] == (_lastMove.src[1] - 2) || _lastMove.dest[1] == (_lastMove.src[1] + 2))
        {
            atValue = getAtValue(_lastMove.dest);
            if (_enPassant == false || _enPassantDest != _lastMove.dest)
            {
                if (_board.at(atValue).piece == NULL)
                    return (false);
            }
        }
    }
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
