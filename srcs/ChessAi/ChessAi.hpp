#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../../includes/Game.hpp"

class ChessAi
{
	public:

		ChessAi(void);
		~ChessAi(void);

		string	getBestMove(const vector<string>& moves) const;

		bool	fail(void) const { return (_fail); };
	
	private:

		bool		_fail;

		ofstream	_answer;
		ifstream	_line;

		FILE*		_stream;
};

#endif