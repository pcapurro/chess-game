#ifndef KNIGHT_HPP
# define KNIGHT_HPP

# include "ChessPiece.hpp"
# include "../../AlgebraParser/AlgebraParser.hpp"

class Knight final : public ChessPiece
{
	public:
	
		Knight(const string& color, const string& pos) : ChessPiece(color, pos) { _type = 'N'; }
		~Knight() {};

		virtual bool isOnMyWay(const string& target, const vector<string>& boardCoords = {}, \
			const int value = 0, const string& enPassant = "") const
		{
			int	dest_x = target[0] - 97;
			int	dest_y = atoi(target.c_str() + 1);

			(void) boardCoords;
			(void) value;
			(void) enPassant;

			if (AlgebraParser::isChessCoord(target[0]) != true
				|| AlgebraParser::isChessDigit(target[1]) != true)
				return (false);

			if ((_x - 1 == dest_x && _y + 2 == dest_y) || (_x + 1 == dest_x && _y + 2 == dest_y))
				return (true);

			if ((_x - 1 == dest_x && _y - 2 == dest_y) || (_x + 1 == dest_x && _y - 2 == dest_y))
				return (true);

			if ((_x - 2 == dest_x && _y + 1 == dest_y) || (_x - 2 == dest_x && _y - 1 == dest_y))
				return (true);

			if ((_x + 2 == dest_x && _y + 1 == dest_y) || (_x + 2 == dest_x && _y - 1 == dest_y))
				return (true);

			return (false);
		}
};

#endif