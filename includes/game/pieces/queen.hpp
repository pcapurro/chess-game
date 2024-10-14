#ifndef QUEEN_HPP
# define QUEEN_HPP

# include "chessPiece.hpp"

class Queen : chessPiece
{
    public:
    
        Queen();
        ~Queen();

        virtual const bool  checkMoveConsistency(const string move) const
        {
            ;
        }
};

#endif