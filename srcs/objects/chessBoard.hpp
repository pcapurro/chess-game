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

        bool    isCheck() const;
        bool    isCheckMate() const;

        bool    isLegal(const string move) const;
        bool    isValid(const string move) const;

        void    announceEvent(const int value, const bool fail = false, \
                                const string move = "none");
        void    playMove(const string move);

    private:

        chessPiece  ***_board;

        int         _turn;
        string      _player;
};

#endif