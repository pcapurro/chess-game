#include "../ChessBoard.hpp"

void	ChessBoard::switchPlayers(void)
{
	++_gameInfo.turn % 2 == 0 ? _gameInfo.color = "white" : _gameInfo.color = "black";
}

void	ChessBoard::unSwitchPlayers(void)
{
	--_gameInfo.turn % 2 == 0 ? _gameInfo.color = "white" : _gameInfo.color = "black";
}

void	ChessBoard::tryEnPassant(string srcdest)
{
	int		atValueSrc;
	int		atValueDestOne;
	int		atValueDestTwo;
	
	string	src;
	string	destOne;
	string	destTwo;

	src = {srcdest[0], srcdest[1]};
	destOne = {srcdest[2], srcdest[3]};
	destTwo = destOne, destTwo[1] = src[1];

	atValueSrc = getAtValue(src);
	atValueDestOne = getAtValue(destOne);
	atValueDestTwo = getAtValue(destTwo);

	_savedObjects.push(_board.at(atValueDestTwo).piece);
	_board.at(atValueDestTwo).piece = nullptr;

	_board.at(atValueDestOne).piece = _board.at(atValueSrc).piece;
	_board.at(atValueDestOne).piece->updatePos(_board.at(atValueDestOne).coord);
	_board.at(atValueSrc).piece = nullptr;

	_gameInfo.enPassant = false;
}

void	ChessBoard::undoEnPassant(string srcdest)
{
	int		atValueSrc;
	int		atValueDestOne;
	int		atValueDestTwo;
	
	string	src;
	string	destOne;
	string	destTwo;

	src = {srcdest[0], srcdest[1]};
	destOne = {srcdest[2], srcdest[3]};
	destTwo = destOne, destTwo[1] = src[1];

	atValueSrc = getAtValue(src);
	atValueDestOne = getAtValue(destOne);
	atValueDestTwo = getAtValue(destTwo);

	_board.at(atValueSrc).piece = _board.at(atValueDestOne).piece;
	_board.at(atValueDestOne).piece = nullptr;
	_board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);

	_board.at(atValueDestTwo).piece = _savedObjects.top();

	_savedObjects.pop();

	_gameInfo.enPassant = true;
}

void	ChessBoard::enableCastling(string srcdest)
{
	string	dest = srcdest.c_str() + 2;

	if (_gameInfo.color == "white" && _gameInfo.whiteCastleLost != "")
	{
		_gameInfo.whiteCastled = false;
		_gameInfo.whiteCastle = true;
		_gameInfo.whiteCastleLost.clear();
	}

	if (_gameInfo.color == "black" && _gameInfo.blackCastleLost != "")
	{
		_gameInfo.blackCastled = false;
		_gameInfo.blackCastle = true;
		_gameInfo.blackCastleLost.clear();
	}
}

void	ChessBoard::disableCastling(string srcdest)
{
	string	dest = srcdest.c_str() + 2;

	if (_gameInfo.color == "white" && _gameInfo.whiteCastle == true)
	{
		if (dest == "c1" || dest == "g1")
		{
			_gameInfo.whiteCastled = true;
			_gameInfo.whiteCastle = false;
			_gameInfo.whiteCastleLost = srcdest;
		}
		else
		{
			_gameInfo.whiteCastled = false;
			_gameInfo.whiteCastle = false;
			_gameInfo.whiteCastleLost = srcdest;
		}
	}

	if (_gameInfo.color == "black" && _gameInfo.blackCastle == true)
	{
		if (dest == "c1" || dest == "g1")
		{
			_gameInfo.blackCastled = true;
			_gameInfo.blackCastle = false;
			_gameInfo.blackCastleLost = srcdest;
		}
		else
		{
			_gameInfo.blackCastled = false;
			_gameInfo.blackCastle = false;
			_gameInfo.blackCastleLost = srcdest;
		}
	}
}

void	ChessBoard::tryMove(string srcdest)
{
	int		atValueSrc;
	int		atValueDest;
	
	string	src;
	string	dest;

	if (srcdest == "O-O" || srcdest == "O-O-O" \
		|| (string{srcdest[2], srcdest[3]} == _gameInfo.enPassantDest \
			&& (getType({srcdest[0], srcdest[1]}) == 'P' || getType({srcdest[2], srcdest[3]}) == 'P')))
	{
		if (srcdest[0] == 'O')
		{
			vector<string>  castling;
		
			castling = getCastlingSrcsDests(srcdest);
			tryMove(castling.at(0));
			tryMove(castling.at(1));
		}
		else
			tryEnPassant(srcdest);
	}
	else
	{
		src = {srcdest[0], srcdest[1]};
		dest = srcdest.c_str() + 2;

		atValueSrc = getAtValue(src);
		atValueDest = getAtValue(dest);

		if (_board.at(atValueSrc).piece->getType() == 'K')
			disableCastling(srcdest);

		if (_board.at(atValueDest).piece != nullptr)
		{
			_savedObjects.push(_board.at(atValueDest).piece);
			_board.at(atValueDest).piece = nullptr;
		}
		else
			_savedObjects.push(nullptr);

		_board.at(atValueDest).piece = _board.at(atValueSrc).piece;
		_board.at(atValueDest).piece->updatePos(_board.at(atValueDest).coord);
		_board.at(atValueSrc).piece = nullptr;
	}
}

void	ChessBoard::undoMove(string srcdest)
{	
	if (srcdest == "O-O" || srcdest == "O-O-O" \
		|| (string{srcdest[2], srcdest[3]} == _gameInfo.enPassantDest \
		&& (getType({srcdest[0], srcdest[1]}) == 'P' || getType({srcdest[2], srcdest[3]}) == 'P')))
	{
		if (srcdest[0] == 'O')
		{
			vector<string>  castling;

			castling = getCastlingSrcsDests(srcdest);
			undoMove(castling.at(1));
			undoMove(castling.at(0));
		}
		else
			undoEnPassant(srcdest);
	}
	else
	{
		string src = {srcdest[0], srcdest[1]};
		string dest = srcdest.c_str() + 2;

		int		atValueSrc = getAtValue(src);
		int		atValueDest = getAtValue(dest);

		if (_board.at(atValueDest).piece->getType() == 'K')
			enableCastling(srcdest);

		_board.at(atValueSrc).piece = _board.at(atValueDest).piece;
		_board.at(atValueSrc).piece->updatePos(_board.at(atValueSrc).coord);
		_board.at(atValueDest).piece = _savedObjects.top();

		_savedObjects.pop();
	}
}
