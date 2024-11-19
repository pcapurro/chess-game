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
