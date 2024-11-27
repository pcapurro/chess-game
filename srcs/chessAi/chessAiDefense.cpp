#include "chessAi.hpp"

string  chessAi::getCounterCheck(void)
{
    string          move;
    string          testMove;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {
        testMove = legalMoves.at(i);
        if (count(testMove.begin(), testMove.end(), 'O') == 0)
            testMove = testMove.c_str() + 1;

        tryMove(testMove);
        if (isCheck() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        undoMove(testMove);
    }

    return (getCounterMateCheckMoves(newLegalMoves));
}

string	chessAi::getCounterCheckMate(void)
{
    string          move;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {   
        tryMove(legalMoves.at(i).c_str() + 1);
        if (isDefeatNext() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        undoMove(legalMoves.at(i).c_str() + 1);
    }

    if (newLegalMoves.size() == 0)
        return (move);

    return (getCounterMateCheckMoves(newLegalMoves));
}

string	chessAi::getCounterProtect(void)
{
    string  move;

    return (move);
}
