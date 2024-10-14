#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : chessPiece
{
    public:
    
        Pawn();
        ~Pawn();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            int target_x = getCoordinateToX(move[0]);
            int target_y = atoi(move.c_str() + 1);

            if (_x + 1 == target_x && _y == target_y)
                return (true);
            if (_x + 1 == target_x && _y - 1 == target_y)
                return (true);
            if (_x + 1 == target_x && _y + 1 == target_y)
                return (true);
        }

    private:

        bool    doubleMove
        bool    enPassant;
};

#endif