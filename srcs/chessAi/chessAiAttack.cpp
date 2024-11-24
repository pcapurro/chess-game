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

string	chessAi::getThreat(void)
{
	string			dest, testMove;
	vector<string>	legalMoves;

	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		if (count(legalMoves.at(i).begin(), legalMoves.at(i).end(), 'O') == 0)
		{
			dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];
			testMove = legalMoves.at(i).c_str() + 1;

			tryMove(testMove);
			if (isSomethingNotProtected() == true && isProtected(dest) == true)
				{ undoMove(testMove); return (legalMoves.at(i)); }
			undoMove(testMove);
		}
	}

	return ("");
}

string	chessAi::getBestAttacker(stack<cP *> targets)
{
	string			move;
	chessPiece		*target;
	vector<string>	legalMoves;
	stack<cP *>    	attackers;

	legalMoves = getLegalMoves();

	targets = orderMaterialsByValue(targets);
	while (targets.size() != 0)
		target = targets.top(), targets.pop();

	for (int i = 0; i != legalMoves.size(); i++)
	{
		string  src = string(1, legalMoves.at(i)[1]) + legalMoves.at(i)[2];
		string  dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];

		if (dest == target->getCoord())
			attackers.push(_board.at(getAtValue(src)).piece);
	}

	if (attackers.size() != 0)
	{
		chessPiece *attacker = orderMaterialsByValue(attackers).top();
		move = string(1, attacker->getType()) + attacker->getCoord() + target->getCoord();
		return (move);
	}

	return (move);
}

string	chessAi::getCounterStrike(void)
{
	string		move;
    stack<cP *>	targets;

	targets = getTargets();

    if (targets.size() == 0)
		move = getThreat();
    else
		move = getBestAttacker(targets);

	if (move == "")
	{
		switchPlayers();
		if (isCheck() == false)
		{
			if (isCastlingPossible("O-O") == true)
				move = preventCastling("O-O");
			if (isCastlingPossible("O-O-O") == true)
				move = preventCastling("O-O-O");
		}
		unSwitchPlayers();
	}

    return (move);
}
