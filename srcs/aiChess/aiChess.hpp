#ifndef AICHESS_HPP
# define AICHESS_HPP

# include "../chessBoard/chessBoard.hpp"

class aiChess
{
	public:
	
		aiChess(void);
		~aiChess(void);

		static string	getNextMove(chessBoard *board, const int aiSide);

	private:
		;
};

#endif