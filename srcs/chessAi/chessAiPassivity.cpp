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

    return ("");
}

string  chessAi::getPawnsDev(void)
{
	string			move;
	vector<string>	legalMoves;
	vector<string>	pawns;

	legalMoves = getLegalMoves();
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
    vector<string>  legalMoves;
	string			nb1, nb2;

    legalMoves = getLegalMoves();

    if (_gameInfo._color == "white")
        nb1 = "1", nb2 = "3";
    else
        nb1 = "8", nb2 = "6";

    if (_board.at(getAtValue(string(1, 'g') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'g') + nb1)).piece->getType() == 'N'
        && _board.at(getAtValue(string(1, 'g') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Ng" + nb1 + 'f' + nb2) != legalMoves.end())
        {
            tryMove("g" + nb1 + 'f' + nb2);
            if (isProtected(string(1, 'f') + nb2) == true)
                { undoMove("g" + nb1 + 'f' + nb2); return ("Ng" + nb1 + 'f' + nb2); }
            undoMove("g" + nb1 + 'f' + nb2);
        }
    }
    if (_board.at(getAtValue(string(1, 'b') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'b') + nb1)).piece->getType() == 'N'
        && _board.at(getAtValue(string(1, 'b') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Nb" + nb1 + 'c' + nb2) != legalMoves.end())
        {
            tryMove("b" + nb1 + 'c' + nb2);
            if (isProtected(string(1, 'c') + nb2) == true)
                { undoMove("b" + nb1 + 'c' + nb2); return ("Nb" + nb1 + 'c' + nb2); }
            undoMove("b" + nb1 + 'c' + nb2);
        }
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

string  chessAi::getBishopsDev(void)
{
    vector<string>  legalMoves;
	string			nb1, nb2;

    legalMoves = getLegalMoves();

    if (_gameInfo._color == "white")
        nb1 = "1", rand() % 2 == 0 ? nb2 = "4" : nb2 = "5";
    else
        nb1 = "8", rand() % 2 == 0 ? nb2 = "5" : nb2 = "4";

    if (_board.at(getAtValue(string(1, 'f') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'f') + nb1)).piece->getType() == 'B'
        && _board.at(getAtValue(string(1, 'f') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Bf" + nb1 + 'c' + nb2) != legalMoves.end())
        {
            tryMove("f" + nb1 + 'c' + nb2);
            if (isProtected(string(1, 'c') + nb2) == true)
                { undoMove("f" + nb1 + 'c' + nb2); return ("Bf" + nb1 + 'c' + nb2); }
            undoMove("f" + nb1 + 'c' + nb2);
        }
    }
    if (_board.at(getAtValue(string(1, 'c') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'c') + nb1)).piece->getType() == 'B'
        && _board.at(getAtValue(string(1, 'c') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Bc" + nb1 + 'f' + nb2) != legalMoves.end())
        {
            tryMove("c" + nb1 + 'f' + nb2);
            if (isProtected(string(1, 'f') + nb2) == true)
                { undoMove("c" + nb1 + 'f' + nb2); return ("Bc" + nb1 + 'f' + nb2); }
            undoMove("c" + nb1 + 'f' + nb2);
        }
    }

    return ("");
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

    return (move);
}
