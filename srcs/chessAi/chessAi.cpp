#include "chessAi.hpp"

chessAi::chessAi(void)
{
	_stream = popen("stockfish", "w");
	if (_stream == NULL || _stream == nullptr)
		_fail = true;
	else
		_fail = false;
}

void	chessAi::sendCommand(const string command)
{
	string	cmd;
	
	cmd = command + '\n';
	fprintf(_stream, "%s", cmd.c_str());

	cout << "sending '" << cmd << "'" << endl;
}

string	chessAi::getAnswer(void)
{
	string	answer;

	return (answer);
}

string	chessAi::getBestAnswer(vector<string> moves)
{
	string	move;
	string	command;

	command = "position startpos moves ";
	for (int i = 0; i != moves.size(); i++)
	{
		move = moves.at(i);
		if (move.size() == 5)
			move[4] = tolower(move[4]);
		command += " " + move;
	}

	sendCommand(command);

	command += "go movetime 500";
	sendCommand(command);

	return (getAnswer());
}

bool	chessAi::fail(void) const
{
	if (_fail == true)
		return (true);
	return (false);
}

chessAi::~chessAi(void)
{
	if (_stream != nullptr && _stream != NULL)
		pclose(_stream);
}
