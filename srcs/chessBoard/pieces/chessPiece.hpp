#ifndef CHESSPIECE_HPP
# define CHESSPIECE_HPP

# include <iostream>
# include <vector>

using namespace std;

class chessPiece
{
    public:
        
        chessPiece(const char type, const string color, const string pos)
        {
            _type = type;
            _color = color;
            _moves = 0;

            _x = pos[0] - 97;
            _y = atoi(pos.c_str() + 1);
        }

        ~chessPiece() {};

        const string        getColor() const { return (_color); }
        const char          getType() const { return (_type); }
        void                move(void) { _moves++; };
        const int           getMoves(void) { return (_moves); }

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords) const = 0;

    protected:

        string  _color;

        char    _type;

        int     _moves;
        int     _x;
        int     _y;

};

#endif