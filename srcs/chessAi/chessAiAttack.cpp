#include "chessAi.hpp"

string	chessAi::getCheckMateMove(void)
{
    string          move;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        tryMove(move);
        switchPlayers();
        if (isCheckMate(-1) == true)
        {
            undoMove(move);
            unSwitchPlayers();
            return (legalMoves.at(i));
        }
        unSwitchPlayers();
        undoMove(move);
    }
    return ("");
}

string  chessAi::preventCastling(const string castle)
{
    vector<string>  legalMoves;
    string          move;

    unSwitchPlayers();
    legalMoves = getLegalMoves();
    switchPlayers();

    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        tryMove(move);
        if (isCastlingPossible(castle) == false)
        {
            unSwitchPlayers();
            if (isProtected(string(1, move[2]) + move[3]) == true)
                { switchPlayers(); undoMove(move); return (legalMoves.at(i)); }
            switchPlayers();
        }
        undoMove(move);
    }
    
    return ("");
}

string	chessAi::getCounterStrike(void)
{
	string                  move;
    string                  testMove;
    vector<string>          legalMoves;
    vector<chessPiece *>    targets;
    stack<chessPiece *>     orderedTargets;
    vector<chessPiece *>    attackers;
    stack<chessPiece *>     orderedAttackers;
    chessPiece              *target;
    chessPiece              *attacker;

    if (_victoryNextNext == true)
        return (_attackMove);

    switchPlayers();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isProtected(_board.at(i).coord) == false)
            targets.push_back(_board.at(i).piece);
    }
    unSwitchPlayers();

    legalMoves = getLegalMoves();

    if (targets.size() == 0)
    {
        for (int i = 0; i != legalMoves.size(); i++)
        {
            if (count(legalMoves.at(i).begin(), legalMoves.at(i).end(), 'O') == 0)
            {
                string  dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];

                testMove = legalMoves.at(i);
                if (count(testMove.begin(), testMove.end(), 'O') == 0)
                    testMove = testMove.c_str() + 1;

                tryMove(testMove);
                if (isSomethingNotProtected() == true && isProtected(dest) == true)
                {
                    undoMove(testMove);
                    return (legalMoves.at(i));
                }
                undoMove(testMove);
            }
        }
    }
    else
    {
        orderedTargets = orderMaterialsByValue(targets);
        while (orderedTargets.size() != 0)
            target = orderedTargets.top(), orderedTargets.pop();

        for (int i = 0; i != legalMoves.size(); i++)
        {
            string  src = string(1, legalMoves.at(i)[1]) + legalMoves.at(i)[2];
            string  dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];

            if (dest == target->getCoord())
                attackers.push_back(_board.at(getAtValue(src)).piece);
        }
    }

    if (attackers.size() != 0)
    {
        orderedAttackers = orderMaterialsByValue(attackers);
        attacker = orderedAttackers.top();
        return (string(1, attacker->getType()) + attacker->getCoord() + target->getCoord());
    }

    switchPlayers();
    if (isCheck() == false)
    {
        if (isCastlingPossible("O-O") == true)
            move = preventCastling("O-O");
        if (isCastlingPossible("O-O-O") == true)
            move = preventCastling("O-O-O");
    }
    unSwitchPlayers();

    return (move);
}
