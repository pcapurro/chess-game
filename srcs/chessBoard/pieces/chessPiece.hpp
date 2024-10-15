#ifndef CHESSPIECE_HPP
# define CHESSPIECE_HPP

# include <iostream>
# include <vector>

using namespace std;

class chessPiece
{
    public:
        
        chessPiece(const string color, const string pos)
        {
            _color = color;
            _moves = 0;

            _x = getCoordinateToX(pos[0]);
            _y = atoi(pos.c_str() + 1);
        }

        ~chessPiece() {};

        int getCoordinateToX(const char c) const
        {
            for (int i = 0; "abcdefgh"[i] != '\0'; i++)
            {
                if ("abcdefgh"[i] == c)
                    return (i);
            }
            return (0);
        }

        const string  getColor() const { return (_color); }

        virtual const bool  checkMoveConsistency(const string move) const = 0;

    protected:

        string  _color;

        int     _moves;
        int     _x;
        int     _y;

};

#endif