#include "chessAi.hpp"

string  chessAi::getPawnsOpening(void)
{
    int value;

    srand(time(nullptr));
    value = rand() % 10;

    if (_gameInfo._turn == 0)
    {
        if (value < 6)
            return ("Pe2e4");
        if (value == 6 || value == 7 || value == 8)
            return ("Pd2d3");
        if (value == 9)
            return ("Pd2d4");
    }

    if (_gameInfo._turn == 1)
    {
        if (_board.at(getAtValue("e4")).piece != NULL)
        {
            if (value == 0)
                return ("Pd7d5");
            if (value < 6)
                return ("Pe7e5");
            if (value >= 6 && value < 9)
                return ("Pd7d6");
        }
        if (_board.at(getAtValue("d4")).piece != NULL)
        {
            if (value < 7)
                return ("Pd7d5");
            if (value > 7)
                return ("Pe7e6");
        }

        if (value < 6)
            return ("Pe7e6");
        if (value == 6 || value == 7 || value == 8)
            return ("Pe7e5");
        if (value == 9)
            return ("Pd7d5");
    }

    srand(time(nullptr));
    value = rand() % 2;

	if (_gameInfo._turn == 2)
	{
		if (_board.at(getAtValue("d3")).piece != NULL)
			return ("Pe2e4");
		if (_board.at(getAtValue("e4")).piece != NULL)
		{
			if (value % 2 == 0)
				return ("Pd2d3");
			else
				return ("Pd2d4");
		}
	}

	if (_gameInfo._turn == 3)
	{
        if (_board.at(getAtValue("e6")).piece != NULL)
            return ("Pd7d5");
        if (_board.at(getAtValue("e5")).piece != NULL)
            return ("Pd7d6");
	}

    return ("");
}

string  chessAi::getPawnsDev(void)
{
	string			move;
	vector<string>	legalMoves;
	vector<string>	pawns;

	legalMoves = getLegalMoves();

    if (find(legalMoves.begin(), legalMoves.end(), "Pe2e3") != legalMoves.end()
        && isMoveWorth("e2e3") == true)
        return ("Pe2e3");

    if (find(legalMoves.begin(), legalMoves.end(), "Pe7e6") != legalMoves.end()
        && isMoveWorth("e7e6") == true)
        return ("Pe7e6");

    if (find(legalMoves.begin(), legalMoves.end(), "Pd2d3") != legalMoves.end()
        && isMoveWorth("d2d3") == true)
        return ("Pd2d3");

    if (find(legalMoves.begin(), legalMoves.end(), "Pd7d6") != legalMoves.end()
        && isMoveWorth("d7d6") == true)
        return ("Pd7d6");

	for (int i = 0; i != legalMoves.size(); i++)
	{
		if (legalMoves.at(i)[0] == 'P')
		{
			move = legalMoves.at(i);
			if (count(move.begin(), move.end(), 'O') == 0)
				move = move.c_str() + 1,

			tryMove(move);
			if (isProtected(string(1, move[2]) + move[3]) == true)
				pawns.push_back(legalMoves.at(i));
			undoMove(move);
		}
	}

    move.clear();

    srand(time(nullptr));

	if (pawns.size() == 1)
		move = pawns.at(0);
	if (pawns.size() > 1)
		move = (pawns.at(rand() % pawns.size()));

    return (move);
}

string  chessAi::getKnightsDev(void)
{
    char            line;
    string          knightOne, knightTwo;
    vector<string>  legalMoves;

    if (_gameInfo._color == "white")
        knightOne = "b1", knightTwo = "g1", line = '3';
    if (_gameInfo._color == "black")
        knightOne = "b8", knightTwo = "g8", line = '6';

    legalMoves = getLegalMoves();

    if (_board.at(getAtValue(knightOne)).piece != NULL && _board.at(getAtValue(knightOne)).piece->getType() == 'N'
        && _board.at(getAtValue(knightOne)).piece->getMoves() == 0)
    {
        string  move;

        move = "N" + knightOne + "c" + line;
        if (find(legalMoves.begin(), legalMoves.end(), move) != legalMoves.end())
            return (move);
        move = "N" + knightOne + "a" + line;
        if (find(legalMoves.begin(), legalMoves.end(), move) != legalMoves.end())
            return (move);
    }
    if (_board.at(getAtValue(knightTwo)).piece != NULL && _board.at(getAtValue(knightTwo)).piece->getType() == 'N'
        && _board.at(getAtValue(knightTwo)).piece->getMoves() == 0)
    {
        string  move;

        move = "N" + knightTwo + "f" + line;
        if (find(legalMoves.begin(), legalMoves.end(), move) != legalMoves.end())
            return (move);
        move = "N" + knightTwo + "h" + line;
        if (find(legalMoves.begin(), legalMoves.end(), move) != legalMoves.end())
            return (move);
    }

    return ("");
}

