#ifndef BISHOP_HPP
# define BISHOP_HPP

# include "chessPiece.hpp"

class Bishop : chessPiece
{
    public:
    
        Bishop();
        ~Bishop();

        virtual const bool  whereCanIGo() const
        {
            ;
        }
};

#endif