#include "chessAi.hpp"

chessAi::chessAi(void)
{
	_fail = false;

	_answer = ofstream(".stockfish.answer");
	_line = ifstream(".stockfish.answer");

	if (!_answer || !_line)
		_fail = true;
	else
	{
		string command = "stockfish > .stockfish.answer";
		_stream = popen(command.c_str(), "w");
		if (!_stream)
			_fail = true, _stream = nullptr;
	}
}

string	chessAi::getBestMove(vector<string> moves) const
{
	string	history, command;
	string	word, move, bestMove;

	for (int i = 0; i != moves.size(); i++)
		history += moves.at(i) + " ";

	command = "position startpos moves " + history;
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		return ("error");
	
	command = "go movetime 500";
	if (fprintf(_stream, "%s\n", command.c_str()) < 0)
		return ("error");
	else
		fflush(_stream);
	
	sleep(1);

	if (_answer.good() == true && _line.good() == true)
		move = (stringstream() << _line.rdbuf()).str();
	if (move == "")
		return ("error");

	int k = 0;
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
		return ("error");

	return (bestMove);
}

bool	chessAi::fail(void) const
{
	if (_fail == true)
		return (true);
	return (false);
}

chessAi::~chessAi(void)
{
	if (_line)
		_line.close();
	if (_answer)
		_answer.close(), remove(".stockfish.answer");

	if (_stream != nullptr)
		pclose(_stream);
}
