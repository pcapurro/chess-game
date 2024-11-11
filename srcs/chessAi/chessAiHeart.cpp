#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "checkmate move" << endl;
	_nextMove = _newBoard.getCheckMateMove();
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
	
	_nextMove = _newBoard.getCounterStrike();
	cout << "searching for attack move" << endl;

	if (_nextMove == "")
		cout << "no attack found" << endl;
	else
		cout << "attack found > " << _nextMove << endl;
}

void	chessAi::passiveMove(void)
{
	if (_nextMove != "")
		return ;

	_nextMove = _newBoard.getPassiveMove();
	cout << "passive move" << endl;
}

void	chessAi::defendMove(void)
{
	if (_nextMove != "")
		return ;

	if (_newBoard.isCheck() == true)
	{
		cout << "counter check" << endl;
		_nextMove = _newBoard.getCounterCheck();
		return ;
	}
	else
	{
		if (_newBoard.isDefeatNext() == true)
		{
			cout << "counter checkmate" << endl;
			_nextMove = _newBoard.getCounterCheckMate();

			if (_nextMove == "")
				cout << "no counter checkmate move found, attacking..." << endl, attackMove(), passiveMove();

			return ;
		}
	}

	cout << "ally defend move" << endl;
	if (_newBoard.isAllyAttacked() == true)
		_nextMove = _newBoard.getCounterProtect();

	if (_nextMove == "")
		attackMove(), passiveMove();
}

void	chessAi::endGameMove(void)
{
	if (_nextMove != "")
		return ;

	cout << "end game move" << endl;
}

void	chessAi::randomMove(void)
{
	if (_nextMove != "")
		return ;

	cout << "random move" << endl;
	_nextMove = _newBoard.getRandomMove();
}

string	chessAi::getNextMove(void)
{
	// sleep(1); //

	vector<string>	legalMoves;
	legalMoves = _newBoard.getLegalMoves();
	cout << "legal moves: " << endl;
	for (int i = 0; i != legalMoves.size(); i++)
		cout << legalMoves.at(i) << " ; ";
	cout << endl;

	if (_newBoard.isCheck() == true)
		defendMove();
	else
	{
		if (_newBoard.isVictoryNext() == true)
			checkMateMove();
		else
		{
			// if (_newBoard.isDefeatNext() == true || _newBoard.isAllyAttacked() == true)
			// 	defendMove();
			// else
			// {
				if (_newBoard.isEndGame() == true)
					endGameMove();
				else
				{
					attackMove();
					passiveMove();
				}
			// }
		}
		randomMove();
	}

    if (_nextMove == "O-O" || _nextMove == "O-O-O")
    {
        if (_newBoard._gameInfo._color == "white")
            _nextMove = "Ke1" + _nextMove;
        else
            _nextMove = "Ke8" + _nextMove;
    }

	return (_nextMove);
}
