#include "chessAi.hpp"

string  chessAi::getBestAnswer(void)
{
    int             actualScore, bestScore, savedScore = 0;
    string          move, answer, savedAnswer;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    bestScore = getScore(_gameInfo._color, false);

    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (move[0] != 'O')
            move = move.c_str() + 1;

        tryMove(move);

        actualScore = getScore(_gameInfo._color, true);
        if (actualScore > bestScore)
            bestScore = actualScore, answer = legalMoves.at(i);
        if (actualScore > savedScore)
            savedScore = actualScore, savedAnswer = legalMoves.at(i);

        undoMove(move);
    }

    if (answer == "")
        answer = savedAnswer;

	cout << "> " << answer << endl;

    return (answer);
}

string	chessAi::getNextMove(void)
{
	return (getBestAnswer());
}
