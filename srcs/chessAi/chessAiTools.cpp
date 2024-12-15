#include "chessAi.hpp"

stack<chessPiece *> chessAi::orderByValue(stack<chessPiece *> materials)
{
    stack<cP *>     stack;
    vector<cP *>    vMaterials;

    while (materials.size() != 0)
        vMaterials.push_back(materials.top()), materials.pop();

    for (int i = 0; i != 5; i++)
    {
        for (int k = 0; k != vMaterials.size(); k++)
        {
            if (i == 4 && vMaterials.at(k)->getType() == 'K')
                stack.push(vMaterials.at(k));
            if (i == 3 && vMaterials.at(k)->getType() == 'Q')
                stack.push(vMaterials.at(k));
            if (i == 2 && vMaterials.at(k)->getType() == 'R')
                stack.push(vMaterials.at(k));
            if (i == 1 && (vMaterials.at(k)->getType() == 'B' || vMaterials.at(k)->getType() == 'N'))
                stack.push(vMaterials.at(k));
            if (i == 0 && vMaterials.at(k)->getType() == 'P')
                stack.push(vMaterials.at(k));
        }
    }
    return (stack);
}

string  chessAi::getEnPassantTarget(void)
{
    string  target;

    target = _gameInfo._enPassantDest;
    if (_gameInfo._turn % 2 == 0)
        target[1] = target[1] + 1;
    if (_gameInfo._turn % 2 == 1)
        target[1] = target[1] - 1;
    
    return (target);
}

int chessAi::getWatchersNumber(const string coord)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getColor() == _gameInfo._color && _board.at(i).coord != coord
                && _board.at(i).piece->isVisible() == true)
            {
                if (_board.at(i).piece->isOnMyWay(coord, getPiecesCoords(), 1, _gameInfo._enPassantDest) == true)
                    return (1);
            }
        }
    }
    return (0);
}

stack<cP *> chessAi::getWatchers(const string coord)
{
    vector<string>          baordCoords;
    stack<cP *>             material;
    stack<cP *>             material3;
    vector<stack<cP *>>     materials;

    while (getWatchersNumber(coord) != 0)
    {
        baordCoords = getPiecesCoords();

        for (int i = 0; i != 64; i++)
        {
            if (_board.at(i).piece != NULL)
            {
                if (_board.at(i).piece->getColor() == _gameInfo._color && _board.at(i).coord != coord
                    && _board.at(i).piece->isVisible() == true)
                {
                    if (_board.at(i).piece->isOnMyWay(coord, baordCoords, 1, _gameInfo._enPassantDest) == true)
                    {
                        material.push(_board.at(i).piece);
                        _board.at(i).piece->setVisibility();
                    }
                }
            }
        }
        material = orderByValue(material);
        materials.push_back(material);
        while (material.size() != 0)
            material.pop();
    }

    if (materials.size() != 0)
    {
        for (int i = materials.size() - 1; i != -1; i--)
        {
            while (materials.at(i).size() != 0)
            {
                material3.push(materials.at(i).top());
                material3.top()->setVisibility();
                materials.at(i).pop();
            }
        }
    }

    return (material3);
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
    if (type == 'K')
        return (200);

    return (0);
}
