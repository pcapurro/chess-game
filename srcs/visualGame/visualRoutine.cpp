#include "visualGame.hpp"

#include "../chessAi/chessAi.hpp"

string	visualGame::getVisualAnswer(void)
{
	string	answer;

	if (_sandBoxMode == false && visualInfo._turn % 2 == visualInfo._aiSide)
	{
		answer = _ai->getBestMove(_board->getHistory());
		if (answer == "error")
			{ systemFailed(true, "Stockfish failed."); return ("error"); }
		answer = _board->getType({answer[0], answer[1]}) + answer;

		if (answer == "Ke1g1" || answer == "Ke8g8")
			answer = "O-O";
		if (answer == "Ke1c1" || answer == "Ke8c8")
			answer = "O-O-O";

		if (answer.find('O') == string::npos)
			displayMoveAnimation(answer.c_str() + 1);
	}
	else
		answer = waitForEvent();

	return (answer);
}

int	visualGame::visualLoop(void)
{
	string	answer;

	while (_board->isGameOver() == false)
	{
		displayGame(true);

		answer = getVisualAnswer();
		if (answer == "error" || answer == "restart" \
			|| answer == "end")
		{
			if (answer == "error")
				return (3);
			if (answer == "restart")
				return (4);
			if (answer == "end")
				{ _board->printEndGame(1); return (2); }
		}
		else
		{
			if (_board->playMove({}, answer) == FAIL)
				continue ;
			visualInfo._lastMove = answer.c_str() + 1;
			
			if (_board->isAllocated() == false)
				return (1);
		}

		if (visualInfo._evaluation == true)
		{
			displayGame(true);
			visualInfo._whiteScore = _board->getScore("white");
			visualInfo._blackScore = _board->getScore("black");
		}

		visualInfo._turn++;
	}
	displayGame(true);
	_board->printEndGame(1);

	return (0);
}

void	visualGame::visualRoutine(void)
{
	if (fail() == true)
		return ;

	while (1)
	{
		_board = new (nothrow) chessBoard;
		if (!_board || _board == nullptr \
			|| _board->isAllocated() == false)
			_error = true, memoryFailed(false);

		if (_error == true)
			return ;

		int	value = visualLoop();

		delete _board, _board = nullptr;
		if (value == 1 || value == 3)
		{
			_error = true;
			if (value == 1)
				memoryFailed(false);
			return ;
		}
		if (value == 2)
			return ;
			
		setToDefault();
		if (value != 4 && waitForNewGame() == "end")
			break ;
	}
}
