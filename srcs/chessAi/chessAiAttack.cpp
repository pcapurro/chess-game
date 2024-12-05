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
			|| isProtected(string(1, move[2]) + move[3]) == true || isFree(string(1, move[2]) + move[3]) == true))
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
            if (isProtected(string(1, move[2]) + move[3]) == true
				|| isFree(string(1, move[2]) + move[3]) == true)
            {
				switchPlayers();
				undoMove(move);
				return (legalMoves.at(i));
			}
            switchPlayers();
        }
        undoMove(move);
    }
    
    return ("");
}

string	chessAi::getThreat(void)
{
	int				attackedAllies;
	string			move, dest, testMove;
	vector<string>	legalMoves;

	attackedAllies = getAttackedValues();
	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		if (count(legalMoves.at(i).begin(), legalMoves.at(i).end(), 'O') == 0)
		{
			dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];
			testMove = legalMoves.at(i).c_str() + 1;

			tryMove(testMove);
			if (isSomethingAttacked() == true && (isProtected(dest) == true || isFree(dest) == true)
				&& getAttackedValues() <= attackedAllies)
			{
				undoMove(testMove);
				move = legalMoves.at(i);

				srand(time(nullptr));
				if (rand() % 2 != 0)
					move.clear();

				break ;
			}
			undoMove(testMove);
		}
	}

	return (move);
}

string	chessAi::getExchange(void)
{
	string			move, dest;
	vector<string>	legalMoves;

	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		if (count(legalMoves.at(i).begin(), legalMoves.at(i).end(), 'O') == 0)
		{
			dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];
			if (_board.at(getAtValue(dest)).piece != NULL)
			{
				if (legalMoves.at(i)[0] == _board.at(getAtValue(dest)).piece->getType())
				{
					move = legalMoves.at(i);
					if (rand() % 4 != 0)
						move.clear();
					break ;
				}
			}
		}
	}
	return (move);
}

string	chessAi::getBestAttack(stack<cP *> targets)
{
	string			move;
	chessPiece 		*attacker, *target;
	vector<string>	legalMoves, attacks;
	stack<cP *>    	attackers;

	legalMoves = getLegalMoves();
	targets = orderByValueRev(targets);

	while (targets.size() != 0)
	{
		target = targets.top(), targets.pop();

		for (int i = 0; i != legalMoves.size(); i++)
		{
        	if (count(legalMoves.at(i).begin(), legalMoves.at(i).end(), 'O') == 0)
			{
				move = legalMoves.at(i);
				attacker = _board.at(getAtValue(string(1, move[1]) + move[2])).piece;

				if (isMoveWorth(move.c_str() + 1) == true)
				{
					tryMove(move.c_str() + 1);
					if (_board.at(getAtValue(target->getCoord())).piece == NULL
						|| _board.at(getAtValue(target->getCoord())).piece->getColor() == _gameInfo._color)
						attackers.push(attacker), attacks.push_back(move);
					undoMove(move.c_str() + 1);
				}
			}
		}

		if (attackers.size() != 0)
		{
			attacker = orderByValue(attackers).top();

			for (int i = 0; i != legalMoves.size(); i++)
			{
				move = legalMoves.at(i);
				if (find(attacks.begin(), attacks.end(), move) != attacks.end()
					&& string(1, move[1]) + move[2] == attacker->getCoord())
					break ;
			}

			if (move[0] == 'P' && (move[4] == '8' || move[4] == '1'))
				move = move + 'Q';

			return (move);
		}
	}

	move.clear();

	return (move);
}

string	chessAi::getPromotionNow(void)
{
	string			move;
	vector<string>	legalMoves;

	legalMoves = getLegalMoves();

	for (int i = 0; i != legalMoves.size(); i++)
	{
		if (legalMoves.at(i)[0] == 'P' && legalMoves.at(i).size() == 6)
		{
			move = legalMoves.at(i);
			if (isMoveWorth(move.c_str() + 1) == true)
				{ move[5] = 'Q'; return (move); }
		}
	}

	move.clear();

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

			if (isMoveWorth(move) == true)
				pawns.push_back(legalMoves.at(i));
		}
	}

	move.clear();

	for (int i = 0; i != pawns.size(); i++)
	{
		if (pawns.at(i).size() == 6 && pawns.at(i)[5] == 'Q')
			move = pawns.at(i);
	}

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

	switchPlayers();
	targets = getTargets();
	unSwitchPlayers();

    if (targets.size() == 0)
	{
		if (_checkMateInTwo == true)
			move = getCheckMateInTwoMove();
		else
		{
			if (move == "")
				move = getPromotionNow(), cout << "getting promotion now" << endl;

			srand(time(nullptr));

			if (move == "" && (rand() % 4 == 2 || isExchangeWorth() == true))
				move = getExchange(), cout << "getting exchange now" << endl;
		}
	}
    else
		move = getBestAttack(targets);

	srand(time(nullptr));

	if (move == "" && rand() % 4 == 0)
	{
		cout << "getting preventCastling now" << endl;
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

	if (move == "" && _gameInfo._turn > 21
		&& isDeveloped() == true)
		move = getPromotion(), cout << "getting getPromotion now" << endl;

	if (move == "" && rand() % 3 == 1)
		move = getThreat(), cout << "getting getThreat now" << endl;

    return (move);
}
