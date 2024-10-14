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
        }
        ~chessPiece() {};

        const string  getColor() const
        {
            return (_pos);
        }

        virtual const bool  whereCanIGo() const;

    protected:

        string  _color;
        string  _pos;

};

#endif