#include "chessAi.hpp"

chessAi::chessAi(void)
{
	_stream = popen("stockfish", "w");
	if (_stream == NULL || _stream == nullptr)
		_fail = true;
	else
	{
		char str[21];

		fgets(str, 21, _stream);
		cout << "'" << str << "'" << endl;

		fprintf(_stream, "uci\n");
		fprintf(_stream, "go movetime 1000\n");

		fgets(str, 21, _stream);
		cout << "'" << str << "'" << endl;
	}
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
