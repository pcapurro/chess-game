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

string	chessAi::getBestMove(vector<string> moves)
{
	string	history, command;
	string	word, move, bestMove;

	for (int i = 0; i != moves.size(); i++)
		history += moves.at(i) + " ";

	command = "position startpos moves " + history;
	fprintf(_stream, "%s\n", command.c_str());
	command = "go movetime 500";
	fprintf(_stream, "%s\n", command.c_str());

	fflush(_stream);
	sleep(1);

	move = (stringstream() << _line.rdbuf()).str();

	int i = 0;
	while (i != move.size() && word != "bestmove")
	{
		if (move[i] == ' ' || move[i] == '\n')
			word.clear();
		else
			word += move[i];
		i++;
	}

	move = move.c_str() + i + 1;
	for (int i = 0; move[i] != ' ' && move[i] != '\n' && move[i] != '\0'; i++)
		bestMove += move[i];

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
