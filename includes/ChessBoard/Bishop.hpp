#ifndef BISHOP_HPP
# define BISHOP_HPP

# include "ChessPiece.hpp"
# include "AlgebraParser/AlgebraParser.hpp"

class Bishop final : public ChessPiece
{
	public:
	
		Bishop(const std::string& color, const std::string& pos) : ChessPiece(color, pos) { _type = 'B'; }
		~Bishop() {};

		virtual bool isOnMyWay(const std::string& target, const std::vector<std::string>& boardCoords = {}, \
			const int value = 0, const std::string& enPassant = "") const
		{
			int	src_x = _x;
			int	src_y = _y;

			std::string	coords;
			std::string	newCoords;

			(void) boardCoords;
			(void) value;
			(void) enPassant;

			for (int k = 0; k != 4; k++)
			{
				for (int i = 0; i != 8; i++)
				{
					if (k == 0)
						src_x++, src_y++;
					if (k == 1)
						src_x--, src_y++;
					if (k == 2)
						src_x--, src_y--;
					if (k == 3)
						src_x++, src_y--;

					newCoords += "abcdefgh"[src_x] + std::to_string(src_y);
					if (AlgebraParser::isChessCoord(newCoords[0]) == false \
						|| AlgebraParser::isChessDigit(newCoords[1]) == false)
						break ;
					else
						coords += newCoords;
					if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end())
						break ;
					newCoords.clear();
				}
				src_x = _x;
				src_y = _y;
				newCoords.clear();
			}

			if (coords.find(target) != std::string::npos)
				return (true);
	
			return (false);
		}
};

#endif