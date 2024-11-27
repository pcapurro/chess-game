#include "chessAi.hpp"

string	chessAi::getCounterCheckMate(const int value)
{
    string          testMove;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {
        testMove = legalMoves.at(i);
        if (count(testMove.begin(), testMove.end(), 'O') == 0)
            testMove = testMove.c_str() + 1;

        tryMove(legalMoves.at(i).c_str() + 1);

        if (value == 0 && isCheck() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        if (value == 1 && isDefeatNext() == false)
            newLegalMoves.push_back(legalMoves.at(i));

        undoMove(legalMoves.at(i).c_str() + 1);
    }

    cout << "new legal moves registered. sorting..." << endl;

    if (newLegalMoves.size() != 0)
        return (sortCounterCheckMoves(newLegalMoves));

    return ("");
}

string	chessAi::getCounterProtect(void)
{
    string  move;

    return (move);
}
