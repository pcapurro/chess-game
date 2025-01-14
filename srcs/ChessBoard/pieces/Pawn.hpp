#ifndef PAWN_HPP
# define PAWN_HPP

# include "ChessPiece.hpp"

class Pawn final : public ChessPiece
{
	public:
	
		Pawn(const string color, const string pos) : ChessPiece(color, pos) { _type = 'P'; }

		~Pawn() {};

		virtual bool isOnMyWay(const string target, const vector<string> boardCoords = {}, \
			const int value = 0, const string enPassant = "") const
		{
			int	src_x = _x;
			int	src_y = _y;
	
			int	dest_x = target[0] - 97;
			int	dest_y = atoi(target.c_str() + 1);

			string	newCoord;

			if (_color == "white")
			{
				newCoord = "abcdefgh"[src_x + 1] + to_string(src_y + 1);
				if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end() \
					&& src_x + 1 == dest_x && src_y + 1 == dest_y)
					return (true);

				if (enPassant.empty() != true && target == enPassant && newCoord == target && _y == 5)
					return (true);

				newCoord = "abcdefgh"[src_x - 1] + to_string(src_y + 1);
				if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end() \
					&& src_x - 1 == dest_x && src_y + 1 == dest_y)
					return (true);

				if (enPassant.empty() != true && target == enPassant && newCoord == target && _y == 5)
					return (true);

				if (value == 0)
				{
					newCoord = "abcdefgh"[src_x] + to_string(src_y + 1);
					if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end() \
						&& src_x == dest_x && src_y + 1 == dest_y)
						return (true);
					
					if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end())
					{
						newCoord = "abcdefgh"[src_x] + to_string(src_y + 2);
						if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end() \
							&& src_x == dest_x && src_y + 2 == dest_y && _moves == 0)
						return (true);
					}
				}
			}

			if (_color == "black")
			{
				newCoord = "abcdefgh"[src_x + 1] + to_string(src_y - 1);
				if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end() \
					&& src_x + 1 == dest_x && src_y - 1 == dest_y)
					return (true);

				if (enPassant.empty() != true && target == enPassant && newCoord == target && _y == 4)
					return (true);

				newCoord = "abcdefgh"[src_x - 1] + to_string(src_y - 1);
				if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end() \
					&& src_x - 1 == dest_x && src_y - 1 == dest_y)
					return (true);

				if (enPassant.empty() != true && target == enPassant && newCoord == target && _y == 4)
					return (true);

				if (value == 0)
				{
					newCoord = "abcdefgh"[src_x] + to_string(src_y - 1);
					if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end() \
						&& src_x == dest_x && src_y - 1 == dest_y)
						return (true);
					
					if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end())
					{
						newCoord = "abcdefgh"[src_x] + to_string(src_y - 2);
						if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end() \
							&& src_x == dest_x && src_y - 2 == dest_y && _moves == 0)
						return (true);
					}
				}
			}

			return (false);
		}
};

#endif