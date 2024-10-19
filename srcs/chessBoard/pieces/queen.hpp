#ifndef QUEEN_HPP
# define QUEEN_HPP

# include "chessPiece.hpp"

class Queen : public chessPiece
{
    public:
    
        Queen(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~Queen() {};

        virtual const bool  isOnMyWay(const string move) const
        {
            return (false);
        }
};

#endif