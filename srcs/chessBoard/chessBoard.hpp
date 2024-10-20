#ifndef CHESSBOARD
# define CHESSBOARD

# include <iostream>

# include "../algebraicParser/algebraicParser.hpp"

# include "pieces/chessPiece.hpp"
# include "pieces/king.hpp"
# include "pieces/queen.hpp"
# include "pieces/bishop.hpp"
# include "pieces/knight.hpp"
# include "pieces/rook.hpp"
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

        bool    fail(void) const;
        bool    isAllocated(void) const;

        int     getActualTurn(void) const;

        bool    isGameOver(void);
        int     playMove(t_move move);

        void    announceEvent(const int value, const bool cfail = false, \
                                const bool bfail = false, const string move = "none");

        void    printBoard(void); //

    private:

        void    setTurn(void);
        void    changeColor(void);

        bool    checkBoardAllocation(void) const;

        void    initRooksKnights(void);
        void    initBishops(void);
        void    initQueensKings(void);
        void    initBoard(void);

        size_t  getAtValue(const string coord) const;

        void    promotePiece(const string initialCoord, char pieceType);
        void    movePiece(const string initialCoord, const string newCoord);
        void    removePiece(const string coord);

        void    priseEnPassant(void);
        
        void    whiteCastles(void);
        void    blackCastles(void);

        void    printIllegal(void) const;
        bool    isLegal(void);

        int     checkSource(void);
        int     checkPawnDestintation(void);
        
        bool    isThereValidDestintation(void);
        bool    isItValidDestination(void);

        bool    isThereSomething(const string coord) const;
        
        bool    isThereAlly(void);
        bool    isRightSide(void);
        bool    isThereAttacker(void);

        bool    isTheDestinationSafe(void);
        bool    isCastlingPossible(void) const;

        bool    doesItResolveCheck(const string srcdest);
        bool    isCheck(void);
        bool    isCheckMate(void);

        bool    isDraw(void);
        bool    canTheKingMove(void);
        bool    canAnyAllyPieceMove(void);
        bool    isCheckMateImpossible(void);

        vector<string>      getPossibleMoves(const string coord);
        vector<string>      getPiecesCoords() const;

        void    countPiecesOnBoard(void);

        void    enableDisableEnPassant(void);

        vector<t_square>    _board;
        bool                _allocated;

        t_move              _lastMove;

        bool                _whiteCastle;
        bool                _blackCastle;

        bool                _enPassant;
        string              _enPassantDest;

        int                 _turn;
        string              _color;

        t_counter           _boardCount;
    
        bool                _moveFailed;
};

#endif