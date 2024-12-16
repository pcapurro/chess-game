#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../../includes/game.hpp"

class chessAi
{
	public:

		chessAi(void);
		~chessAi(void);

		string	getBestAnswer(vector<string> moves);

		void	sendCommand(const string command);
		string	getAnswer(void);

		bool	fail(void) const;
	
	private:

		bool		_fail;
		FILE 		*_stream;
};

#endif