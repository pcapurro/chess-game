#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# include "../chessBoard/chessBoard.hpp"

typedef chessPiece      cP;

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
        bool        isFree(const string coord);
        bool        isAttacked(const string coord);
        bool        isMoveWorth(const string move);
        bool        isAttackedByPawn(const string coord);

        bool        isAllyAttacked(void);
        bool        isDefenseWorth(void);
        bool        isSomethingAttacked(void);

        bool        equalValues(const string move);

        bool        checkMateInTwo(void);
        bool        checkMateInOne(void);
        bool        isDefeatNext(void);

        int             getAttackedNumber(void);
        int             getWatchersNumber(const string coord);
        int             getMaterialValue(const char type);
        string          sortCounterCheckMoves(vector<string> legalMoves);
        stack<cP *>     orderMaterialsByValue(stack<cP *> materials);
        stack<cP *>     getEnemyTargets(void);

        stack<cP *>     getWatchers(const string coord);

        string		    preventCastling(const string castle);
        string	        getBestAttack(stack<cP *> targets);
        string          getPromotion(void);
        string	        getPromotionNow(void);
        string	        getThreat(void);
        string          getExchange(void);

        string		    getCheckMateInOneMove(void);
        string          getCheckMateInTwoMove(void);

        string		    getPawnsOpening(void);
        string          getPawnsDev(void);
        string		    getCastling(void);
        string		    getBishopsDev(void);
        string		    getKnightsDev(void);
        string		    getPassiveMove(void);
        string          getRandomDev(void);

        string		    getCounterStrike(void);

        string          getCounterCheckMate(const int value);
        string		    getCounterProtect(void);

        string		    getRandomMove(void);

		string		    _nextMove;

        bool            _checkMateInOne;
        bool            _checkMateInTwo;
        bool            _defeatNext;
        bool            _allyAttacked;
        bool            _check;

        string          _attackMove;
};

#endif