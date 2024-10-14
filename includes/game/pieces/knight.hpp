#ifndef KNIGHT_HPP
# define KNIGHT_HPP

# include "chessPiece.hpp"

class Knight : chessPiece
{
    public:
    
        Knight(const string color, const string pos) : chessPiece(color, pos) {}
        ~Knight();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            int target_x = getCoordinateToX(move[0]);
            int target_y = atoi(move.c_str() + 1);

            return (false);
        }
};

#endif