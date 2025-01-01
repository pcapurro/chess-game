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

            _originalPos = pos;
            _pos = pos;

            _x = pos[0] - 97;
            _y = atoi(pos.c_str() + 1);

            _visible = true;
        }

        virtual ~chessPiece() {};

        bool            isVisible(void) const { return (_visible); }
        void            setVisibility(void) { _visible == true ? _visible = false : _visible = true; }

        string          getColor() const { return (_color); }
        char            getType() const { return (_type); }
        
        int             getMoves(void) { return (_moves); }

        string          getCoord(void) const { return (_pos); }
        string          getOriginalCoord(void) const { return (_originalPos); }
        int             getX(void) const { return (_x); }
        int             getY(void) const { return (_y); }
        void            move(void) { _moves++; };

        void            updatePos(const string coord)
        {
            _pos = coord;
            _x = coord[0] - 97;
            _y = atoi(coord.c_str() + 1);
        }

        virtual bool  isOnMyWay(const string target, const vector<string> boardCoords = {}, \
                                    const int value = 0, const string enPassant = "") const = 0;

    protected:

        string  _color;

        char    _type;

        int     _moves;

        string  _originalPos;
        string  _pos;
        int     _x;
        int     _y;

        bool    _visible;

};

#endif