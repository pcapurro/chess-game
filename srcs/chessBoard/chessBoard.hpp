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

class chessBoard
{
    public:

        chessBoard(void);
        ~chessBoard(void);

        bool    isAllocated(void) const;
        bool    fail(void) const;

        int     getActualTurn(void) const;

        bool    isCheckMate() const;
        int     playMove(t_move move);

        void    announceEvent(const int value, const bool cfail = false, \
                                const bool bfail = false, const string move = "none");

        void    printBoard(void); //

    private:

        bool    checkBoardAllocation(void) const;

        void    initRooksKnights(void);
        void    initBishops(void);
        void    initQueensKings(void);
        void    initBoard(void);

        size_t  getAtValue(const string coord) const;

        void    promotePiece(const string initialCoord, char pieceType);
        void    removePiece(const string coord);
        void    priseEnPassant(const string initialCoord, const string newCoord);
        void    movePiece(const string initialCoord, const string newCoord);
        
        void    whiteCastles(void);
        void    blackCastles(void);

        void    printIllegal(void) const;
        bool    isLegal(void);

        int     checkSource(void);
        int     checkPawnDestintation(void);
        
        bool    isThereValidDestintation(void);
        bool    isItValidDestination(void);
        
        bool    isThereAlly(const string coord);
        bool    isRightSide(const string coord);
        bool    isThereAttacker(void);
        bool    isThereSomething(const string coord);

        bool    isOnPawnPath(const string src, const string dest);

        string  getQueenPath(const string src, const string dest);
        string  getPawnPath(const string src, const string dest);
        string  getBishopPath(const string src, const string dest);
        string  getRookPath(const string src, const string dest);
        bool    isTheWayClear(const char type, const string src, \
                                const string dest);

        bool    isTheDestinationSafe(void);

        bool    isCastlingPossible(void) const;
        bool    willItCheck(void) const;
        bool    isCheck(void) const;

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
    
        bool                _moveFailed;
};

#endif