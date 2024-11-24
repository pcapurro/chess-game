#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

typedef chessPiece cP;

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

        bool        isProtected(const string coord);
        bool        isAttacked(const string coord);
        bool        isAttackedByPawn(const string coord);

        bool        isAllyAttacked(void);
        bool        isDefenseWorth(void);
        bool        isSomethingNotProtected(void);

        bool        equalValues(const string move);

        bool        isVictoryNextNext(void);
        bool        isVictoryNext(void);
        bool        isDefeatNext(void);
        bool        isEndGame(void);

        int             getAttackedNumber(void);
        int             getMaterialValue(const char type);
        string		    getBestCounterMateCheck(vector<string> legalMoves);
        vector<cP *>    getTargets(void);
        stack<cP *>     orderMaterialsByValue(vector<cP *> materials);

        string		    preventCastling(const string castle);
        string	        getBestAttacker(vector<cP *> targets);
        string	        getThreat(void);

        string		    getCheckMateMove(void);

        string		    getPawnsOpening(void);
        string          getPawnsDev(void);
        string		    getCastling(void);
        string		    getBishopsDev(void);
        string		    getKnightsDev(void);
        string		    getPassiveMove(void);

        string		    getCounterStrike(void);

        string		    getCounterCheck(void);
        string		    getCounterCheckMate(void);
        string		    getCounterProtect(void);

        string		    getRandomMove(void);

		string		    _nextMove;

        string          _attackMove;

        bool            _victoryNextNext;
        bool            _defeatNext;
        bool            _allyAttacked;
        bool            _check;

        vector<cP *>    _attackedAlly;
};

#endif