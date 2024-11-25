#include "chessAi.hpp"

string  chessAi::getRandomMove(void)
{
    vector<string>  legalMoves;
    string          move;
    int             value;

    legalMoves = getLegalMoves();
    srand(time(nullptr));

	value = rand() % legalMoves.size();
	move = legalMoves.at(value);

    if (move.size() == 6)
        move[5] = 'Q';

    return (move);
}
