# include "AlgebraParser.hpp"

void	AlgebraParser::operator=(const string move)
{
	_move.move = move;
	_move.error = false;

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
