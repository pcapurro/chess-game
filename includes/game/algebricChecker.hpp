#ifndef ALGEBRICCHECKER_HPP
# define ALGEBRICCHECKER_HPP

# include <iostream>

using namespace std;

class algebricChecker
{
    public:

        algebricChecker();
        ~algebricChecker();

        bool    isValid() const;

    private:

        string _move;
};

#endif