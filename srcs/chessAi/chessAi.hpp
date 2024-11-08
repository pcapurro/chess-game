#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

class chessAi
{
	public:
		static string	getNextMove(const chessBoard *board, const int aiSide);

	private:
		chessAi(void);
		~chessAi(void);
};

#endif