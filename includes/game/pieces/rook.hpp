#ifndef ROOK_HPP
# define ROOK_HPP

# include "chessPiece.hpp"

class Rook : chessPiece
{
    public:
    
        Rook(const string color, const string pos) : chessPiece(color, pos) {}
        ~Rook();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            int target_x = getCoordinateToX(move[0]);
            int target_y = atoi(move.c_str() + 1);

            for (int i = 1; i != 8; i++)
            {
                if (_x + i == target_x && _y == target_y)
                    return (true);
                if (_x == target_x && _y + i == target_y)
                    return (true);
            }
            return (false);
        }
};

#endif