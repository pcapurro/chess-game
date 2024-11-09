#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

class chessAi
{
	public:
		static string	getNextMove(const chessBoard *board, const int aiSide);

	private:
		chessAi(void) {};
		~chessAi(void) {};

		static void				checkMateMove(string *nextMove);
		static void				attackMove(string *nextMove);
		static void				passiveMove(string *nextMove);
		static void				defendMove(string *nextMove);
		static void				endGameMove(string *nextMove);
		static void				randomMove(string *nextMove);

		static vector<string>	getLegalMoves(chessBoard *newBoard);

};

#endif