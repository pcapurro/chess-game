#include "ChessAi/ChessAi.hpp"

ChessAi::~ChessAi(void)
{
	if (_line)
		_line.close();
	if (_answer)
		_answer.close(), remove(".stockfish.answer");

	if (_stream != nullptr)
		pclose(_stream);
}
