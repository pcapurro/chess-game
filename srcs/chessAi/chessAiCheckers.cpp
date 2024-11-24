#include "chessAi.hpp"

bool    chessAi::isEndGame(void)
{
    return (false);
}

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

bool    chessAi::isProtected(const string coord)
{
    int                     attackerMaterialsEarned = 0;
    int                     defenderMaterialsEearned = 0;
    stack<chessPiece *>     attackers;
    stack<chessPiece *>     defenders;

    attackers = getAttackers(coord);
    if (attackers.size() == 0)
        return (true);

    defenders = getDefenders(coord);
    if (defenders.size() == 0)
        return (false);

    attackers = orderMaterialsByValue(attackers);

    defenders = orderMaterialsByValue(defenders);
    defenders.push(_board.at(getAtValue(coord)).piece);

    while (attackers.size() != 0 && defenders.size() != 0)
    {
        attackerMaterialsEarned += getMaterialValue(defenders.top()->getType()), defenders.pop();
        if (defenders.size() == 0)
            break ;
        defenderMaterialsEearned += getMaterialValue(attackers.top()->getType()), attackers.pop();
        if (attackerMaterialsEarned > defenderMaterialsEearned)
            break ;
    }

    if (attackerMaterialsEarned > defenderMaterialsEearned)
        return (false);

    return (true);
}

bool    chessAi::isSomethingNotProtected(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            switchPlayers();
            if (isProtected(_board.at(i).coord) == false)
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
        switchPlayers();

        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            targets += getMaterialValue(_board.at(i).piece->getType());
        
        unSwitchPlayers();

        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            attacked += getMaterialValue(_board.at(i).piece->getType());
    }

    if (targets >= attacked)
        return (false);

    return (true);
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
            if (_board.at(i).piece->getType() == 'P' && _board.at(i).piece->isOnMyWay(coord, boardCoords, 1, _gameInfo._enPassantDest) == true)
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
