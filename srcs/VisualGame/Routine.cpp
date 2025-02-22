#include "VisualGame/VisualGame.hpp"

std::string	VisualGame::getVisualAnswer(void)
{
	std::string	answer;

	if (_sandBoxMode == false && _visualInfo.turn % 2 == _visualInfo.aiSide)
	{
		answer = _ai->getBestMove(_board->getHistory());
		
		answer = _board->getType({answer[0], answer[1]}) + answer;

		if (answer == "Ke1g1" || answer == "Ke8g8")
			answer = "O-O";
		if (answer == "Ke1c1" || answer == "Ke8c8")
			answer = "O-O-O";

		if (answer.find('O') == std::string::npos)
			displayMoveAnimation(answer.c_str() + 1);
	}
	else
		answer = waitForEvent();

	return (answer);
}

int	VisualGame::visualLoop(void)
{
	std::string	answer;

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
			if (_board->playMove({}, answer) == 1)
				continue ;
			_visualInfo.lastMove = answer.c_str() + 1;
		}

		if (_visualInfo.evaluation == true)
		{
			displayGame(true);
			_visualInfo.whiteScore = _board->getScore("white");
			_visualInfo.blackScore = _board->getScore("black");
		}

		_visualInfo.turn++;
	}
	displayGame(true);
	_board->printEndGame(1);

	return (0);
}

void	VisualGame::visualRoutine(void)
{
	while (true)
	{
		_board = new (std::nothrow) ChessBoard;

		int	value = visualLoop();

		delete _board, _board = nullptr;
		if (value == 2)
			return ;
			
		setToDefault();
		if (value != 4 && waitForNewGame() == "end")
			break ;
	}
}
