#include "../../include/header.hpp"

algebraicParser::algebraicParser(void) { _turn = 0; }

algebraicParser::~algebraicParser(void) {}

void    algebraicParser::setTurn(const int turn) { _turn = turn; }

t_move  algebraicParser::getParsedMove(void) const { return (_move); };

void    algebraicParser::operator=(const string move)
{
    _move.move = move;
    isValid();
    if (_fail == false)
        parseMove();
}

bool    algebraicParser::fail(void) const
{
    if (_fail == false)
        return (false);
    return (true);
}

void    algebraicParser::printInvalid(void) const
{
    cout << "\033[2A" << ERASE_LINE;
    cerr << RED << "Invalid move. " << COLOR_E;
}