string  chessAi::getBishopsDev(void)
{
    int             attackedValue;
    string          coord1, coord2, numbers;
    vector<string>  legalMoves;

    if (_gameInfo._color == "white")
        coord1 = "f1", coord2 = "c1", numbers = "452";
    if (_gameInfo._color == "black")
        coord1 = "f8", coord2 = "c8", numbers = "547";

    legalMoves = getLegalMoves();

    if (_board.at(getAtValue(coord1)).piece != NULL && _board.at(getAtValue(coord1)).piece->getType() == 'B'
        && _board.at(getAtValue(coord1)).piece->getMoves() == 0)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "B" + coord1 + "c" + numbers[0]) != legalMoves.end()
            && isMoveWorth(coord1 + "c" + numbers[0]) == true)
            return ("B" + coord1 + "c" + numbers[0]);

        if (find(legalMoves.begin(), legalMoves.end(), "B" + coord1 + "b" + numbers[1]) != legalMoves.end()
            && isMoveWorth(coord1 + "b" + numbers[1]) == true)
            return ("B" + coord1 + "b" + numbers[1]);

        if (find(legalMoves.begin(), legalMoves.end(), "B" + coord1 + "e" + numbers[2]) != legalMoves.end()
            && isMoveWorth(coord1 + "e" + numbers[2]) == true)
            return ("B" + coord1 + "e" + numbers[2]);
    }

    if (_board.at(getAtValue(coord2)).piece != NULL && _board.at(getAtValue(coord2)).piece->getType() == 'B'
        && _board.at(getAtValue(coord2)).piece->getMoves() == 0)
    {        
        if (find(legalMoves.begin(), legalMoves.end(), "B" + coord2 + "f" + numbers[0]) != legalMoves.end()
            && isMoveWorth(coord2 + "f" + numbers[0]) == true)
            return ("B" + coord2 + "f" + numbers[0]);

        if (find(legalMoves.begin(), legalMoves.end(), "B" + coord2 + "g" + numbers[1]) != legalMoves.end()
            && isMoveWorth(coord2 + "g" + numbers[1]) == true)
            return ("B" + coord2 + "g" + numbers[1]);

        if (find(legalMoves.begin(), legalMoves.end(), "B" + coord2 + "d" + numbers[2]) != legalMoves.end()
            && isMoveWorth(coord2 + "d" + numbers[2]) == true)
            return ("B" + coord2 + "d" + numbers[2]);
    }

    return ("");
}

string  chessAi::getCastling(void)
{
    if (isCastlingPossible("O-O") == true && isCheck() == false)
        return ("O-O");
    if (isCastlingPossible("O-O-O") == true && isCheck() == false)
        return ("O-O-O");

    return ("");
}

string  chessAi::getRandomDev(void)
{
    string          move, dest;
	vector<string>	legalMoves;

	legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];

        tryMove(legalMoves.at(i).c_str() + 1);
        if (isProtected(dest) == true)
        {
            undoMove(legalMoves.at(i).c_str() + 1);
            move = legalMoves.at(i);
            break ;
        }
        undoMove(legalMoves.at(i).c_str() + 1);
    }

    return (move);
}

string  chessAi::getPassiveMove(void)
{
    string	move;

    move = getPawnsOpening();

    if (move == "")
        move = getBishopsDev();
    if (move == "")
        move = getKnightsDev();

    if (move == "")
        move = getCastling();

    if (move == "")
		move = getPawnsDev();

    if (move == "")
        move = getRandomDev();

    return (move);
}
