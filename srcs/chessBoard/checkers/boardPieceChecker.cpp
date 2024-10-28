#include "../chessBoard.hpp"

bool    chessBoard::isCastlingPossible(void)
{
    int atValue;

    if (_color == "white")
    {
        if (_whiteCastle == false)
            return (false);

        if (_lastMove.dest == "O-O")
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

            if (doesItResolveCheck("e1g1") == false
                || doesItResolveCheck("e1f1") == false)
                return (false);
        }
        if (_lastMove.dest == "O-O-O")
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

            if (doesItResolveCheck("e1d1") == false
                || doesItResolveCheck("e1c1") == false)
                return (false);
        }
    }
    if (_color == "black")
    {
        if (_blackCastle == false)
            return (false);

        cout << "ok" << endl;

        if (_lastMove.dest == "O-O")
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

            cout << "ok1" << endl;

            if (doesItResolveCheck("e8f8") == false
                || doesItResolveCheck("e8g8") == false)
                return (false);
        }
        if (_lastMove.dest == "O-O-O")
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
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _color)
        {
            if (_board.at(i).piece->isOnMyWay(_lastMove.dest, coords, 1) == true)
                return (false);
        }
    }
    return (true);
}

bool    chessBoard::isRightSide(void) const
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

bool    chessBoard::isThereAlly(void) const
{
    int     atValue;

    atValue = getAtValue(_lastMove.dest);
    if (_board.at(atValue).piece != NULL && _board.at(atValue).piece->getColor() == _color)
        return (true);
    return (false);
}
