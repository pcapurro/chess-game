# include "AlgebraParser.hpp"

#include "../ChessBoard/pieces/King.hpp"
#include "../ChessBoard/pieces/Queen.hpp"
#include "../ChessBoard/pieces/Rook.hpp"
#include "../ChessBoard/pieces/Bishop.hpp"
#include "../ChessBoard/pieces/Knight.hpp"

bool	AlgebraParser::isChessDigit(const char c)
{
	if (c != '1' && c != '2' && c != '3' && c != '4'
		&& c != '5' && c != '6' && c != '7' && c != '8')
		return (false);

	return (true);
}

bool	AlgebraParser::isChessPiece(const char c)
{
	if (c != 'K' && c != 'Q' && c != 'R' && c != 'B' && c != 'N')
		return (false);

	return (true);
}

bool	AlgebraParser::isChessCoord(const char c)
{
	if (c != 'a' && c != 'b' && c != 'c' && c != 'd'
		&& c != 'e' && c != 'f' && c != 'g' && c != 'h')
		return (false);

	return (true);
}

string	AlgebraParser::getLeftSequence(void) const
{
	string  left;

	for (int i = 0; _move.move[i] != '\0'; i++)
	{
		if (_move.move[i] == 'x' || _move.move[i] == '-')
			break ;
		left += _move.move[i];
	}

	return (left);
}

string	AlgebraParser::getRightSequence(void) const
{
	string	right;

	for (int i = 0; _move.move[i] != '\0'; i++)
	{
		if (_move.move[i] == 'x' || _move.move[i] == '-')
			{ right = _move.move.c_str() + i + 1; break ; }
	}

	if (right[right.length() - 1] == '#' || right[right.length() - 1] == '+')
		right.erase(right.length() - 1);

	return (right);
}

vector<string>	getWatchersSequence(const char type, const string& move, const char sign)
{
	vector<string>	coords;
	ChessPiece*		object;

	if (type == 'K')
		object = new (nothrow) King("white", move);
	if (type == 'Q')
		object = new (nothrow) Queen("white", move);
	if (type == 'N')
		object = new (nothrow) Knight("white", move);
	if (type == 'B')
		object = new (nothrow) Bishop("white", move);
	if (type == 'R')
		object = new (nothrow) Rook("white", move);

	for (int i = 9; i != 1; i--)
	{
		for (int k = 0; k != 8; k++)
		{
			string newCoords = "abcdefgh"[k] + to_string(i - 1);
			if (object->isOnMyWay(newCoords) == true \
				&& (sign == 'i' || newCoords[0] == sign))
				coords.push_back(newCoords);
		}
	}

	delete object;
	object = nullptr;

	return (coords);
}

vector<string>	getPawnSequence(const string& move, const int turn, const char sign)
{
	vector<string>	coords;
	vector<string>	realCoords;
	string			newMove;
	string			newCoords;

	newMove = move;
	if (move.length() > 2)
		newMove.erase(newMove.length() - 1);

	newCoords = newMove;
	if (turn % 2 == 0)
	{
		newCoords[1] = newCoords[1] - 1;
		coords.push_back(newCoords);

		newCoords = newMove;
		newCoords[1] = newCoords[1] - 2;
		coords.push_back(newCoords);

		newCoords = newMove;
		newCoords[0] = newCoords[0] - 1;
		newCoords[1] = newCoords[1] - 1;
		coords.push_back(newCoords);
	
		newCoords = newMove;
		newCoords[0] = newCoords[0] + 1;
		newCoords[1] = newCoords[1] - 1;
		coords.push_back(newCoords);
	}
	else
	{
		newCoords[1] = newCoords[1] + 1;
		coords.push_back(newCoords);

		newCoords = newMove;
		newCoords[1] = newCoords[1] + 2;
		coords.push_back(newCoords);

		newCoords = newMove;
		newCoords[0] = newCoords[0] + 1;
		newCoords[1] = newCoords[1] + 1;
		coords.push_back(newCoords);

		newCoords = newMove;
		newCoords[0] = newCoords[0] - 1;
		newCoords[1] = newCoords[1] + 1;
		coords.push_back(newCoords);
	}

	for (size_t i = 0; i != coords.size(); i++)
	{
		if (sign == 'i' || coords.at(i)[0] == sign)
			realCoords.push_back(coords.at(i));
	}

	return (realCoords);
}
