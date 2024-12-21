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
	string	word, move;

	for (int i = 0; i != moves.size(); i++)
		history += moves.at(i) + " ";

	command = "position startpos moves " + history;
	fprintf(_stream, "%s\n", command.c_str());
	command = "go movetime 500";
	fprintf(_stream, "%s\n", command.c_str());

	fflush(_stream);
	sleep(1);

	cout << "'" << move << "'" << endl;

	return (move);
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
