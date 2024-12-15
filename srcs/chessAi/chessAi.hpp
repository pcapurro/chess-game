#ifndef CHESSAI_HPP
# define CHESSAI_HPP

# define MAX_LEVEL 4

# include "../chessBoard/chessBoard.hpp"

typedef chessPiece      cP;

typedef struct s_path
{
    vector<string>  branch;
    int             score;

}   t_path;

class chessAi : protected chessBoard
{
	public:

		chessAi(const chessBoard *board);
		~chessAi(void) {};

		string	    getNextMove(void);
        int		    getScore(const string color);
        string      getBestAnswer(void);

	private:

        int             getWatchersNumber(const string coord);
        int             getMaterialValue(const char type);
        string          getEnPassantTarget(void);
        string          getRandomAnswer(void);

        stack<cP *>     orderByValue(stack<cP *> materials);
        stack<cP *>     getWatchers(const string coord);

        vector<t_path>  getPaths(void);
        void            evaluatePaths(vector<t_path> &paths);

        int		    evaluateMaterial(void);

        int         evaluateDefense(void);
        int		    evaluateAttack(void);
        int         evaluateThreats(void);

        int		    evaluateKingControl(void);
        int		    evaluateKingDefense(void);

        int         evaluateMobility(void);
        int         evaluatePromotion(void);
        int         evaluatePawns(void);

        int		    evaluateCenter(void);
        int         evaluateDev(void);

        bool        isSafe(const string coord);
        bool        isProtected(const string coord);
        bool        isFree(const string coord);
        bool        isAttacked(const string coord);

        bool        isEndGame(void);
        bool        isDefeatNext(void);

        bool        checkMateInOne(void);

		string      _nextMove;
        bool        _simulation;
};

#endif