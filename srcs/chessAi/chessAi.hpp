#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

class chessAi : protected chessBoard
{
	public:

		chessAi(const chessBoard *board) : chessBoard(board) {};
		~chessAi(void) {};

		string	getNextMove(void);

	private:

		stack<chessPiece *> orderMaterialsByValue(vector<chessPiece *> materials);

        int			getMaterialValue(const char type);

        string		getBestCounterMateCheck(vector<string> legalMoves);
        string		getCheckMateMove(void);

        string		getPawnsDev(void);
        string		getCastling(void);
        string		getBishopsDev(void);
        string		getKnightsDev(void);
        string		getPassiveMove(void);

        string		preventCastling(const string castle);
        string		getCounterStrike(void);

        string		getCounterCheck(void);
        string		getCounterCheckMate(void);
        string		getCounterProtect(void);
        string		getRandomMove(void);

		void		checkMateMove(void);
		void		attackMove(void);
		void		passiveMove(void);
		void		defendMove(void);
		void		endGameMove(void);
		void		randomMove(void);

        bool    isProtected(const string coord);
        bool    isAttacked(const string coord);
        bool    isAttackedByPawn(const string coord);

        bool    isAllyAttacked(void);
        bool    isSomethingNotProtected(void);

        bool    isVictoryNextNext(void);
        bool    isVictoryNext(void);
        bool    isDefeatNext(void);
        bool    isEndGame(void);

		string		_nextMove;
		chessBoard	_newBoard;

};

#endif