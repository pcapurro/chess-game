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
            int dest_x = move[0] - 97;
            int dest_y = atoi(move.c_str() + 1);

            if (_x - 1 == dest_x && _y + 2 == dest_y)
                return (true);
            if (_x + 1 == dest_x && _y + 2 == dest_y)
                return (true);

            if (_x - 1 == dest_x && _y - 2 == dest_y)
                return (true);
            if (_x + 1 == dest_x && _y - 2 == dest_y)
                return (true);

            if (_x - 2 == dest_x && _y + 1 == dest_y)
                return (true);
            if (_x - 2 == dest_x && _y - 1 == dest_y)
                return (true);

            if (_x + 2 == dest_x && _y + 1 == dest_y)
                return (true);
            if (_x + 2 == dest_x && _y - 1 == dest_y)
                return (true);

            return (false);
        }
};

#endif