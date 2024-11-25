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
        bool        isSomethingAttacked(void);

        bool        equalValues(const string move);

        bool        checkMateInTwo(void);
        bool        checkMateInOne(void);
        bool        isDefeatNext(void);
        bool        isEndGame(void);

        int             getAttackedNumber(void);
        int             getMaterialValue(const char type);
        string		    getBestCounterMateCheck(vector<string> legalMoves);
        stack<cP *>     orderMaterialsByValue(stack<cP *> materials);
        stack<cP *>     getTargets(void);

        stack<cP *>     getOthers(const string coord);

        string		    preventCastling(const string castle);
        string	        getBestAttack(stack<cP *> targets);
        string	        getThreat(void);

        string		    getCheckMateInOneMove(void);
        string          getCheckMateInTwoMove(void);

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

        bool            _endGame;
        bool            _checkMateInOne;
        bool            _checkMateInTwo;
        bool            _defeatNext;
        bool            _allyAttacked;
        bool            _check;

        string          _attackMove;
};

#endif