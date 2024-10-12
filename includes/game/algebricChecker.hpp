#ifndef ALGEBRICCHECKER_HPP
# define ALGEBRICCHECKER_HPP

# include <iostream>

using namespace std;

class algebricChecker
{
    public:

        algebricChecker();
        ~algebricChecker();

        void    operator=(string move);

        bool    isValid() const;

    private:

        string _move;
};

#endif