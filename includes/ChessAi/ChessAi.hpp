#pragma once

#include "Game.hpp"

class ChessAi
{
	private:
		std::ofstream	_answer;
		std::ifstream	_line;

		FILE*			_stream;

	public:
		ChessAi(void);
		~ChessAi(void);

		string	getBestMove(const vector<string>& moves) const;
};
