#ifndef KNIGHT_HPP
# define KNIGHT_HPP

# include "chessPiece.hpp"

class Knight : public chessPiece
{
    public:
    
        Knight(const string color, const string pos) : chessPiece(color, pos) { _type = 'N'; }
        ~Knight() {};

        virtual bool  isOnMyWay(const string move, const vector<string> boardCoords = {}, const int value = 0) const
        {
            int dest_x = move[0] - 97;
            int dest_y = atoi(move.c_str() + 1);

            (void) boardCoords;
            (void) value;

            if ((_x - 1 == dest_x && _y + 2 == dest_y) || (_x + 1 == dest_x && _y + 2 == dest_y))
                return (true);

            if ((_x - 1 == dest_x && _y - 2 == dest_y) || (_x + 1 == dest_x && _y - 2 == dest_y))
                return (true);

            if ((_x - 2 == dest_x && _y + 1 == dest_y) || (_x - 2 == dest_x && _y - 1 == dest_y))
                return (true);

            if ((_x + 2 == dest_x && _y + 1 == dest_y) || (_x + 2 == dest_x && _y - 1 == dest_y))
                return (true);

            return (false);
        }
};

#endif