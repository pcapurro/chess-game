#include "chessAi.hpp"

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

bool    chessAi::isSafe(const string coord)
{
    if (isProtected(coord) == true || isFree(coord) == true)
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

bool    chessAi::isEndGame(void)
{
    int whiteMaterials = 0;
    int blackMaterials = 0;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getType() != 'K')
        {
            if (_board.at(i).piece->getColor() == "white")
                whiteMaterials += getMaterialValue(_board.at(i).piece->getType());

            if (_board.at(i).piece->getColor() == "black")
                blackMaterials += getMaterialValue(_board.at(i).piece->getType());
        }
    }

    if (whiteMaterials < 21 || blackMaterials < 21)
        return (true);

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

bool    chessAi::checkMateInOne(void)
{
    string          move;
    string          target;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (move[0] != 'O')
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
