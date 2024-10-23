#ifndef ROOK_HPP
# define ROOK_HPP

# include "chessPiece.hpp"

class Rook : public chessPiece
{
    public:
    
        Rook(const string color, const string pos) : chessPiece(color, pos) { _type = 'R'; }
        ~Rook() {};

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords = {}, const int value = 0) const
        {
            int src_x = _x;
            int src_y = _y;
    
            int dest_x = move[0] - 97;
            int dest_y = atoi(move.c_str() + 1);

            string  coords;
            string  newCoords;

            for (int k = 0; k != 4; k++)
            {
                for (int i = 0; i != 8; i++)
                {
                    if (k == 0)
                        src_x--;
                    if (k == 1)
                        src_x++;
                    if (k == 2)
                        src_y++;
                    if (k == 3)
                        src_y--;

                    newCoords = newCoords + "abcdefgh"[src_x] + to_string(src_y);
                    if (isChessCoord(newCoords[0]) == false || isChessDigit(newCoords[1]) == false)
                        break ;
                    else
                        coords = coords + newCoords;
                    if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end())
                        break ;
                    newCoords.clear();
                }
                src_x = _x;
                src_y = _y;
                newCoords.clear();
            }

            if (coords.find(move) != string::npos)
                return (true);
            return (false);
        }
};

#endif