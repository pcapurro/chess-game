#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "Game.hpp"

class ChessAi
{
	public:

		ChessAi(void);
		~ChessAi(void);

		string	getBestMove(const vector<string>& moves) const;
	
	private:

		std::ofstream	_answer;
		std::ifstream	_line;

		FILE*			_stream;
};

#endif
