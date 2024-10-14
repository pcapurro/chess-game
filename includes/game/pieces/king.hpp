#ifndef KING_HPP
# define KING_HPP

# include "chessPiece.hpp"

class King : chessPiece
{
    public:
    
        King();
        ~King();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            int target_x = getCoordinateToX(move[0]);
            int target_y = atoi(move.c_str() + 1);

            if (_x - 1 == target_x && _y == target_y)
                return (true);
            if (_x == target_x && _y - 1 == target_y)
                return (true);
            if (_x + 1 == target_x && _y == target_y)
                return (true);
            if (_x == target_x && _y + 1 == target_y)
                return (true);
        }
};

#endif