#include "AlgebraParser/AlgebraParser.hpp"

#include "ChessBoard/King.hpp"
#include "ChessBoard/Queen.hpp"
#include "ChessBoard/Rook.hpp"
#include "ChessBoard/Bishop.hpp"
#include "ChessBoard/Knight.hpp"

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

std::string	AlgebraParser::getLeftSequence(void) const
{
	std::string  left;

	for (int i = 0; _move.move[i] != '\0'; i++)
	{
		if (_move.move[i] == 'x' || _move.move[i] == '-')
			break ;
		left += _move.move[i];
	}

	return (left);
}

std::string	AlgebraParser::getRightSequence(void) const
{
	std::string	right;

	for (int i = 0; _move.move[i] != '\0'; i++)
	{
		if (_move.move[i] == 'x' || _move.move[i] == '-')
			{ right = _move.move.c_str() + i + 1; break ; }
	}

	if (right[right.length() - 1] == '#' || right[right.length() - 1] == '+')
		right.erase(right.length() - 1);

	return (right);
}

std::vector<std::string>	getWatchersSequence(const char type, const std::string& move, const char sign)
{
	std::vector<std::string>	coords;
	ChessPiece*					object;

	King	king("white", move);
	Queen	queen("white", move);
	Knight	knight("white", move);
	Bishop	bishop("white", move);
	Rook	rook("white", move);

	if (type == 'K')
		object = &king;
	if (type == 'Q')
		object = &queen;
	if (type == 'N')
		object = &knight;
	if (type == 'B')
		object = &bishop;
	if (type == 'R')
		object = &rook;

	for (int i = 9; i != 1; i--)
	{
		for (int k = 0; k != 8; k++)
		{
			std::string newCoords = "abcdefgh"[k] + std::to_string(i - 1);
			if (object->isOnMyWay(newCoords) == true \
				&& (sign == 'i' || newCoords[0] == sign))
				coords.push_back(newCoords);
		}
	}

	return (coords);
}

std::vector<std::string>	getPawnSequence(const std::string& move, const int turn, const char sign)
{
	std::vector<std::string>	coords;
	std::vector<std::string>	realCoords;
	std::string					newMove;
	std::string					newCoords;

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
