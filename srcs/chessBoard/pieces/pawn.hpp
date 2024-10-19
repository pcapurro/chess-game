#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : public chessPiece
{
    public:
    
        Pawn(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}

        ~Pawn() {};

        virtual const bool  isOnMyWay(const string move) const
        {
            return (false);
        }
};

#endif