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

using namespace std;

typedef struct s_square
{
    chessPiece  *piece;
    string      coord;

}   t_square;

class chessBoard
{
    public:

        chessBoard();
        ~chessBoard();

        bool    isAllocated(void) const;
        bool    fail(void) const;

        bool    isCheckMate() const;
        bool    isLegal(const string move);
        void    playMove(const string move);

        void    announceEvent(const int value, const bool cfail = false, \
                                const bool bfail = false, const string move = "none");

    private:

        bool    checkBoardAllocation() const;

        void    initRooksKnights();
        void    initBishops();
        void    initQueensKings();
        void    initBoard(void);

        bool    isCheck() const;
        
        int     getCoordinateToX(const char c) const;

        void    printBoard(void) const; //

        vector<t_square>    _board;
        bool                _allocated;

        int                 _turn;
        bool                _moveFailed;
        string              _player;
};

#endif