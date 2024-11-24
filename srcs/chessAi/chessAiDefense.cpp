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
	string                  move;
    vector<string>          legalMoves;
    vector<string>          moves;
    stack<chessPiece *>     orderedTargets;
    vector<chessPiece *>     targets;
    chessPiece              *target;
    chessPiece              *attackedOne;

    orderedTargets = orderMaterialsByValue(_attackedAlly);
    while (orderedTargets.size() != 0)
        attackedOne = orderedTargets.top(), orderedTargets.pop();

    legalMoves = getLegalMoves();

    string  testMove;
    int     attacked;
    bool    capture;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        testMove = legalMoves.at(i);
        if (count(testMove.begin(), testMove.end(), 'O') == 0)
            testMove = testMove.c_str() + 1;

        capture = false;
        attacked = getAttackedNumber();
        if (_board.at(getAtValue(string(1, testMove[2]) + testMove[3])).piece != NULL)
            capture = true;

        tryMove(testMove);
        if (isProtected(attackedOne->getCoord()) == true && isProtected(string(1, testMove[2]) + testMove[3]) == true)
            moves.push_back(legalMoves.at(i));
        if (capture == true && attacked <= getAttackedNumber())
            moves.push_back(legalMoves.at(i));
        undoMove(testMove);
    }

    vector<string>  runAway;
    vector<string>  protectNormal;
    vector<string>  protectAttack;
    vector<string>  protectWithPawn;
    vector<string>  protectExchange;
    string          src;
    string          dest;

    for (int i = 0; i != moves.size(); i++)
    {
        src = string(1, moves.at(i)[1]) + moves.at(i)[2];
        dest = string(1, moves.at(i)[3]) + moves.at(i)[4];
        if (src == attackedOne->getCoord() && _board.at(getAtValue(dest)).piece == NULL)
            runAway.push_back(moves.at(i));
        else
        {
            if (_board.at(getAtValue(dest)).piece != NULL)
            {
                if (src == attackedOne->getCoord() && attackedOne->getType() == _board.at(getAtValue(dest)).piece->getType())
                    protectExchange.push_back(moves.at(i));
                else
                {
                    int attacked = getAttackedNumber();

                    tryMove(moves.at(i).c_str() + 1);
                    if (getAttackedNumber() < attacked)
                        protectAttack.push_back(moves.at(i));
                    undoMove(moves.at(i).c_str() + 1);
                }
            }
            else
            {
                if (moves.at(i)[0] == 'P')
                    protectWithPawn.push_back(moves.at(i));
                else
                    protectNormal.push_back(moves.at(i));
            }
        }
    }

    if (moves.size() == runAway.size() && runAway.size() > 1
        && _gameInfo._turn < 21)
    {
        for (int i = 0; i != runAway.size() && runAway.size() > 1; i++)
        {
            if (runAway.at(i)[0] == 'N' || runAway.at(i)[0] == 'B')
            {
                if (_gameInfo._color == "white" && runAway.at(i)[4] == '1')
                    runAway.erase(runAway.begin() + i), i = 0;
                if (_gameInfo._color == "black" && runAway.at(i)[4] == '8')
                    runAway.erase(runAway.begin() + i), i = 0;
            }
        }
    }

    if (protectAttack.size() != 0)
    {
        while (orderedTargets.size() != 0)
            orderedTargets.pop();
        targets.clear();

        for (int i = 0; i != protectAttack.size(); i++)
        {
            string destCoords = string(1, protectAttack.at(i)[3]) + protectAttack.at(i)[4];
            targets.push_back(_board.at(getAtValue(destCoords)).piece);
        }

        orderedTargets = orderMaterialsByValue(targets);
        while (orderedTargets.size() != 0)
            target = orderedTargets.top(), orderedTargets.pop();
    }

    srand(time(nullptr));

    if (protectAttack.size() >= 1 || protectExchange.size() >= 1)
    {
        if (protectAttack.size() >= 1)
        {
            for (int i = 0; i != protectAttack.size(); i++)
            {
                string dest = string(1, protectAttack.at(i)[3]) + protectAttack.at(i)[4];
                if (dest == target->getCoord())
                    return (protectAttack.at(i));
            }
        }
        if ((protectExchange.size() >= 1 && protectExchange.size() == moves.size()) || rand() % 2 == 0)
            return (protectExchange.at(0));
    }
    else
    {
        if (isAttackedByPawn(attackedOne->getCoord()) == true
            && attackedOne->getType() != 'P')
        {
            if (runAway.size() == 1)
                move = runAway.at(0);
            if (runAway.size() > 1)
                move = runAway.at(rand() % runAway.size());
        }
        else
        {
            if (protectWithPawn.size() >= 1)
            {
                if (protectWithPawn.size() == 1)
                    move = protectWithPawn.at(0);
                else
                    move = protectWithPawn.at(rand() % protectWithPawn.size());
            }
            else
            {
                if (protectNormal.size() >= 1)
                {
                    if (protectNormal.size() == 1)
                        move = protectNormal.at(0);
                    else
                        move = protectNormal.at(rand() % protectNormal.size());
                }
                else if (runAway.size() >= 1)
                {
                    if (runAway.size() == 1)
                        move = runAway.at(0);
                    else
                        move = runAway.at(rand() % runAway.size());
                }
            }
        }
    }

    return (move);
}
