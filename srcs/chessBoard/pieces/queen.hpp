#ifndef QUEEN_HPP
# define QUEEN_HPP

# include "chessPiece.hpp"

class Queen : public chessPiece
{
    public:
    
        Queen(const string color, const string pos) : chessPiece(color, pos) {}
        ~Queen() {};

        virtual const bool  checkAccess(const string move) const
        {
            int target_x = move[0] - 97;
            int target_y = atoi(move.c_str() + 1);

            for (int i = 1; i != 8; i++)
            {
                if ((_x + i == target_x && _y == target_y)
                || (_x - i == target_x && _y == target_y))
                    return (true);
                if ((_x == target_x && _y + i == target_y)
                    || (_x == target_x && _y - i == target_y))
                    return (true);
                if ((_x - i == target_x && _y + i == target_y)
                    || (_x + i == target_x && _y + i == target_y))
                    return (true);
                if ((_x - i == target_x && _y - i == target_y)
                    || (_x + i == target_x && _y - i == target_y))
                    return (true);
            }

            return (false);
        }

        virtual void    move(void)
        {
            _moves++;
        }
};

#endif