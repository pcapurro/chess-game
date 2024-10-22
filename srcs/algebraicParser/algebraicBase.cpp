#include "../../include/shellChess.hpp"

void    algebraicParser::operator=(const string move)
{
    _move.move = move;
    isValid();
    if (_fail == false)
        parseMove();
}

bool    algebraicParser::fail(void) const
{
    if (_fail == true)
        return (true);
    return (false);
}
