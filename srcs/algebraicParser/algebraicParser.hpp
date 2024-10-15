#ifndef ALGEBRAICPARSER_HPP
# define ALGEBRAICPARSER_HPP

# include <iostream>

using namespace std;

class algebraicParser
{
    public:

        algebraicParser();
        ~algebraicParser();

        void    operator=(const string move);

        string  getParsedMove() const;
        bool    fail() const;

    private:

        bool    isValid();
        
        bool    isGoodLength() const;
        bool    isValidComplexSequence() const;
        bool    isValidSimpleSequence() const;
        bool    isValidSequence() const;
        bool    isValidChar() const;

        void    parseMove();

        bool    _fail;
        string  _move;
        string  _newMove;
};

bool    isChessDigit(const char c);
bool    isChessPiece(const char c);
bool    isChessCoord(const char c);

#endif