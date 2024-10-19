#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : public chessPiece
{
    public:
    
        Pawn(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}

        ~Pawn() {};

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords) const
        {
            int src_x = _x;
            int src_y = _y;
    
            int dest_x = move[0] - 97;
            int dest_y = atoi(move.c_str() + 1);

            if (_color == "white")
            {
                if (src_x + 1 == dest_x && src_y + 1 == dest_y)
                    return (true);
                if (src_x - 1 == dest_x && src_y + 1 == dest_y)
                    return (true);
            }
            if (_color == "black")
            {
                if (src_x + 1 == dest_x && src_y - 1 == dest_y)
                    return (true);
                if (src_x - 1 == dest_x && src_y - 1 == dest_y)
                    return (true);
            }
            return (false);
        }
};

#endif