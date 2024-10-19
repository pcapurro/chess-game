#ifndef BISHOP_HPP
# define BISHOP_HPP

# include "chessPiece.hpp"

class Bishop : public chessPiece
{
    public:
    
        Bishop(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~Bishop() {};

        virtual const bool  isOnMyWay(const string move) const
        {
            return (false);
        }
};

#endif