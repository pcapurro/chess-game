#ifndef ALGEBRAICCHECKER_HPP
# define ALGEBRAICCHECKER_HPP

# include <iostream>

using namespace std;

class algebraicChecker
{
    public:

        algebraicChecker();
        ~algebraicChecker();

        void    operator=(string move);

        bool    fail() const;

    private:

        bool    isValid();
        bool    isGoodLength() const;
        bool    isValidComplexSequence() const;
        bool    isValidSimpleSequence() const;
        bool    isValidSequence() const;
        bool    isValidChar() const;

        bool    _fail;
        string _move;
};

bool    isChessDigit(char c);
bool    isChessPiece(char c);
bool    isChessLetter(char c);

#endif