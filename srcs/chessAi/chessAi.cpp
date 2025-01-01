#include "chessAi.hpp"

chessAi::chessAi(void)
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

	string command = "stockfish > .stockfish.answer";
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

string	chessAi::getBestMove(vector<string> moves) const
{
	string	history, command;
	string	word, move, bestMove;

	for (size_t i = 0; i != moves.size(); i++)
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

	size_t k = 0;
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

	if (bestMove.size() == 5)
		bestMove[4] = toupper(bestMove[4]);

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
