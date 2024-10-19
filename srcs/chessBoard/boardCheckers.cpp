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

bool    chessBoard::doesItResolveCheck(void) const
{
    return (true);
}

bool    chessBoard::isCheck(void) const
{
    string          kingPos;
    string          kingColor;
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getType() == 'K')
            kingPos = _board.at(i).coord, kingColor = _board.at(i).piece->getColor();
    }
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != kingColor)
        {
            if (_board.at(i).piece->isOnMyWay(kingPos, boardCoords) == true)
            {
                cout << "piece at " << _board.at(i).coord << " (" << _board.at(i).piece->getType() << ") can reach " << kingPos << endl;
                return (true);
            }
        }
    }
    return (false);
}

bool    chessBoard::isCheckMate(void) const
{
    return (false);
}

bool    chessBoard::isCastlingPossible(void) const
{
    int atValue;

    if (_color == "white")
    {
        if (_whiteCastle != true)
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
        if (_blackCastle != true)
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
    cout << "dest is safe" << endl;
    return (true);
}

bool    chessBoard::isRightSide(void)
{
    int     atValue;

    atValue = getAtValue(_lastMove.src);
    if (_board.at(atValue).piece == NULL
        || _board.at(atValue).piece->getColor() == _color)
        return (true);
    cout << "not right side" << endl;
    return (false);
}

bool    chessBoard::isThereSomething(const string dest) const
{
    int     atValue;

    atValue = getAtValue(dest);
    if (_board.at(atValue).piece != NULL)
        return (true);
    cout << "there is nothing there" << endl;
    return (false);
}

bool    chessBoard::isThereAttacker(void)
{
    int     atValue;

    atValue = getAtValue(_lastMove.src);
    if (_board.at(atValue).piece != NULL && _board.at(atValue).piece->getType() == _lastMove.obj)
        return (true);
    cout << "there is no attacker" << endl;
    return (false);
}

bool    chessBoard::isThereAlly(void)
{
    int     atValue;

    atValue = getAtValue(_lastMove.dest);
    if (_board.at(atValue).piece != NULL && _board.at(atValue).piece->getColor() == _color)
    {
        cout << "there is ally on dest" << endl;
        return (true);
    }
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
                cout << "checking if piece at " << _board.at(i).coord << " can reach " << _lastMove.dest << endl;
                if (_board.at(i).piece->isOnMyWay(_lastMove.dest, boardCoords) == true)
                {
                    cout << _board.at(i).coord << " is valid " << endl;
                    _lastMove.src = _lastMove.src + _board.at(i).coord;
                }
            }
        }
    }

    if (_lastMove.src.length() != 2)
    {
        cout << "no src or multiple srcs" << endl;
        cout << "srcs > " << _lastMove.src << endl;
        return (FAIL);
    }
    return (SUCCESS);
}

bool    chessBoard::isThereValidDestintation(void)
{
    if (_lastMove.obj == 'P')
    {
        if (checkPawnDestintation() == FAIL)
        {
            cout << "no valid dest (p)" << endl;
            return (false);
        }
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
                {
                    cout << "no valid dest" << endl;
                    return (false);
                }
            }
        }
    }
    return (true);
}

bool    chessBoard::isLegal(void)
{
    if (_lastMove.dest == "O-O-O" || _lastMove.dest == "O-O")
    {
        if (isCastlingPossible() != true)
        {
            cout << "no castling possible" << endl;
            return (false);
        }
    }
    else
    {
        if (_lastMove.action == 'x' && isThereSomething(_lastMove.dest) != true)
        {
            if (_lastMove.obj != 'P' || _enPassant == false)
                return (false);
        }

        if (_lastMove.src.length() != 2)
        {
            if (isThereValidDestintation() != true)
                return (false);
        }
        else
        {
            if (isItValidDestination() != true
                || isThereAttacker() != true)
                return (false);
        }
        if (isThereAlly() == true || isRightSide() == false
            || (_lastMove.obj == 'K' && isTheDestinationSafe() == false))
            return (false);

        if (isCheck() == true && doesItResolveCheck() == false)
            return (false);
    }
    return (true);
}
