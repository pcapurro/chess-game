#include "chessAi.hpp"

string	chessAi::getCheckMateInOneMove(void)
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

string	chessAi::getCheckMateInTwoMove(void)
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
        if (checkMateInOne() == true && (count(move.begin(), move.end(), 'O') != 0
            || isProtected(string(1, move[2]) + move[3]) == true))
        {
			undoMove(move);
			return (legalMoves.at(i));
		}
        undoMove(move);
    }

	move.clear();

    return (move);
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
			if (isSomethingAttacked() == true && isProtected(dest) == true)
				{ undoMove(testMove); return (legalMoves.at(i)); }
			undoMove(testMove);
		}
	}

	return ("");
}

string	chessAi::getBestAttack(stack<cP *> targets)
{
	string			move;
	chessPiece 		*attacker;
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
		attacker = orderMaterialsByValue(attackers).top();
		move = string(1, attacker->getType()) + attacker->getCoord() + target->getCoord();

		if ((move[0] == 'P' && move[4] == '8' && _gameInfo._color == "white")
			|| (move[0] == 'P' && move[4] == '1' && _gameInfo._color == "black"))
			move = move + 'Q';

		return (move);
	}

	return (move);
}

string	chessAi::getPromotion(void)
{
	string			move;
	vector<string>	legalMoves;
	vector<string>	pawns;

	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		if (legalMoves.at(i)[0] == 'P')
		{
			move = legalMoves.at(i).c_str() + 1;

			tryMove(move);
			if (isProtected(string(1, move[2]) + move[3]) == true)
				pawns.push_back(legalMoves.at(i));
			undoMove(move);
		}
	}

	for (int i = 0; i != pawns.size(); i++)
	{
		if (pawns.at(i).size() == 6 && pawns.at(i)[5] == 'Q')
			move = pawns.at(i);
	}

	move.clear();

	if (move == "")
	{
		srand(time(nullptr));

		if (pawns.size() == 1)
			move = pawns.at(0);
		if (pawns.size() > 1)
			move = (pawns.at(rand() % pawns.size()));
	}

	return (move);
}

string	chessAi::getCounterStrike(void)
{
	string		move;
    stack<cP *>	targets;

	targets = getTargets();

    if (targets.size() == 0)
	{
		if (_checkMateInTwo == true)
			move = getCheckMateInTwoMove();
		else
		{
			if (_gameInfo._turn > 21)
				move = getPromotion();

			if (move == "")
				move = getThreat();
		}
	}
    else
		move = getBestAttack(targets);

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
