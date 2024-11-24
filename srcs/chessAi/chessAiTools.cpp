#include "chessAi.hpp"

stack<chessPiece *> chessAi::orderMaterialsByValue(vector<chessPiece *> materials)
{
    int                 value;
    stack<chessPiece *> stack;

    for (int i = 0; i != 5; i++)
    {
        for (int k = 0; k != materials.size(); k++)
        {
            if (i == 0 && materials.at(k)->getType() == 'K')
                stack.push(materials.at(k));
            if (i == 1 && materials.at(k)->getType() == 'Q')
                stack.push(materials.at(k));
            if (i == 2 && materials.at(k)->getType() == 'R')
                stack.push(materials.at(k));
            if (i == 3 && (materials.at(k)->getType() == 'B' || materials.at(k)->getType() == 'N'))
                stack.push(materials.at(k));
            if (i == 4 && materials.at(k)->getType() == 'P')
                stack.push(materials.at(k));
        }
    }
    return (stack);
}

vector<cP *>    chessAi::getTargets(void)
{
    vector<cP *>  targets;

    switchPlayers();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isProtected(_board.at(i).coord) == false)
            targets.push_back(_board.at(i).piece);
    }
    unSwitchPlayers();

    return (targets);
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
