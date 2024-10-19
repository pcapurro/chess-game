#ifndef ROOK_HPP
# define ROOK_HPP

# include "chessPiece.hpp"

class Rook : public chessPiece
{
    public:
    
        Rook(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~Rook() {};

        virtual const bool  isOnMyWay(const string move) const
        {
            return (false);
        }
};

#endif