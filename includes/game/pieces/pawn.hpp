#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : chessPiece
{
    public:
    
        Pawn();
        ~Pawn();

        virtual const bool  whereCanIGo() const
        {
            ;
        }
};

#endif