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

        tryMove(testMove);

        if (value == 0 && isCheck() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        if (value == 1 && isDefeatNext() == false)
            newLegalMoves.push_back(legalMoves.at(i));

        undoMove(testMove);
    }

    if (newLegalMoves.size() != 0)
        return (sortCounterCheckMoves(newLegalMoves));

    return ("");
}

vector<string>  chessAi::getProtectAnswers(chessPiece *target)
{
    string          testMove;
    vector<string>  legalMoves;
    vector<string>  answers;

    legalMoves = getLegalMoves();

    cout << target->getType() << " (" << target->getCoord() << ") selected." << endl;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        testMove = legalMoves.at(i);
        if (count(testMove.begin(), testMove.end(), 'O') == 0)
            testMove = testMove.c_str() + 1;

        tryMove(testMove);
        if (isProtected(target->getCoord()) == true)
            answers.push_back(legalMoves.at(i)), cout << legalMoves.at(i) << " can save it." << endl;
        undoMove(testMove);
    }

    cout << answers.size() << " can save " << target->getType() << " (" << target->getCoord() << ")" << endl;

    return (answers);
}

string  chessAi::sortProtectAnswers(vector<string> answers, chessPiece *target)
{
    string          move;
    vector<string>  attackMoves;
    vector<string>  othersAttackMoves;
    vector<string>  runAwayMoves;
    vector<string>  shieldMoves;

    for (int i = 0; i != answers.size(); i++)
    {
        move = answers.at(i);
        if (move.c_str() + 1 == target->getCoord())
            runAwayMoves.push_back(move);
        else
        {
            ;
        }
    }
}

string	chessAi::getCounterProtect(void)
{
    string          move;
    vector<string>  answers;
    stack<cP *>     targets;
    chessPiece      *target;

    targets = getTargets();
    targets = orderByValueRev(targets);

    cout << targets.size() << " allied attacked" << endl;

    while (targets.size() != 0)
    {
        target = targets.top();
        targets.pop();

        answers = getProtectAnswers(target);
        if (answers.size() != 0)
            move = sortProtectAnswers(answers, target);

        if (move != "")
            break ;
    }

    return (move);
}
