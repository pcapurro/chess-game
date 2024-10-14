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

            return (false);
        }
};

#endif