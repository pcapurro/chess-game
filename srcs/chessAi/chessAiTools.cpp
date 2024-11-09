#include "chessAi.hpp"

vector<string>	chessAi::getLegalMoves(void)
{
	vector<string>	legalMoves;

	legalMoves = _newBoard.getAvailaibleMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		_newBoard._lastMove.action = '-';
		_newBoard._lastMove.obj = legalMoves.at(i)[0];
		
		_newBoard._lastMove.src = string(1, legalMoves.at(i)[1]) + legalMoves.at(i)[2];
		_newBoard._lastMove.dest = legalMoves.at(i).c_str() + 3;
		
		if (_newBoard.isLegal() == false)
			legalMoves.at(i) = "";
	}
	return (legalMoves);
}
