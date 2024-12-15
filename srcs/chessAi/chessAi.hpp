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

		chessAi(const chessBoard *board) : chessBoard(board) {};
		~chessAi(void) {};

		string	    getNextMove(void);
        int		    getScore(const string color, const bool simulation);
        string      getBestAnswer(void);

	private:

        int             getWatchersNumber(const string coord);
        int             getMaterialValue(const char type);
        string          getEnPassantTarget(void);

        stack<cP *>     orderByValue(stack<cP *> materials);
        stack<cP *>     getWatchers(const string coord);

        int		    evaluateMaterial(const bool simulation);

        int         evaluateDefense(void);
        int		    evaluateAttack(void);
        int         evaluateThreats(void);

        int		    evaluateKingControl(const bool simulation);
        int		    evaluateKingDefense(void);

        int         evaluateMobility(void);
        int         evaluatePromotion(void);
        int         evaluatePawns(void);

        int		    evaluateCenter(void);
        int         evaluateDev(void);

        bool        isSafe(const string coord);
        bool        isProtected(const string coord);
        bool        isFree(const string coord);

        bool        isEndGame(void);
        bool        isDefeatNext(void);

        bool        checkMateInOne(void);
};

#endif