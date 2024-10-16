#ifndef KNIGHT_HPP
# define KNIGHT_HPP

# include "chessPiece.hpp"

class Knight : public chessPiece
{
    public:
    
        Knight(const string color, const string pos) : chessPiece(color, pos) {}
        ~Knight() {};

        virtual const bool  checkAccess(const string move) const
        {
            int target_x = move[0] - 97;
            int target_y = atoi(move.c_str() + 1);

            if ((_x + 2 == target_x && _y + 1 == target_y)
                || (_x + 2 == target_x && _y - 1 == target_y)
                || (_x - 2 == target_x && _y + 1 == target_y)
                || (_x - 2 == target_x && _y - 1 == target_y))
                return (true);
            
            if ((_x + 1 == target_x && _y + 2 == target_y)
                || (_x - 1 == target_x && _y + 2 == target_y)
                || (_x + 1 == target_x && _y - 2 == target_y)
                || (_x - 1 == target_x && _y - 2 == target_y))
                return (true);

            return (false);
        }
};

#endif