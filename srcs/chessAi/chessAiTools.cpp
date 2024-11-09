#include "chessAi.hpp"

vector<string>	chessAi::getLegalMoves(chessBoard *newBoard)
{
	vector<string>	legalMoves;

	legalMoves = newBoard->getAvailaibleMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		newBoard->_lastMove.action = '-';
		newBoard->_lastMove.obj = legalMoves.at(i)[0];
		
		newBoard->_lastMove.src = string(1, legalMoves.at(i)[1]) + legalMoves.at(i)[2];
		newBoard->_lastMove.dest = legalMoves.at(i).c_str() + 3;
		
		if (newBoard->isLegal() == false)
			legalMoves.at(i) = "";
	}
	return (legalMoves);
}
