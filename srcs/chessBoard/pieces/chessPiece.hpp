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

            _x = pos[0] - 97;
            _y = atoi(pos.c_str() + 1);
        }

        ~chessPiece() {};

        void    increaseMovesNb(void) { _moves++; }
        const string  getColor() const { return (_color); }

        virtual const bool  checkAccess(const string move) const = 0;
        virtual void        move(void) = 0;

    protected:

        string  _color;

        int     _moves;
        int     _x;
        int     _y;

};

#endif