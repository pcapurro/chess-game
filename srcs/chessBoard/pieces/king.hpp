#ifndef KING_HPP
# define KING_HPP

# include "chessPiece.hpp"

class King : public chessPiece
{
	public:
	
		King(const string color, const string pos) : chessPiece(color, pos) { _type = 'K'; }
		~King() {};

		virtual bool isOnMyWay(const string target, const vector<string> boardCoords = {}, \
			const int value = 0, const string enPassant = "") const
		{
			int	dest_x = target[0] - 97;
			int	dest_y = atoi(target.c_str() + 1);

			(void) boardCoords;
			(void) value;
			(void) enPassant;

			if ((_x + 1 == dest_x && _y - 1 == dest_y) || (_x + 1 == dest_x && _y == dest_y))
				return (true);
			if ((_x + 1 == dest_x && _y + 1 == dest_y) || (_x - 1 == dest_x && _y - 1 == dest_y))
				return (true);

			if ((_x - 1 == dest_x && _y == dest_y) || (_x - 1 == dest_x && _y + 1 == dest_y))
				return (true);
			if ((_x == dest_x && _y + 1 == dest_y) || (_x == dest_x && _y - 1 == dest_y))
				return (true);

			return (false);
		}

};

#endif