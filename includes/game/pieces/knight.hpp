#ifndef KNIGHT_HPP
# define KNIGHT_HPP

# include "chessPiece.hpp"

class Knight : chessPiece
{
    public:
    
        Knight();
        ~Knight();

        virtual const bool  whereCanIGo() const
        {
            ;
        }
};

#endif