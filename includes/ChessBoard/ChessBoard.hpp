#ifndef CHESSBOARD_HPP
# define CHESSBOARD_HPP

# include "Game.hpp"
# include "ChessBoard/ChessObjects.hpp"

typedef	ChessPiece cP;

class ChessBoard
{
	public:

		ChessBoard(void);
		~ChessBoard(void) = default;

		bool	fail(void) const
			{ return (_gameInfo.moveFailed); };

		int		getScore(const std::string color);

		char	getType(const std::string& coord) const;
		std::string	getColor(const std::string& coord) const;

		int		getActualTurn(void) const
			{ return (_gameInfo.turn); };
		int		getStateValue(void) const;

		bool	isLegal(const std::string& move = "");
		bool	isItCheck(void) const
			{ return (_gameInfo.check); };
		bool	isItDraw(void) const
			{ return (_gameInfo.draw); };
		bool	isItCheckMate(void) const
			{ return (_gameInfo.checkmate); }
		bool	isGameOver(void);

		int		playMove(Move structureMove, const std::string& move = "");

		void	printEvent(const bool cfail, const bool bfail, const bool blindMode);
		void	printEndGame(const int value = 0);
		void	printBoard(const int aiSide) const;

		int		getWhiteMaterialsScore(void) const
			{ return (_boardCount.whiteMaterial); };
		int		getBlackMaterialsScore(void) const
			{ return (_boardCount.blackMaterial); };

		const std::vector<std::string>&	getHistory(void) const
			{ return (_simpleHistory); };
		std::vector<char>	getWhiteCaptured(void) const
			{ return (_whiteCaptured); };
		std::vector<char>	getBlackCaptured(void) const
			{ return (_blackCaptured); };

		std::vector<std::string>	getLegalMoves(void);

	private:

		size_t	getAtValue(const std::string& coord) const;
		std::string	getEnPassantTarget(void) const;

		std::vector<std::string>	getPossibleTargets(const std::string& coord) const;
		std::vector<std::string>	getPiecesCoords(void) const;
		std::vector<std::string>	getCastlingSrcsDests(const std::string& srcdest) const;

		std::stack<cP*>	orderByValue(std::stack<cP*> materials) const;
		std::stack<cP*>	getWatchers(const std::string& coord);

		int		getWatchersNumber(const std::string& coord) const;
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

		bool	isSafe(const std::string& coord);
		bool	isProtected(const std::string& coord);
		bool	isFree(const std::string& coord);
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

		bool	isThereSomething(const std::string& coord) const;
		bool	isThereAlly(void) const;
		bool	isRightSide(void) const;
		bool	isTheDestinationSafe(void) const;
		bool	isCastlingPossible(const std::string& castle);

		bool	doesItResolveCheck(const std::string& srcdest);
		bool	isCheckMateImpossible(void);
		bool	canTheKingMove(void);
		bool	canAnyAllyPieceMove(void);

		bool	isCheck(void);
		bool	isCheckMate(const int value = 0);
		bool	isDraw(void);

		void	switchPlayers(void);
		void	unSwitchPlayers(void);

		void	tryMove(const std::string& srcdest);
		void	undoMove(const std::string& srcdest);
		void	tryEnPassant(const std::string& srcdest);
		void	undoEnPassant(const std::string& srcdest);
		void	enableCastling(const std::string& srcdest);
		void	disableCastling(const std::string& srcdest);

		void	loadMove(const std::string& move);

		void	printWhiteBoard(void) const;
		void	printBlackBoard(void) const;
		void	printPiece(const char type, const std::string& color) const;
		void	printHistory(void) const;
		void	addToHistory(void);

		void	initRooksKnights(void);
		void	initBishops(void);
		void	initQueensKings(void);
		void	initBoard(void);

		void	priseEnPassant(void);
		void	enableDisableEnPassant(void);
		void	whiteCastles(void);
		void	blackCastles(void);

		void	promotePiece(const std::string& initialCoord, char pieceType);
		void	movePiece(const std::string& initialCoord, const std::string& newCoord);
		void	removePiece(const std::string& coord);

		void	countPiecesOnBoard(void);
		void	countTotalMaterials(void);
		void	resetCount(void);

		std::vector<Square>	_board;
		GameInfo		_gameInfo;

		Counter			_boardCount;
		std::vector<char>	_whiteCaptured;
		std::vector<char>	_blackCaptured;

		std::vector<std::string>	_history;
		std::vector<std::string>	_simpleHistory;

		std::stack<cP*>		_savedObjects;
};

#endif