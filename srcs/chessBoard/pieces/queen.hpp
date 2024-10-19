#ifndef QUEEN_HPP
# define QUEEN_HPP

# include "chessPiece.hpp"

class Queen : public chessPiece
{
    public:
    
        Queen(const char type, const string color, const string pos) : chessPiece(type, color, pos) {}
        ~Queen() {};

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords) const
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
                    if (isChessCoord(newCoords[0]) == true && isChessDigit(newCoords[1]) == true)
                    {
                        coords = coords + newCoords;
                        if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end())
                            break ;
                        if (newCoords == move)
                            return (true);
                    }
                    newCoords.clear();
                }
                newCoords.clear();
                src_x = _x;
                src_y = _y;
            }
            
            newCoords.clear();
            src_x = _x;
            src_y = _y;

            for (int k = 0; k != 4; k++)
            {
                for (int i = 0; i != 8; i++)
                {
                    if (k == 0)
                        src_x++, src_y++;
                    if (k == 1)
                        src_x--, src_y++;
                    if (k == 2)
                        src_x--, src_y--;
                    if (k == 3)
                        src_x++, src_y--;

                    newCoords = newCoords + "abcdefgh"[src_x] + to_string(src_y);
                    if (isChessCoord(newCoords[0]) == true && isChessDigit(newCoords[1]) == true)
                    {
                        coords = coords + newCoords;
                        if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end())
                            break ;
                        if (newCoords == move)
                            return (true);
                    }
                    newCoords.clear();
                }
                newCoords.clear();
                src_x = _x;
                src_y = _y;
            }
            return (false);
        }
};

#endif