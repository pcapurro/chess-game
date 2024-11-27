#include "chessAi.hpp"

stack<chessPiece *> chessAi::orderMaterialsByValue(stack<chessPiece *> materials)
{
    stack<cP *>     stack;
    vector<cP *>    vMaterials;

    while (materials.size() != 0)
        vMaterials.push_back(materials.top()), materials.pop();

    for (int i = 0; i != 5; i++)
    {
        for (int k = 0; k != vMaterials.size(); k++)
        {
            if (i == 0 && vMaterials.at(k)->getType() == 'K')
                stack.push(vMaterials.at(k));
            if (i == 1 && vMaterials.at(k)->getType() == 'Q')
                stack.push(vMaterials.at(k));
            if (i == 2 && vMaterials.at(k)->getType() == 'R')
                stack.push(vMaterials.at(k));
            if (i == 3 && (vMaterials.at(k)->getType() == 'B' || vMaterials.at(k)->getType() == 'N'))
                stack.push(vMaterials.at(k));
            if (i == 4 && vMaterials.at(k)->getType() == 'P')
                stack.push(vMaterials.at(k));
        }
    }
    return (stack);
}

stack<cP *>    chessAi::getEnemyTargets(void)
{
    stack<cP *>  targets;

    switchPlayers();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isProtected(_board.at(i).coord) == false && isAttacked(_board.at(i).coord) == true)
            targets.push(_board.at(i).piece);
    }
    unSwitchPlayers();

    return (targets);
}

stack<cP *> chessAi::getWatchers(const string coord)
{
    vector<chessPiece *>    vMaterials;
    stack<chessPiece *>     materials;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getColor() == _gameInfo._color && _board.at(i).coord != coord
                && _board.at(i).piece->isVisible() == true)
            {
                if (_board.at(i).piece->isOnMyWay(coord, getPiecesCoords(), 1, _gameInfo._enPassantDest) == true)
                {
                    vMaterials.push_back(_board.at(i).piece);
                    _board.at(i).piece->setVisibility();
                    i = 0;
                }
            }
        }
    }

    for (int i = 0; i != vMaterials.size(); i++)
        vMaterials.at(i)->setVisibility(), materials.push(vMaterials.at(i));

    return (materials);
}

string  chessAi::sortCounterMoves(vector<string> kingAttackMoves, vector<string> kingRunAwayMoves, \
                                    vector<string> shieldMoves, vector<string> othersAttackMoves)
{
    if (othersAttackMoves.size() == 0 && kingAttackMoves.size() != 0)
        return (kingAttackMoves.at(rand() % kingAttackMoves.size()));
    else
    {
        if (othersAttackMoves.size() != 0)
            return (kingAttackMoves.at(rand() % kingAttackMoves.size()));
        else
        {
            if (shieldMoves.size() != 0)
                return (shieldMoves.at(rand() % shieldMoves.size()));
            else
                return (kingRunAwayMoves.at(rand() % kingRunAwayMoves.size()));
        }
    }

    return ("");
}

string  chessAi::getCounterMateCheckMoves(vector<string> legalMoves)
{
    vector<string>  kingAttackMoves;
    vector<string>  othersAttackMoves;
    vector<string>  shieldMoves;
    vector<string>  kingRunAwayMoves;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        string src = string(1, legalMoves.at(i)[0]) + legalMoves.at(i)[1];
        string dest = legalMoves.at(i).c_str() + legalMoves.at(i).length() - 3;

        if (algebraParser::isChessPiece(dest[dest.length() - 1]) == true)
            dest.erase(dest.length() - 1);
        else
            dest = dest.c_str() + 1;
        
        if (_board.at(getAtValue(dest)).piece != NULL
            && legalMoves.at(i)[0] != 'K' && _board.at(getAtValue(dest)).piece->isOnMyWay(src) == false)
            othersAttackMoves.push_back(legalMoves.at(i));
        else
        {
            if (_board.at(getAtValue(dest)).piece != NULL
                && legalMoves.at(i)[0] == 'K')
                kingAttackMoves.push_back(legalMoves.at(i));
            else
            {
                if (legalMoves.at(i)[0] == 'K')
                    kingRunAwayMoves.push_back(legalMoves.at(i));
                else
                    shieldMoves.push_back(legalMoves.at(i));
            }
        }
    }

    return (sortCounterMoves(kingAttackMoves, kingRunAwayMoves, shieldMoves, othersAttackMoves));
}

int     chessAi::getAttackedNumber(void)
{
    int nb = 0;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            nb++;
    }
    return (nb);
}

int chessAi::getMaterialValue(const char type)
{
    if (type == 'P')
        return (1);
    if (type == 'N' || type == 'B')
        return (3);
    if (type == 'R')
        return (5);
    if (type == 'Q')
        return (9);
    return (0);
}
