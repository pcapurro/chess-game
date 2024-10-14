#ifndef ROOK_HPP
# define ROOK_HPP

# include "chessPiece.hpp"

class Rook : chessPiece
{
    public:
    
        Rook();
        ~Rook();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            ;
        }
};

#endif