#include "ShellGame/ShellGame.hpp"

string	ShellGame::getShellAnswer(void) const
{
	string	answer;

	if (_sandBoxMode == false && ((_board->getActualTurn() % 2 == 0 && _aiSide % 2 == 0) \
		|| (_board->getActualTurn() % 2 != 0 && _aiSide % 2 != 0)))
	{
		answer = _ai->getBestMove(_board->getHistory());

		char	type = _board->getType(string{answer[0], answer[1]});

		if (type + answer == "Ke1g1" || type + answer == "Ke8g8")
			return ("O-O");
		if (type + answer == "Ke1c1" || type + answer == "Ke8c8")
			return ("O-O-O");

		string	src = string{answer[0], answer[1]};
		string	dest = string{answer[2], answer[3]};

		if (type != 'P')
			src = string{type} + src;
		if (answer.size() == 3)
			dest += answer[2];

		_board->getType(dest) != ' ' ? answer = src + 'x' + dest : answer = src + '-' + dest;
	}
	else
	{
		cout << ERASE_LINE << "> ";
		getline(cin, answer);
		cout << "\033[1A";

		if (cin.fail() == true)
			return ("error");
	}

	return (answer);
}

void	ShellGame::shellRoutine(void)
{
	string	input;
	Move	move;

	if (_blindMode == false)
		_board->printBoard(_aiSide);

	while (_board->isGameOver() == false)
	{
		_board->printEvent(_checker->fail(), _board->fail(), _blindMode);
		input = getShellAnswer();
		if (input == "error")
			throw runtime_error("getline() failed.");
		if (input == "end" || input == "error")
			return ;

		*_checker = input;
		move = _checker->getParsedMove();

		if (_checker->fail() == true || _board->playMove(move) == 1)
			continue ;

		if (_blindMode == false)
			_board->printBoard(_aiSide);
		_checker->setTurn(_board->getActualTurn());
	}
	_board->printEndGame();
}
