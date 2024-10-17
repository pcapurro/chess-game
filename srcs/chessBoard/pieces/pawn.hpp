#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : public chessPiece
{
    public:
    
        Pawn(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}

        ~Pawn() {};

        virtual const bool  checkAccess(const string move) const
        {
            int target_x = move[0] - 97;
            int target_y = atoi(move.c_str() + 1);

            if (_color == "white")
            {
                if ((_x + 1 == target_x && _y + 1 == target_y) || (_x - 1 == target_x && _y + 1 == target_y))
                    return (true);
                if (_x == target_x && _y + 1 == target_y)
                    return (true);
                if (_x == target_x && _y + 2 == target_y)
                    return (true);
            }
            else
            {
                if ((_x + 1 == target_x && _y - 1 == target_y) || (_x - 1 == target_x && _y - 1 == target_y))
                    return (true);
                if (_x == target_x && _y - 1 == target_y)
                    return (true);
                if (_x == target_x && _y - 2 == target_y)
                    return (true);
            }
            return (false);
        }
};

#endif