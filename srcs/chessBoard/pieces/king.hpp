#ifndef KING_HPP
# define KING_HPP

# include "chessPiece.hpp"

class King : public chessPiece
{
    public:
    
        King(const string color, const string pos) : chessPiece(color, pos) {}
        ~King() {};

        virtual const bool  checkAccess(const string move) const
        {
            int target_x = move[0] - 97;
            int target_y = atoi(move.c_str() + 1);

            if ((_x - 1 == target_x && _y == target_y) || (_x == target_x && _y - 1 == target_y))
                return (true);
            if ((_x + 1 == target_x && _y == target_y) || (_x == target_x && _y + 1 == target_y))
                return (true);
            if ((_x - 1 == target_x && _y + 1 == target_y) || (_x + 1 == target_x && _y + 1 == target_y))
                return (true);
            if ((_x - 1 == target_x && _y - 1 == target_y) || (_x + 1 == target_x && _y - 1 == target_y))
                return (true);

            return (false);
        }
};

#endif