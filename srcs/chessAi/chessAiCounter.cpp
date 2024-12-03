#include "chessAi.hpp"

vector<string>  chessAi::getKingAttacks(vector <string> legalMoves)
{
    vector<string>  kingAttacks;
    string          move, dest;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
        {
            dest = string(1, move[3]) + move[4];
            if (_board.at(getAtValue(dest)).piece != NULL && move[0] == 'K')
                kingAttacks.push_back(legalMoves.at(i));
        }
    }

    return (kingAttacks);
}

vector<string>  chessAi::getKingRunAwayMoves(vector <string> legalMoves)
{
    vector<string>  kingRunAwayMoves;
    string          dest;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        if (legalMoves.at(i) == "O-O" || legalMoves.at(i) == "O-O-O")
            kingRunAwayMoves.push_back(legalMoves.at(i));
        else
        {
            dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];
            if (legalMoves.at(i)[0] == 'K' && _board.at(getAtValue(dest)).piece == NULL)
                kingRunAwayMoves.push_back(legalMoves.at(i));
        }
    }

    return (kingRunAwayMoves);
}

vector<string>  chessAi::getOthersAttacks(vector <string> legalMoves)
{
    vector<string>  othersAttacks;
    string          move, src, dest;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);

        if (count(move.begin(), move.end(), 'O') == 0)
        {
            src = string(1, move[1]) + move[2];
            dest = string(1, move[3]) + move[4];

            if (_board.at(getAtValue(dest)).piece != NULL && move[0] != 'K')
            {
                tryMove(move.c_str() + 1);
                if (isProtected(string(1, move[3]) + move[4]) == true
                    || move[0] == _board.at(getAtValue(dest)).piece->getType())
                    othersAttacks.push_back(legalMoves.at(i));
                undoMove(move.c_str() + 1);
            }
        }
    }

    return (othersAttacks);
}

vector<string>  chessAi::getShieldMoves(vector <string> legalMoves)
{
	bool			value;
	string          move, dest;
    vector<string>  shieldMoves;

	value = false;
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
        {
            dest = string(1, move[3]) + move[4];

            if (_board.at(getAtValue(dest)).piece == NULL && move[0] != 'K')
            {
                tryMove(move.c_str() + 1);
                if (isProtected(string(1, move[3]) + move[4]) == true)
                {
                    shieldMoves.push_back(legalMoves.at(i));
                    if (move[0] == 'P')
                        value = true;
                }
                undoMove(move.c_str() + 1);
            }
        }
    }

	if (value == true)
	{
		for (int i = 0; i != shieldMoves.size(); i++)
		{
			if (shieldMoves.at(i)[0] != 'P')
				shieldMoves.erase(shieldMoves.begin() + i), i = 0;
		}
	}

    return (shieldMoves);
}

string  chessAi::sortCounterCheckMoves(vector<string> legalMoves)
{
    vector<string>  kingAttackMoves = getKingAttacks(legalMoves);
    vector<string>  othersAttackMoves = getOthersAttacks(legalMoves);

    if (othersAttackMoves.size() == 0 && kingAttackMoves.size() != 0)
        return (kingAttackMoves.at(rand() % kingAttackMoves.size()));
    else
    {
        if (othersAttackMoves.size() != 0)
            return (othersAttackMoves.at(rand() % othersAttackMoves.size()));
        else
        {
            vector<string>  kingRunAwayMoves = getKingRunAwayMoves(legalMoves);
            vector<string>  shieldMoves = getShieldMoves(legalMoves);

            if (shieldMoves.size() != 0)
            {
                for (int i = 0; i != shieldMoves.size(); i++)
                {
                    if (shieldMoves.at(i)[0] == 'P')
                        return (shieldMoves.at(i));
                }
                if (kingRunAwayMoves.size() == 0)
                    return (shieldMoves.at(rand() % shieldMoves.size()));
            }
            else
                if (kingRunAwayMoves.size() != 0)
                    return (kingRunAwayMoves.at(rand() % kingRunAwayMoves.size()));
        }
    }

    return ("");
}

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
