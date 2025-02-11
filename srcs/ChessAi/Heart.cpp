#include "ChessAi.hpp"

string	ChessAi::getBestMove(const vector<string>& moves) const
{
	string	history, command;
	string	word, move, bestMove;

	for (size_t i = 0; i != moves.size(); i++)
		history += moves.at(i) + " ";

	command = "position startpos moves " + history;
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw runtime_error("Stockfish failed.");
	
	command = "go movetime 500";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		throw runtime_error("Stockfish failed.");
	else
		fflush(_stream);
	
	sleep(1);

	if (_answer.good() == true && _line.good() == true)
		move = (stringstream() << _line.rdbuf()).str();
	if (move == "")
		throw runtime_error("Stockfish failed.");

	size_t	k = 0;
	while (k != move.size() && word != "bestmove")
	{
		if (move[k] == ' ' || move[k] == '\n')
			word.clear();
		else
			word += move[k];
		k++;
	}

	move = move.c_str() + k + 1;
	for (int i = 0; move[i] != ' ' && move[i] != '\n' && move[i] != '\0'; i++)
		bestMove += move[i];

	if (bestMove.size() == 0 || bestMove.size() > 5)
		throw runtime_error("Stockfish failed.");

	if (bestMove.size() == 5)
		bestMove[4] = toupper(bestMove[4]);

	return (bestMove);
}
