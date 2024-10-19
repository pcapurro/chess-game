#ifndef KNIGHT_HPP
# define KNIGHT_HPP

# include "chessPiece.hpp"

class Knight : public chessPiece
{
    public:
    
        Knight(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~Knight() {};

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords) const
        {
            return (false);
        }
};

#endif