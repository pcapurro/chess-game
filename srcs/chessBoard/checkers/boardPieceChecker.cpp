#include "../chessBoard.hpp"

bool    chessBoard::isCastlingPossible(void)
{
    int atValue;

    if (_gameInfo._color == "white")
    {
        if (_gameInfo._lastMove.dest == "O-O")
        {
            if (_gameInfo._whiteShortCastle == false)
                return (false);

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

            if (doesItResolveCheck("e1g1") == false
                || doesItResolveCheck("e1f1") == false)
                return (false);
        }
        if (_gameInfo._lastMove.dest == "O-O-O")
        {
            if (_gameInfo._whiteLongCastle == false)
                return (false);

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

            if (doesItResolveCheck("e1d1") == false
                || doesItResolveCheck("e1c1") == false)
                return (false);
        }
    }
    if (_gameInfo._color == "black")
    {
        if (_gameInfo._lastMove.dest == "O-O")
        {
            if (_gameInfo._blackShortCastle == false)
                return (false);

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

            if (doesItResolveCheck("e8f8") == false
                || doesItResolveCheck("e8g8") == false)
                return (false);
        }
        if (_gameInfo._lastMove.dest == "O-O-O")
        {
            if (_gameInfo._blackLongCastle == false)
                return (false);

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

            if (doesItResolveCheck("e8d8") == false
                || doesItResolveCheck("e8c8") == false)
                return (false);
        }
    }
    return (true);
}

bool    chessBoard::isTheDestinationSafe(void) const
{
    vector<string>  coords;

    coords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            if (_board.at(i).piece->isOnMyWay(_gameInfo._lastMove.dest, coords, 1, _gameInfo._enPassantDest) == true)
                return (false);
        }
    }
    return (true);
}

bool    chessBoard::isRightSide(void) const
{
    int     atValue;

    atValue = getAtValue(_gameInfo._lastMove.src);
    if (_board.at(atValue).piece == NULL
        || _board.at(atValue).piece->getColor() == _gameInfo._color)
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

bool    chessBoard::isThereAlly(void) const
{
    int     atValue;

    atValue = getAtValue(_gameInfo._lastMove.dest);
    if (_board.at(atValue).piece != NULL && _board.at(atValue).piece->getColor() == _gameInfo._color)
        return (true);
    return (false);
}
