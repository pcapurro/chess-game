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
            _pos = pos;
            _moves = 0;

            _x = getCoordinateToX(pos[0]);
            _y = atoi(pos.c_str() + 1);
        }

        ~chessPiece() {};

        const string  getColor() const
        {
            return (_pos);
        }

        int getCoordinateToX(const char c) const
        {
            string letters = "abcdefgh";
            for (int i = 0; letters[i] != '\0'; i++)
            {
                if (letters[i] == c)
                    return (i);
            }
        }

        virtual const bool  checkMoveConsistency(const string move) const;

    protected:

        string  _color;
        string  _pos;
        int     _moves;
        int     _x;
        int     _y;

};

#endif