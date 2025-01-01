#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../../includes/game.hpp"

class chessAi
{
	public:

		chessAi(void);
		~chessAi(void);

		string	getBestMove(vector<string> moves) const;

		bool	fail(void) const { return (_fail); };
	
	private:

		bool		_fail;

		ofstream	_answer;
		ifstream	_line;

		FILE		*_stream;
};

#endif