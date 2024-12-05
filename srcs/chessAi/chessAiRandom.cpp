#include "chessAi.hpp"

string  chessAi::getRandomLogicMove(void)
{
    vector<string>  legalMoves;
    string          move;
    int             value;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        if (isMoveWorth(move) == true)
            break ;
    }

    if (move[0] == 'P' && move.size() == 6)
        move[5] = 'Q';

    return (move);
}


string  chessAi::getRandomMove(void)
{
    vector<string>  legalMoves;
    string          move;
    int             value;

    legalMoves = getLegalMoves();
    srand(time(nullptr));

	value = rand() % legalMoves.size();
	move = legalMoves.at(value);

    if (move[0] == 'P' && move.size() == 6)
        move[5] = 'Q';

    return (move);
}
