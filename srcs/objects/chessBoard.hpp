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

class chessBoard
{
    public:

        chessBoard();
        ~chessBoard();

        bool    isAllocated(void) const;

        bool    fail(void) const;

        bool    isCheck() const;
        bool    isCheckMate() const;

        bool    isLegal(const string move);

        void    announceEvent(const int value, const bool cfail = false, \
                                const bool bfail = false, const string move = "none");
        void    playMove(const string move);

        void    printBoard(void) const;

    private:

        bool        _allocated;
        chessPiece  **_board;

        int         _turn;
        bool        _moveFailed;
        string      _player;
};

#endif