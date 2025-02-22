#include "ChessBoard/ChessBoard.hpp"

void	ChessBoard::enableDisableEnPassant(void)
{
	char			obj = _gameInfo.lastMove.obj;
	std::string		src = _gameInfo.lastMove.src;
	std::string		dest = _gameInfo.lastMove.dest;

	if (obj == 'P')
	{
		if ((_gameInfo.color == "white" && dest[1] == src[1] + 2 && dest[1] == '4') \
			|| (_gameInfo.color == "black" && dest[1] == src[1] - 2 && dest[1] == '5'))
		{
			_gameInfo.enPassant = true;

			_gameInfo.enPassantSrcOne = dest;
			_gameInfo.enPassantSrcOne[0] = _gameInfo.enPassantSrcOne[0] - 1;
			_gameInfo.enPassantSrcTwo = dest;
			_gameInfo.enPassantSrcTwo[0] = _gameInfo.enPassantSrcTwo[0] + 1;

			_gameInfo.enPassantDest = dest;

			if (_gameInfo.color == "white")
				_gameInfo.enPassantDest[1] = _gameInfo.enPassantDest[1] - 1;
			else
				_gameInfo.enPassantDest[1] = _gameInfo.enPassantDest[1] + 1;

			return ;
		}
	}
	_gameInfo.enPassant = false;
	_gameInfo.enPassantSrcOne.clear();
	_gameInfo.enPassantSrcTwo.clear();
	_gameInfo.enPassantDest.clear();
}

void	ChessBoard::priseEnPassant()
{
	size_t			atValue;
	std::string		newCoordUpdated;
	ChessPiece*		piece;

	atValue = getAtValue(_gameInfo.lastMove.src); 
	piece = _board.at(atValue).piece;
	_board.at(atValue).piece = nullptr;

	atValue = getAtValue(_gameInfo.lastMove.dest);
	_board.at(atValue).piece = piece;
	_board.at(atValue).piece->move();
	_board.at(atValue).piece->updatePos(_gameInfo.lastMove.dest);

	newCoordUpdated = _gameInfo.lastMove.dest;
	if (_gameInfo.color == "white")
		newCoordUpdated[1] = newCoordUpdated[1] - 1;
	if (_gameInfo.color == "black")
		newCoordUpdated[1] = newCoordUpdated[1] + 1;

	removePiece(newCoordUpdated);
}

void	ChessBoard::removePiece(const std::string& coord)
{
	size_t	atValue = getAtValue(coord);

	if (_board.at(atValue).piece != nullptr)
	{
		if (_board.at(atValue).piece->getColor() == "black")
			_whiteCaptured.push_back(_board.at(atValue).piece->getType());
		if (_board.at(atValue).piece->getColor() == "white")
			_blackCaptured.push_back(_board.at(atValue).piece->getType());

		delete _board.at(atValue).piece;
		_board.at(atValue).piece = nullptr;
	}
}

void	ChessBoard::promotePiece(const std::string& initialCoord, char pieceType)
{
	size_t			atValue;
	std::string		initialCoordUpdated;
	std::string		color;

	initialCoordUpdated = initialCoord;
	initialCoordUpdated[2] = '\0';
	atValue = getAtValue(initialCoordUpdated);
	color = _board.at(atValue).piece->getColor();
	
	removePiece(initialCoord);
	if (pieceType == 'Q')
		_board.at(atValue).piece = new (std::nothrow) Queen(color, initialCoordUpdated);
	if (pieceType == 'N')
		_board.at(atValue).piece = new (std::nothrow) Knight(color, initialCoordUpdated);
	if (pieceType == 'B')
		_board.at(atValue).piece = new (std::nothrow) Bishop(color, initialCoordUpdated);
	if (pieceType == 'R')
		_board.at(atValue).piece = new (std::nothrow) Rook(color, initialCoordUpdated);
	}

void	ChessBoard::movePiece(const std::string& initialCoord, const std::string& newCoord)
{
	ChessPiece*		piece;
	size_t			atValue;
	std::string		newCoordUpdated;
	
	atValue = getAtValue(initialCoord); 
	piece = _board.at(atValue).piece;
	_board.at(atValue).piece = nullptr;

	newCoordUpdated = newCoord;
	if (newCoord.length() == 3)
		newCoordUpdated = newCoord, newCoordUpdated[2] = '\0';
	
	removePiece(newCoordUpdated);
	atValue = getAtValue(newCoordUpdated);
	_board.at(atValue).piece = piece;

	_board.at(atValue).piece->move();
	_board.at(atValue).piece->updatePos(newCoord);

	if (_board.at(atValue).piece->getType() == 'K')
	{
		if (_board.at(atValue).piece->getOriginalCoord() == "e1")
			_gameInfo.whiteCastle = false;

		if (_board.at(atValue).piece->getOriginalCoord() == "e8")
			_gameInfo.blackCastle = false;
	}
}


