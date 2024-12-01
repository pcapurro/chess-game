#include "chessAi.hpp"

vector<string>  chessAi::sortProtectAnswers(vector<string> answers)
{
    bool            value;
    string          dest;
    vector<string>  newAnswers;

    value = false;
    for (int i = 0; i != answers.size(); i++)
    {
        dest = string(1, answers.at(i)[3]) + answers.at(i)[4];

        if (_board.at(getAtValue(dest)).piece != NULL)
            { value = true; break ; }
    }

    if (value == true)
    {
        for (int i = 0; i != answers.size(); i++)
        {
            dest = string(1, answers.at(i)[3]) + answers.at(i)[4];

            if (_board.at(getAtValue(dest)).piece != NULL)
                newAnswers.push_back(answers.at(i));
        }
    }
    else
        newAnswers = answers;

    return (newAnswers);
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

        if (isMoveWorth(testMove) == true)
        {
            tryMove(testMove);
            if (isProtected(target->getCoord()) == true)
                answers.push_back(legalMoves.at(i)), cout << legalMoves.at(i) << " can save it." << endl;
            undoMove(testMove);
        }
    }

    cout << answers.size() << " can save " << target->getType() << " (" << target->getCoord() << ")" << endl;

    return (answers);
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
            move = answers.at(rand() % answers.size());

        if (move != "")
            break ;
    }

    return (move);
}
