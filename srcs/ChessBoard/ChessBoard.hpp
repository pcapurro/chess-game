#ifndef CHESSBOARD_HPP
# define CHESSBOARD_HPP

# include "../../includes/Game.hpp"
# include "ChessObjects.hpp"

typedef	ChessPiece cP;

class ChessBoard
{
	public:

		ChessBoard(void);
		~ChessBoard(void);

		bool	fail(void) const
			{ return (_gameInfo.moveFailed); };
		bool	isAllocated(void) const
			{ return (_allocated); }

		int		getScore(const string color);

		char	getType(const string& coord) const;
		string	getColor(const string& coord) const;

		int		getActualTurn(void) const
			{ return (_gameInfo.turn); };
		int		getStateValue(void) const;

		bool	isLegal(const string& move = "");
		bool	isItCheck(void) const
			{ return (_gameInfo.check); };
		bool	isItDraw(void) const
			{ return (_gameInfo.draw); };
		bool	isItCheckMate(void) const
			{ return (_gameInfo.checkmate); }
		bool	isGameOver(void);

		int		playMove(Move structureMove, const string& stringMove = "");

		void	printEvent(const bool cfail, const bool bfail, const bool blindMode);
		void	printEndGame(const int value = 0);
		void	printBoard(const int aiSide) const;

		int		getWhiteMaterialsScore(void) const
			{ return (_boardCount.whiteMaterial); };
		int		getBlackMaterialsScore(void) const
			{ return (_boardCount.blackMaterial); };

		const vector<string>&	getHistory(void) const
			{ return (_simpleHistory); };
		vector<char>	getWhiteCaptured(void) const
			{ return (_whiteCaptured); };
		vector<char>	getBlackCaptured(void) const
			{ return (_blackCaptured); };

		vector<string>	getLegalMoves(void);

	private:

		size_t	getAtValue(const string& coord) const;
		string	getEnPassantTarget(void) const;

		vector<string>	getPossibleTargets(const string& coord) const;
		vector<string>	getPiecesCoords(void) const;
		vector<string>	getCastlingSrcsDests(const string& srcdest) const;

		stack<cP*>	orderByValue(stack<cP*> materials) const;
		stack<cP*>	getWatchers(const string& coord);

		int		getWatchersNumber(const string& coord) const;
		int		getMaterialValue(const char type) const;

		int		evaluateMaterial(const bool colorSwitch);
		int		evaluateKingControl(const bool colorSwitch);
		int		evaluateKingDefense(const bool colorSwitch);
		int		evaluateDefense(void);
		int		evaluateAttack(void);
		int		evaluateMobility(void);
		int		evaluatePromotion(void);
		int		evaluatePawns(void);
		int		evaluateCenter(void);
		int		evaluateDev(void) const;

		bool	isSafe(const string& coord);
		bool	isProtected(const string& coord);
		bool	isFree(const string& coord);
		bool	isEndGame(void) const;
		bool	isDefeatNext(void);
		bool	checkMateInOne(void);

		int		checkNormalSource(void);
		int		checkPawnSource(void);
		bool	isThereValidSource(void);

		int		checkPawnDest(void) const;
		int		checkNormalDest(void) const;

		bool	isItValidSource(void) const;

		bool	isValidEnPassant(void) const;

		bool	isThereSomething(const string& coord) const;
		bool	isThereAlly(void) const;
		bool	isRightSide(void) const;
		bool	isTheDestinationSafe(void) const;
		bool	isCastlingPossible(const string& castle);

		bool	doesItResolveCheck(const string& srcdest);
		bool	isCheckMateImpossible(void);
		bool	canTheKingMove(void);
		bool	canAnyAllyPieceMove(void);

		bool	isCheck(void);
		bool	isCheckMate(const int value = 0);
		bool	isDraw(void);

		void	switchPlayers(void);
		void	unSwitchPlayers(void);

		void	tryMove(const string& srcdest);
		void	undoMove(const string& srcdest);
		void	tryEnPassant(const string& srcdest);
		void	undoEnPassant(const string& srcdest);
		void	enableCastling(const string& srcdest);
		void	disableCastling(const string& srcdest);

		void	loadMove(const string& move);

		void	printWhiteBoard(void) const;
		void	printBlackBoard(void) const;
		void	printPiece(const char type, const string& color) const;
		void	printHistory(void) const;
		void	addToHistory(void);

		void	initRooksKnights(void);
		void	initBishops(void);
		void	initQueensKings(void);
		void	initBoard(void);

		bool	checkBoardAllocation(void) const;

		void	priseEnPassant(void);
		void	enableDisableEnPassant(void);
		void	whiteCastles(void);
		void	blackCastles(void);

		void	promotePiece(const string& initialCoord, char pieceType);
		void	movePiece(const string& initialCoord, const string& newCoord);
		void	removePiece(const string& coord);

		void	countPiecesOnBoard(void);
		void	countTotalMaterials(void);
		void	resetCount(void);

		bool			_allocated;
		bool			_free;

		vector<Square>	_board;
		GameInfo		_gameInfo;

		Counter			_boardCount;
		vector<char>	_whiteCaptured;
		vector<char>	_blackCaptured;

		vector<string>	_history;
		vector<string>	_simpleHistory;

		stack<cP*>		_savedObjects;
};

#endif