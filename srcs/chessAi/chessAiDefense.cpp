#include "chessAi.hpp"

string  chessAi::getBestCounterMateCheck(vector<string> legalMoves)
{
    string          src;
    string          dest;
    string          move;

    vector<string>  attackMoves;
    vector<string>  shieldMoves;
    vector<string>  othersMoves;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        src = string(1, legalMoves.at(i)[0]) + legalMoves.at(i)[1];
        dest = legalMoves.at(i).c_str() + legalMoves.at(i).length() - 3;
        if (algebraParser::isChessPiece(dest[dest.length() - 1]) == true)
            dest.erase(dest.length() - 1);
        else
            dest = dest.c_str() + 1;
        
        if (_board.at(getAtValue(dest)).piece != NULL
            && _board.at(getAtValue(dest)).piece->isOnMyWay(src) == false
            && legalMoves.at(i)[0] != 'K')
            attackMoves.push_back(legalMoves.at(i));
        else
        {
            if (legalMoves.at(i)[0] == 'K')
                othersMoves.push_back(legalMoves.at(i));
            else
                shieldMoves.push_back(legalMoves.at(i));
        }
    }

    vector<string>  *moves;

    if (attackMoves.size() != 0)
        moves = &attackMoves;
    else
    {
        if (othersMoves.size() != 0)
            moves = &othersMoves;
        else
        {
            if (shieldMoves.size() != 0)
                moves = &shieldMoves;
        }
    }

    if (moves->size() == 1)
        move = moves->at(0);
    if (moves->size() > 1)
        move = moves->at(rand() % moves->size());

    return (move);
}

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

    move = getBestCounterMateCheck(newLegalMoves);

    return (move);
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
    else
        move = getBestCounterMateCheck(newLegalMoves);

    return (move);
}

string	chessAi::getCounterProtect(void)
{
    string  move;

    return (move);
}
