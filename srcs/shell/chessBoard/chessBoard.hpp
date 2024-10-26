#ifndef CHESSBOARD
# define CHESSBOARD

# include "../../../include/shellChessClassic.hpp"

# include "pieces/chessPiece.hpp"
# include "pieces/king.hpp"
# include "pieces/queen.hpp"
# include "pieces/rook.hpp"
# include "pieces/bishop.hpp"
# include "pieces/knight.hpp"
# include "pieces/pawn.hpp"

using namespace std;

typedef struct s_square
{
    chessPiece  *piece;
    string      coord;

}   t_square;

typedef struct s_counter
{
    int whiteKing;
    int blackKing;

    int whiteQueen;
    int blackQueen;

    int whiteRook;
    int blackRook;

    int whiteBishop;
    int blackBishop;

    int whiteKnight;
    int blackKnight;

    int whitePawn;
    int blackPawn;

    int total;

}   t_counter;

class chessBoard
{
    public:

        chessBoard(void);
        ~chessBoard(void);

        bool    fail(void) const { return (_moveFailed); };
        bool    isAllocated(void) const;

        char    getType(const string coord) const;
        string  getColor(const string coord) const;

        int     getActualTurn(void) const { return (_turn); };

        bool    isGameOver(void);
        int     playMove(t_move move);

        void    printEvent(const bool cfail, const bool bfail,\
                            const int value);
        void    printEndGame(const int value = 0);
        void    printBoard(void) const;

    private:

        size_t              getAtValue(const string coord) const;
        vector<string>      getPossibleMoves(const string coord) const;
        vector<string>      getPiecesCoords(void) const;

        void    printPiece(const char type, const string color) const;

        void    printHistory(void) const;
        void    addToHistory(void);

        void    initRooksKnights(void);
        void    initBishops(void);
        void    initQueensKings(void);
        void    initBoard(void);

        bool    checkBoardAllocation(void) const;

        void    priseEnPassant(void);
        void    enableDisableEnPassant(void);
        void    whiteCastles(void);
        void    blackCastles(void);

        void    promotePiece(const string initialCoord, char pieceType);
        void    movePiece(const string initialCoord, const string newCoord);
        void    removePiece(const string coord);

        int     checkNormalSource(void);
        int     checkPawnSource(void);
        bool    isThereValidSource(void);

        int     checkPawnDest(void) const;
        int     checkNormalDest(void) const;

        bool    isItValidSource(void) const;

        bool    isThereSomething(const string coord) const;
        bool    isThereAlly(void) const;
        bool    isRightSide(void) const;
        bool    isTheDestinationSafe(void) const;
        bool    isCastlingPossible(void) const;

        bool    isLegal(void);

        bool    doesItResolveCheck(const string srcdest);
        bool    isCheckMateImpossible(void);
        bool    canTheKingMove(void);
        bool    canAnyAllyPieceMove(void);

        bool    isCheck(void);
        bool    isCheckMate(void);
        bool    isDraw(void);

        void    countPiecesOnBoard(void);
        void    resetCount(void);

        vector<t_square>    _board;
        bool                _allocated;

        t_move              _lastMove;
        bool                _moveFailed;

        bool                _whiteCastle;
        bool                _blackCastle;
        bool                _enPassant;
        string              _enPassantDest;

        int                 _turn;
        string              _color;

        t_counter           _boardCount;
        vector<string>      _history;
};

#endif