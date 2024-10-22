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
        const int           getMoves(void) { return (_moves); }
        const int           getX(void) { return (_x); }
        const int           getY(void) { return (_y); }
    
        void                move(void) { _moves++; };

        void                updatePos(const string coord)
        {
            _x = coord[0] - 97;
            _y = atoi(coord.c_str() + 1);
        }

        virtual const bool  isOnMyWay(const string move, const vector<string> boardCoords = {},
                                        const int value = 0) const = 0;

    protected:

        string  _color;

        char    _type;

        int     _moves;
        int     _x;
        int     _y;

};

#endif