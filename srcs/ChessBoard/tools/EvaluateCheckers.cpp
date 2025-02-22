#include "ChessBoard/ChessBoard.hpp"

bool	ChessBoard::isFree(const string& coord)
{
	if (getEnPassantTarget() == coord)
	{
		if (isFree(_gameInfo.enPassantDest) == true)
			return (true);
	}
	else
	{
		stack<cP*>	attackers;

		switchPlayers();
		attackers = getWatchers(coord);
		unSwitchPlayers();

		if (attackers.size() == 0)
			return (true);
	}

	return (false);
}

bool	ChessBoard::isSafe(const string& coord)
{
	if (isProtected(coord) == true || isFree(coord) == true)
		return (true);

	return (false);
}

bool	ChessBoard::isProtected(const string& coord)
{
	stack<cP*>	defenders = getWatchers(coord);
	if (defenders.size() == 0)
		return (false);

	switchPlayers();
	stack<cP*>	attackers = getWatchers(coord);
	unSwitchPlayers();
	if (attackers.size() == 0)
		return (true);

	if (coord == _gameInfo.enPassantDest)
		defenders.push(_board.at(getAtValue(getEnPassantTarget())).piece);
	else
		defenders.push(_board.at(getAtValue(coord)).piece);

	int attMaterials = 0;
	int defMaterials = 0;

	while (attackers.size() != 0 && defenders.size() != 0)
	{
		attMaterials +=  getMaterialValue(defenders.top()->getType()), defenders.pop();
		if (defenders.size() == 0)
			break ;
		defMaterials += getMaterialValue(attackers.top()->getType()), attackers.pop();
		if (attMaterials > defMaterials)
			break ;
	}

	if (attMaterials > defMaterials)
		return (false);

	return (true);
}

bool	ChessBoard::isEndGame(void) const
{
	int	whiteMaterials = 0;
	int	blackMaterials = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getType() != 'K')
		{
			if (_board.at(i).piece->getColor() == "white")
				whiteMaterials += getMaterialValue(_board.at(i).piece->getType());

			if (_board.at(i).piece->getColor() == "black")
				blackMaterials += getMaterialValue(_board.at(i).piece->getType());
		}
	}

	if (whiteMaterials < 21 || blackMaterials < 21)
		return (true);

	return (false);
}

bool    ChessBoard::checkMateInOne(void)
{
	string			move;
	vector<string>	legalMoves;

	legalMoves = getLegalMoves();
	for (size_t i = 0; i != legalMoves.size(); i++)
	{
		move = legalMoves.at(i);
		if (move[0] != 'O')
			move = move.c_str() + 1;

		tryMove(move);
		switchPlayers();
		if (isCheckMate(-1) == true)
		{
			undoMove(move);
			unSwitchPlayers();
			return (true);
		}
		unSwitchPlayers();
		undoMove(move);
	}

	return (false);
}

bool	ChessBoard::isDefeatNext(void)
{
	switchPlayers();
	if (checkMateInOne() == true)
		{ unSwitchPlayers(); return (true); }
	unSwitchPlayers();
	
	return (false);
}
