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

        bool    isValid();
        bool    fail() const;

    private:

        bool    isGoodLength() const;
        bool    isValidChar() const;

        bool    _fail;
        string _move;
};

#endif