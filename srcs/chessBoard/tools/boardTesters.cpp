#include "../chessBoard.hpp"

void	chessBoard::switchPlayers(void)
{
	++_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";
}

void	chessBoard::unSwitchPlayers(void)
{
	--_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";
}

void	chessBoard::tryEnPassant(string srcdest)
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

	_gameInfo._enPassant = false;
}

void	chessBoard::undoEnPassant(string srcdest)
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

	_gameInfo._enPassant = true;
}

void	chessBoard::enableCastling(string srcdest)
{
	string	dest = srcdest.c_str() + 2;

	if (_gameInfo._color == "white" && _gameInfo._whiteCastleLost != "")
	{
		_gameInfo._whiteCastled = false;
		_gameInfo._whiteCastle = true;
		_gameInfo._whiteCastleLost.clear();
	}

	if (_gameInfo._color == "black" && _gameInfo._blackCastleLost != "")
	{
		_gameInfo._blackCastled = false;
		_gameInfo._blackCastle = true;
		_gameInfo._blackCastleLost.clear();
	}
}

void	chessBoard::disableCastling(string srcdest)
{
	string	dest = srcdest.c_str() + 2;

	if (_gameInfo._color == "white" && _gameInfo._whiteCastle == true)
	{
		if (dest == "c1" || dest == "g1")
		{
			_gameInfo._whiteCastled = true;
			_gameInfo._whiteCastle = false;
			_gameInfo._whiteCastleLost = srcdest;
		}
		else
		{
			_gameInfo._whiteCastled = false;
			_gameInfo._whiteCastle = false;
			_gameInfo._whiteCastleLost = srcdest;
		}
	}

	if (_gameInfo._color == "black" && _gameInfo._blackCastle == true)
	{
		if (dest == "c1" || dest == "g1")
		{
			_gameInfo._blackCastled = true;
			_gameInfo._blackCastle = false;
			_gameInfo._blackCastleLost = srcdest;
		}
		else
		{
			_gameInfo._blackCastled = false;
			_gameInfo._blackCastle = false;
			_gameInfo._blackCastleLost = srcdest;
		}
	}
}

void	chessBoard::tryMove(string srcdest)
{
	int		atValueSrc;
	int		atValueDest;
	
	string	src;
	string	dest;

	if (srcdest == "O-O" || srcdest == "O-O-O" \
		|| (string{srcdest[2], srcdest[3]} == _gameInfo._enPassantDest \
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

void	chessBoard::undoMove(string srcdest)
{	
	if (srcdest == "O-O" || srcdest == "O-O-O" \
		|| (string{srcdest[2], srcdest[3]} == _gameInfo._enPassantDest \
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
