#ifndef CHESSBOARD
# define CHESSBOARD

# include <iostream>

# include "pieces/chessPiece.hpp"
# include "pieces/king.hpp"
# include "pieces/queen.hpp"
# include "pieces/bishop.hpp"
# include "pieces/knight.hpp"
# include "pieces/rook.hpp"
# include "pieces/pawn.hpp"

# define getParsedMove checker.getObject(),\
    checker.getType(), checker.getSource(), \
    checker.getDest()

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
        bool    isLegal(const char obj, const char type, const string src, \
                        const string dest);
        int     playMove(const char obj, const char type, const string src, \
                            const string dest, const string move);

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
        void    movePiece(const string initialCoord, const string newCoord);
        
        void    whiteCastles(const string move);
        void    blackCastles(const string move);

        void    printIllegal(void) const;

        int     checkSource(const char type, const string src, const string dest);
        int     checkPawnDestintation(const string src, const string dest);
        
        bool    isThereValidDestintation(const char obj, const string src, \
                                        const string dest);
        bool    isItValidDestination(const char obj, const string src, \
                                        const string dest);
        
        bool    isThereAlly(const string dest);
        bool    isRightSide(const string src);
        bool    isThereAttacker(const char type);
        bool    isThereSomething(const string dest);

        string  getBishopPath(const string src, const string dest);
        string  getQueenPath(const string src, const string dest);
        string  getRookPath(const string src, const string dest);
        bool    isTheWayClear(const char type, const string src, \
                                            const string dest);

        bool    isCastlingPossible(const string move) const;
        bool    willItCheck(void) const;
        bool    isCheck(void) const;

        void    enableDisableEnPassant(const char obj, const string src, \
                                        const string dest);

        vector<t_square>    _board;
        bool                _allocated;

        string              _src;

        bool                _whiteCastle;
        bool                _blackCastle;

        bool                _enPassant;
        string              _enPassantDest;

        int                 _turn;
        bool                _moveFailed;
        string              _color;
};

#endif