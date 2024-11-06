#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : public chessPiece
{
    public:
    
        Pawn(const string color, const string pos) : chessPiece(color, pos) { _type = 'P'; }

        ~Pawn() {};

        virtual bool  isOnMyWay(const string move, const vector<string> boardCoords = {}, const int value = 0) const
        {
            int src_x = _x;
            int src_y = _y;
    
            int dest_x = move[0] - 97;
            int dest_y = atoi(move.c_str() + 1);

            string newCoord;

            if (_color == "white")
            {
                newCoord = "abcdefgh"[src_x + 1] + to_string(src_y + 1);
                if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end()
                    && src_x + 1 == dest_x && src_y + 1 == dest_y)
                    return (true);
                newCoord = "abcdefgh"[src_x - 1] + to_string(src_y + 1);
                if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end()
                    && src_x - 1 == dest_x && src_y + 1 == dest_y)
                    return (true);

                if (value == 0)
                {
                    newCoord = "abcdefgh"[src_x] + to_string(src_y + 1);
                    if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end()
                        && src_x == dest_x && src_y + 1 == dest_y)
                        return (true);
                    
                    if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end())
                    {
                        newCoord = "abcdefgh"[src_x] + to_string(src_y + 2);
                        if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end()
                            && src_x == dest_x && src_y + 2 == dest_y && _moves == 0)
                        return (true);
                    }
                }
            }

            if (_color == "black")
            {
                newCoord = "abcdefgh"[src_x + 1] + to_string(src_y - 1);
                if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end()
                    && src_x + 1 == dest_x && src_y - 1 == dest_y)
                    return (true);
                newCoord = "abcdefgh"[src_x - 1] + to_string(src_y - 1);
                if (find(boardCoords.begin(), boardCoords.end(), newCoord) != boardCoords.end()
                    && src_x - 1 == dest_x && src_y - 1 == dest_y)
                    return (true);

                if (value == 0)
                {
                    newCoord = "abcdefgh"[src_x] + to_string(src_y - 1);
                    if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end()
                        && src_x == dest_x && src_y - 1 == dest_y)
                        return (true);
                    
                    if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end())
                    {
                        newCoord = "abcdefgh"[src_x] + to_string(src_y - 2);
                        if (find(boardCoords.begin(), boardCoords.end(), newCoord) == boardCoords.end()
                            && src_x == dest_x && src_y - 2 == dest_y && _moves == 0)
                        return (true);
                    }
                }
            }

            return (false);
        }
};

#endif