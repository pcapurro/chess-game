#ifndef KING_HPP
# define KING_HPP

# include "chessPiece.hpp"

class King : chessPiece
{
    public:
    
        King();
        ~King();

        virtual const bool  whereCanIGo() const
        {
            ;
        }
};

#endif