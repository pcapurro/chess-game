#ifndef QUEEN_HPP
# define QUEEN_HPP

# include "chessPiece.hpp"
# include "../../algebraParser/algebraParser.hpp"

class Queen : public chessPiece
{
    public:
    
        Queen(const string color, const string pos) : chessPiece(color, pos) { _type = 'Q'; }
        ~Queen() {};

        virtual bool  isOnMyWay(const string target, const vector<string> boardCoords = {}, \
                                    const int value = 0, const string enPassant = "") const
        {
            int src_x = _x;
            int src_y = _y;

            string  coords;
            string  newCoords;

            (void) boardCoords;
            (void) value;
            (void) enPassant;

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
                    if (algebraParser::isChessCoord(newCoords[0]) == false || algebraParser::isChessDigit(newCoords[1]) == false)
                        break ;
                    else
                        coords = coords + newCoords;
                    if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end())
                        break ;
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
                    if (algebraParser::isChessCoord(newCoords[0]) == false || algebraParser::isChessDigit(newCoords[1]) == false)
                        break ;
                    else
                        coords = coords + newCoords;
                    if (find(boardCoords.begin(), boardCoords.end(), newCoords) != boardCoords.end())
                        break ;
                    newCoords.clear();
                }
                newCoords.clear();
                src_x = _x;
                src_y = _y;
            }

            if (coords.find(target) != string::npos)
                return (true);
            return (false);
        }
};

#endif