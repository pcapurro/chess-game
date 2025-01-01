# include "algebraParser.hpp"

void	algebraParser::parseDoubleSequence(void)
{
	if (count(_move.move.begin(), _move.move.end(), 'x') != 0)
		_move.action = 'x';
	if (count(_move.move.begin(), _move.move.end(), '-') != 0)
		_move.action = '-';

	string	left = getLeftSequence();
	string	right = getRightSequence();
	string	middle;

	if (left.length() < 3 
		|| (algebraParser::isChessCoord(_move.move[0]) == false && left.length() == 1))
	{
		vector<string>	coords;

		char	c = 'i';
		if (left.length() == 1 && algebraParser::isChessCoord(left[0]) == true)
			c = left[0];

		if (algebraParser::isChessCoord(_move.move[0]) == true)
			coords = getPawnSequence(right, _turn, c);
		else
			coords = getWatchersSequence(_move.move[0], right, 'i');

		if (coords.size() == 1 && coords.at(0) == "error")
			{ _move.error = true; return ; }

		for (size_t i = 0; i != coords.size(); i++)
		{
			if (algebraParser::isChessCoord(coords.at(i)[0]) == true
				&& algebraParser::isChessDigit(coords.at(i)[1]) == true)
			{
				if (left.length() != 2 || (left.length() == 2 && coords.at(i)[0] == _move.move[1]))
					middle = middle + coords.at(i);
			}
		}
	}

	if (algebraParser::isChessCoord(_move.move[0]) == true && left.length() != 1)
		_move.obj = 'P', _move.src = left, _move.dest = right;
	else
	{
		algebraParser::isChessCoord(_move.move[0]) == true ? _move.obj = 'P' : _move.obj = _move.move[0];
		middle.size() != 0 ? _move.src = middle : _move.src = (left.c_str() + 1);
		_move.dest = right;
	}
}

void	algebraParser::parseUniqueSequence(void)
{
	vector<string>	coords;
	int 			i = 0;

	if (algebraParser::isChessCoord(_move.move[0]) == true)
		coords = getPawnSequence(_move.move, _turn, 'i'), _move.obj = 'P';
	else
	{   
		char	sign = 'i';
		if (_move.move.length() == 4)
			sign = _move.move[1], i = 1;

		_move.obj = _move.move[0];
		coords = getWatchersSequence(_move.move[0], _move.move.c_str() + 1 + i, sign);

		if (coords.size() == 1 && coords.at(0) == "error")
			{ _move.error = true; return ; }
	}

	for (size_t i = 0; i != coords.size(); i++)
	{
		if (algebraParser::isChessCoord(coords.at(i)[0]) == true
			&& algebraParser::isChessDigit(coords.at(i)[1]) == true)
			_move.src = _move.src + coords.at(i);
	}
	if (algebraParser::isChessCoord(_move.move[0]) == true)
		_move.dest = _move.dest + _move.move.c_str();
	else
		_move.dest = _move.dest + (_move.move.c_str() + 1 + i);
}

void	algebraParser::parseMove(void)
{
	_move.src.clear();
	_move.dest.clear();

	_move.action = '>';
	if (_move.move == "O-O" || _move.move == "O-O-O")
		_move.obj = 'R', _move.src = "", _move.dest = _move.move;
	else
	{
		if (count(_move.move.begin(), _move.move.end(), '#') != 0
			|| count(_move.move.begin(), _move.move.end(), '+') != 0)
			_move.move.erase(_move.move.length() - 1);

		if (count(_move.move.begin(), _move.move.end(), 'x') != 0
			|| count(_move.move.begin(), _move.move.end(), '-') != 0)
			parseDoubleSequence();
		else
			parseUniqueSequence();
	}
}
