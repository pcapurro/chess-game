#ifndef BISHOP_HPP
# define BISHOP_HPP

# include "chessPiece.hpp"

class Bishop : chessPiece
{
    public:
    
        Bishop(const string color, const string pos) : chessPiece(color, pos) {}
        ~Bishop();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            int target_x = getCoordinateToX(move[0]);
            int target_y = atoi(move.c_str() + 1);

            return (false);
        }
};

#endif