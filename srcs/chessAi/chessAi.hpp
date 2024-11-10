#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

# define P 1
# define N 3
# define B 3
# define R 5
# define Q 9

class chessAi
{
	public:

		chessAi(const chessBoard *board) : _newBoard(board) {};
		~chessAi(void) {};

		string	getNextMove(void);

	private:

		void	checkMateMove(void);
		void	attackMove(void);
		void	passiveMove(void);
		void	defendMove(void);
		void	endGameMove(void);
		void	randomMove(void);

		string			_nextMove;

		chessBoard		_newBoard;

};

#endif