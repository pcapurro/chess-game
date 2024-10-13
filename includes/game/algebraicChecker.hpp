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
        bool    isValidSequence() const;
        bool    isValidChar() const;

        bool    _fail;
        string _move;
};

bool    isChessDigit(int nb);

#endif