void	ChessBoard::whiteCastles(void)
{
	if (_gameInfo.lastMove.dest == "O-O")
	{
		movePiece("h1", "f1");
		movePiece("e1", "g1");
	}
	if (_gameInfo.lastMove.dest == "O-O-O")
	{
		movePiece("e1", "c1");
		movePiece("a1", "d1");
	}

	_gameInfo.whiteCastle = false;
	_gameInfo.whiteCastled = true;
}

void	ChessBoard::blackCastles(void)
{
	if (_gameInfo.lastMove.dest == "O-O")
	{
		movePiece("e8", "g8");
		movePiece("h8", "f8");
	}
	if (_gameInfo.lastMove.dest == "O-O-O")
	{
		movePiece("e8", "c8");
		movePiece("a8", "d8");
	}

	_gameInfo.blackCastle = false;
	_gameInfo.blackCastled = true;
}

void	ChessBoard::addToHistory(void)
{
	char			action = _gameInfo.lastMove.action;
	char			obj = _gameInfo.lastMove.obj;
	std::string		src = _gameInfo.lastMove.src;
	std::string		dest = _gameInfo.lastMove.dest;

	if (dest == "O-O" || dest == "O-O-O")
	{
		char letter, number;
		_gameInfo.turn % 2 == 0 ? src = "e1" : src = "e8";
		dest.size() == 3 ? letter = 'g' : letter = 'c';
		src == "e1" ? number = '1' : number = '8';

		_simpleHistory.push_back(src + letter + number);
		_history.push_back(dest);
	}
	else
	{
		if (action == 'x')
		{
			if (obj != 'P')
				_history.push_back(obj + src + "x" + dest);
			else
				_history.push_back(src + "x" + dest);
		}
		else
		{
			if (obj != 'P')
				_history.push_back(obj + src + "-" + dest);
			else
				_history.push_back(dest);
		}

		if (dest.size() == 3)
			dest[2] = tolower(dest[2]);

		_simpleHistory.push_back(src + dest);
	}
}

void	ChessBoard::loadMove(const std::string& move)
{
	if (move == "O-O-O" || move == "O-O")
	{
		_gameInfo.turn % 2 == 0 ? _gameInfo.lastMove.src = "e1" : _gameInfo.lastMove.src = "e8";

		if (move == "O-O-O")
			_gameInfo.lastMove.dest = "O-O-O";
		else
			_gameInfo.lastMove.dest = "O-O";
	}
	else
	{
		_gameInfo.lastMove.obj = move[0];

		_gameInfo.lastMove.move = move;
		_gameInfo.lastMove.src = {move[1], move[2]};
		_gameInfo.lastMove.dest = move.c_str() + 3;

		if (_gameInfo.lastMove.dest == _gameInfo.enPassantDest \
			|| _board.at(getAtValue(move.c_str() + 3)).piece != nullptr)
			_gameInfo.lastMove.action = 'x';
		else
			_gameInfo.lastMove.action = '-';
	}
}

int	ChessBoard::playMove(Move structureMove, const std::string& move)
{
	if (move == "")
		_gameInfo.lastMove = structureMove;
	else
		loadMove(move);

	if (isLegal() == false)
		{ _gameInfo.moveFailed = true; return (1); }
	else
	{
		_gameInfo.moveFailed = false;

		if (_board.at(getAtValue(_gameInfo.lastMove.dest)).piece != nullptr)
			_gameInfo.lastMove.action = 'x';

		std::string	src = _gameInfo.lastMove.src;
		std::string	dest = _gameInfo.lastMove.dest;
		char	action = _gameInfo.lastMove.action;

		if (_gameInfo.lastMove.dest == "O-O"
			|| _gameInfo.lastMove.dest == "O-O-O")
		{
			if (_gameInfo.color == "white")
				whiteCastles();
			if (_gameInfo.color == "black")
				blackCastles();
		}
		else
		{
			if ((action == 'x' || action == '-') \
				&& isThereSomething(dest) == false \
				&& _gameInfo.enPassant == true && _gameInfo.enPassantDest == dest)
				priseEnPassant();
			else
			{
				movePiece(src, dest);
				if (AlgebraParser::isChessPiece(dest.at(dest.length() - 1)) == true)
					promotePiece(dest, dest[dest.length() - 1]);
			}
		}
		enableDisableEnPassant();
		addToHistory();
		countTotalMaterials();

		++_gameInfo.turn % 2 == 0 ? _gameInfo.color = "white" : _gameInfo.color = "black";
	}

	return (0);
}
