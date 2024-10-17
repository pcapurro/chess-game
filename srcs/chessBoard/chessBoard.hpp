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

# define getParsedMove checker.getObject(), \
    checker.checkSource(), checker.getDest()

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

        bool    isCheckMate() const;
        bool    isLegal(const char obj, const string src, const string dest);
        void    playMove(const char obj, const string src, const string dest, const string move);

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

        void    printIllegal(void) const;

        string  checkSource(const char type, const string src);

        bool    isCheck() const;

        vector<t_square>    _board;
        bool                _allocated;

        int                 _turn;
        bool                _moveFailed;
        string              _player;
};

#endif