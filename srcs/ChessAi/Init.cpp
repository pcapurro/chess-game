#include "ChessAi/ChessAi.hpp"

ChessAi::ChessAi(void)
{
	if (system("stockfish < /dev/null > /dev/null 2>&1") != 0)
		throw std::runtime_error("Stockfish not found.");

	_answer = std::ofstream(".stockfish.answer");
	_line = std::ifstream(".stockfish.answer");

	std::string	command = "stockfish > .stockfish.answer";
	_stream = popen(command.c_str(), "w");
	if (!_stream)
		throw std::runtime_error("popen() failed.");

	command = "uci";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw std::runtime_error("Stockfish failed.");

	command = "setoption name UCI_LimitStrength value true";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw std::runtime_error("Stockfish failed.");

	srand(time(nullptr));
	int 	value = rand() % 7;
	std::string	elo[] = {"1400", "1500", "1600", "1700", "1800", "1900, 2000"};

	command = "setoption name UCI_Elo " + elo[value];
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw std::runtime_error("Stockfish failed.");
}
