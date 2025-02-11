#include "ChessAi.hpp"

ChessAi::ChessAi(void)
{
	if (system("stockfish < /dev/null > /dev/null 2>&1") != 0)
		throw runtime_error("Stockfish not found.");

	_answer = ofstream(".stockfish.answer");
	_line = ifstream(".stockfish.answer");

	string	command = "stockfish > .stockfish.answer";
	_stream = popen(command.c_str(), "w");
	if (!_stream)
		throw runtime_error("popen() failed.");

	command = "uci";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw runtime_error("Stockfish failed.");

	command = "setoption name UCI_LimitStrength value true";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw runtime_error("Stockfish failed.");

	srand(time(nullptr));
	int 	value = rand() % 7;
	string	elo[] = {"1400", "1500", "1600", "1700", "1800", "1900, 2000"};

	command = "setoption name UCI_Elo " + elo[value];
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw runtime_error("Stockfish failed.");
}
