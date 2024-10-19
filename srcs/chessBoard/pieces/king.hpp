#ifndef KING_HPP
# define KING_HPP

# include "chessPiece.hpp"

class King : public chessPiece
{
    public:
    
        King(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~King() {};

        virtual const bool  isOnMyWay(const string move) const
        {
            return (false);
        }

};

#endif