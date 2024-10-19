#ifndef BISHOP_HPP
# define BISHOP_HPP

# include "chessPiece.hpp"

class Bishop : public chessPiece
{
    public:
    
        Bishop(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~Bishop() {};

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords) const
        {
            int src_x = _x;
            int src_y = _y;
    
            int dest_x = move[0] - 97;
            int dest_y = atoi(move.c_str() + 1);

            string  coords;
            string  newCoords;

            for (int i = 0; i != 8; i++)
            {
                if (src_x < dest_x && src_y < dest_y)
                    src_x++, src_y++;
                if (src_x > dest_x && src_y < dest_y)
                    src_x--, src_y++;
                if (src_x > dest_x && src_y > dest_y)
                    src_x--, src_y--;
                if (src_x < dest_x && src_y > dest_y)
                    src_x++, src_y--;

                newCoords = newCoords + "abcdefgh"[src_x] + to_string(src_y);
                if (isChessCoord(newCoords[0]) == true && isChessDigit(newCoords[1]) == true)
                    coords = coords + newCoords;
                if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end()
                    || newCoords == move)
                    break ;
                newCoords.clear();
            }

            if (coords.find(move) == string::npos)
                return (false);
            return (true);
        }
};

#endif