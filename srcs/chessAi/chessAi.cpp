#include "chessAi.hpp"

chessAi::chessAi(void)
{
	_stream = popen("stockfish | grep 'bestmove'", "w");
	if (_stream == NULL || _stream == nullptr)
		_fail = true;
	else
		_fail = false;
}

void	chessAi::sendCommand(const string command)
{
	string	cmd;

	cout << "sending > '" << command << "'" << endl;

	cmd = command + '\n';
	fprintf(_stream, "%s", cmd.c_str());
}

string	chessAi::getAnswer(void)
{
	char	str[4096];
	string	answer;

	fgets(str, 4096, _stream);
	cout << "answer > '" << str << "'" << endl;

	return (answer);
}

string	chessAi::getBestAnswer(vector<string> moves)
{
	string	move;
	string	command;

	if (moves.size() != 0)
	{
		command = "position startpos moves";
		for (int i = 0; i != moves.size(); i++)
		{
			move = moves.at(i);
			if (move.size() == 5)
				move[4] = tolower(move[4]);
			command += " " + move;
		}

		sendCommand(command);
	}

	sendCommand("go movetime 500");
	sleep(1);

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
