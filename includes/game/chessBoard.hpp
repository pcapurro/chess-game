#ifndef CHESS_BOARD
# define CHESS_BOARD

# include <iostream>

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

    private:
};

#endif