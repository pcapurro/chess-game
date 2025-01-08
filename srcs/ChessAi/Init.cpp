#include "ChessAi.hpp"

ChessAi::ChessAi(void)
{
	_fail = false;

	if (system("stockfish < /dev/null > /dev/null 2>&1") != 0)
	{
		_fail = true;
		systemFailed(false, "Stockfish not found.");
		return ;
	}

	_answer = ofstream(".stockfish.answer");
	_line = ifstream(".stockfish.answer");

	if (!_answer || !_line)
	{
		_fail = true;
		systemFailed(false, "ofstream/ifstream failed.");
		return ;
	}

	string	command = "stockfish > .stockfish.answer";
	_stream = popen(command.c_str(), "w");
	if (!_stream)
	{
		_fail = true;
		_stream = nullptr;
		systemFailed(false, "popen() failed.");
		return ;
	}

	command = "uci";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		_fail = true, systemFailed(false, "Stockfish failed.");

	command = "setoption name UCI_LimitStrength value true";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		_fail = true, systemFailed(false, "Stockfish failed.");

	srand(time(nullptr));
	int 	value = rand() % 7;
	string	elo[] = {"1400", "1500", "1600", "1700", "1800", "1900, 2000"};

	command = "setoption name UCI_Elo " + elo[value];
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		_fail = true, systemFailed(false, "Stockfish failed.");
}
