#ifndef KING_HPP
# define KING_HPP

# include "ChessPiece.hpp"

class King final : public ChessPiece
{
	public:
	
		King(const std::string& color, const std::string& pos) : ChessPiece(color, pos) { _type = 'K'; }
		~King() {};

		virtual bool isOnMyWay(const std::string& target, const std::vector<std::string>& boardCoords = {}, \
			const int value = 0, const std::string& enPassant = "") const
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