#include "chessAi.hpp"

bool    chessAi::equalValues(const string move)
{
    int     oneValue;
    int     twoValue;
    string  coordOne;
    string  coordTwo;

    coordOne = string(1, move[0]) + move[1];
    coordTwo = string(1, move[2]) + move[3];

    oneValue = getMaterialValue(_board.at(getAtValue(coordOne)).piece->getType());

    if (_board.at(getAtValue(coordTwo)).piece != NULL)
        twoValue = getMaterialValue(_board.at(getAtValue(coordTwo)).piece->getType());
    else
        return (true);

    if (oneValue == twoValue)
        return (true);

    return (false);
}

bool    chessAi::isDeveloped(void)
{
    char    nb;

    if (_gameInfo._color == "white")
        nb = '1';
    if (_gameInfo._color == "white")
        nb = '8';

    if (_gameInfo._color == "white")
    {
        if (_board.at(getAtValue("b" + nb)).piece != NULL && _board.at(getAtValue("b" + nb)).piece->getMoves() == 0)
            return (false);
        if (_board.at(getAtValue("c" + nb)).piece != NULL && _board.at(getAtValue("c" + nb)).piece->getMoves() == 0)
            return (false);

        if (_board.at(getAtValue("f" + nb)).piece != NULL && _board.at(getAtValue("f" + nb)).piece->getMoves() == 0)
            return (false);
        if (_board.at(getAtValue("g" + nb)).piece != NULL && _board.at(getAtValue("g" + nb)).piece->getMoves() == 0)
            return (false);

        if (_board.at(getAtValue("e" + nb)).piece != NULL && _board.at(getAtValue("e" + nb)).piece->getMoves() == 0)
        {
            if (_board.at(getAtValue("a" + nb)).piece != NULL && _board.at(getAtValue("a" + nb)).piece->getMoves() == 0)
                return (false);
            if (_board.at(getAtValue("h" + nb)).piece != NULL && _board.at(getAtValue("h" + nb)).piece->getMoves() == 0)
                return (false);
        }
    }

    return (true);
}

bool    chessAi::isExchangeWorth(void)
{
    int materials = 0;
    int enemyMaterials = 0;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
            materials = materials + getMaterialValue(_board.at(i).piece->getType());

        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
            enemyMaterials = enemyMaterials + getMaterialValue(_board.at(i).piece->getType());
    }

    if (materials > enemyMaterials)
        return (true);

    return (false);
}

bool    chessAi::isMoveWorth(const string move)
{
    int     earned = 0;
    int     attacked = getAttackedValues();
    string  dest;
    
    if (move != "O-O" && move != "O-O-O")
    {
        dest = string(1, move[2]) + move[3];

        if (_board.at(getAtValue(dest)).piece != NULL)
            earned = earned + getMaterialValue(_board.at(getAtValue(dest)).piece->getType());
    }

    tryMove(move);

    if (getAttackedValues() - earned < attacked)
        { undoMove(move); return (true); }
    
    if (getAttackedValues() - earned == attacked)
    {
        if (move == "O-O" || move == "O-O-O"
            || isProtected(dest) == true || isFree(dest) == true)
        {
            undoMove(move);
            return (true);
        }
    }

    undoMove(move);

    return (false);
}

bool    chessAi::isFree(const string coord)
{
    stack<cP *> attackers;

    switchPlayers();
    attackers = getWatchers(coord);
    unSwitchPlayers();

    if (attackers.size() == 0)
        return (true);

    return (false);
}

bool    chessAi::isProtected(const string coord)
{
    int         attMaterials, defMaterials;
    stack<cP *> defenders, attackers;

    defenders = getWatchers(coord);
    if (defenders.size() == 0)
        return (false);

    switchPlayers();
    attackers = getWatchers(coord);
    unSwitchPlayers();
    if (attackers.size() == 0)
        return (true);

    if (coord == _gameInfo._enPassantDest)
        defenders.push(_board.at(getAtValue(getEnPassantTarget())).piece);
    else
        defenders.push(_board.at(getAtValue(coord)).piece);

    attMaterials = 0;
    defMaterials = 0;

    while (attackers.size() != 0 && defenders.size() != 0)
    {
        attMaterials +=  getMaterialValue(defenders.top()->getType()), defenders.pop();
        if (defenders.size() == 0)
            break ;
        defMaterials += getMaterialValue(attackers.top()->getType()), attackers.pop();
        if (attMaterials > defMaterials)
            break ;
    }

    if (attMaterials > defMaterials)
        return (false);

    return (true);
}

bool    chessAi::isSomethingAttacked(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            switchPlayers();
            if (isAttacked(_board.at(i).coord) == true)
            {
                unSwitchPlayers();
                return (true);
            }
            unSwitchPlayers();
        }
    }
    return (false);
}

bool    chessAi::isDefenseWorth(void)
{
    int targets = 0;
    int attacked = 0;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            switchPlayers();
            if (isAttacked(_board.at(i).coord) == true)
                targets += getMaterialValue(_board.at(i).piece->getType());
            unSwitchPlayers();
        }

        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            attacked += getMaterialValue(_board.at(i).piece->getType());
    }

    if (targets >= attacked)
        return (false);

    return (true);
}

bool    chessAi::willBeCheck(void)
{
    string          move;
    vector<string>  legalMoves;

    switchPlayers();

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        if (isMoveWorth(move) == true)
        {
            unSwitchPlayers();

            tryMove(move);
            if (isCheck() == true)
                { undoMove(move); return (true); }
            undoMove(move);

            switchPlayers();
        }
    }

    unSwitchPlayers();

    return (false);
}

bool    chessAi::isAllyAttacked(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
        {
            if (isAttacked(_board.at(i).coord) == true)
                return (true);
        }
    }
    return (false);
}

bool    chessAi::isAttacked(const string coord)
{
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            if (_board.at(i).piece->isOnMyWay(coord, boardCoords, 1, _gameInfo._enPassantDest) == true)
            {
                if (isProtected(coord) == false)
                    return (true);
            }
        }
    }

    if (getEnPassantTarget() == coord)
    {
        if (isAttacked(_gameInfo._enPassantDest) == true)
            return (true);
    }

    return (false);
}

bool    chessAi::isAttackedByPawn(const string coord)
{
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            if (_board.at(i).piece->getType() == 'P'
                && _board.at(i).piece->isOnMyWay(coord, boardCoords, 1, _gameInfo._enPassantDest) == true)
                return (true);
        }
    }
    return (false);
}

bool    chessAi::checkMateInTwo(void)
{
    string          move;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        tryMove(move);

        if (checkMateInOne() == true && (count(move.begin(), move.end(), 'O') != 0
            || isProtected(string(1, move[2]) + move[3]) == true))
        {
            undoMove(move);
            return (true);
        }

        undoMove(move);
    }
    return (false);
}

bool    chessAi::checkMateInOne(void)
{
    string          move;
    string          target;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        tryMove(move);
        switchPlayers();
        if (isCheckMate(-1) == true)
        {
            undoMove(move);
            unSwitchPlayers();
            return (true);
        }
        unSwitchPlayers();
        undoMove(move);
    }

    return (false);
}

bool    chessAi::isDefeatNext(void)
{
    switchPlayers();
    if (checkMateInOne() == true)
        { unSwitchPlayers(); return (true); }
    unSwitchPlayers();
    
    return (false);
}
