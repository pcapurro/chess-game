#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

class chessAi : protected chessBoard
{
	public:

		chessAi(const chessBoard *board);
		~chessAi(void) {};

		string	getNextMove(void);

	private:

        void        analyzeBoard(void);

		void		checkMateMove(void);
		void		attackMove(void);
		void		passiveMove(void);
		void		defendMove(void);
		void		endGameMove(void);
		void		randomMove(void);

        int         getAttackedNumber(void);

        bool        isProtected(const string coord);
        bool        isAttacked(const string coord);
        bool        isAttackedByPawn(const string coord);

        bool        isAllyAttacked(void);
        bool        isSomethingNotProtected(void);

        bool        isVictoryNextNext(void);
        bool        isVictoryNext(void);
        bool        isDefeatNext(void);
        bool        isEndGame(void);

        bool        equalValues(const string move);
        int         getMaterialValue(const char type);

		stack<chessPiece *> orderMaterialsByValue(vector<chessPiece *> materials);

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

		string		    _nextMove;

        string          _attackMove;

        bool            _victoryNextNext;
        bool            _defeatNext;
        bool            _allyAttacked;
        bool            _check;

        vector<chessPiece *>  _attackedAlly;
};

#endif