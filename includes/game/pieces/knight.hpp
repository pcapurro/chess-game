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

            if ((_x + 2 == target_x && _y + 1 == target_y)
                || (_x + 2 == target_x && _y - 1 == target_y)
                || (_x - 2 == target_x && _y + 1 == target_y)
                || (_x - 2 == target_x && _y - 1 == target_y))
                return (true);
            
            if ((_x + 1 == target_x && _y + 2 == target_y)
                || (_x - 1 == target_x && _y + 2 == target_y)
                || (_x + 1 == target_x && _y - 2 == target_y)
                || (_x - 1 == target_x && _y - 2 == target_y))
                return (true);

            return (false);
        }
};

#endif