#include "AlgebraParser/AlgebraParser.hpp"

void	AlgebraParser::operator=(const std::string move)
{
	_move.move = move;

	isValid();
	if (_fail == false)
		parseMove();
}

bool	AlgebraParser::fail(void) const
{
	if (_fail == true)
		return (true);

	return (false);
}
