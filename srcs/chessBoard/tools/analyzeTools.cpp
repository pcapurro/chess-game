#include "../chessBoard.hpp"

bool    chessBoard::isEndGame(void)
{
    return (false);
}

bool    chessBoard::isProtected(void)
{
   return (false);
}

bool    chessBoard::isAttacked(void)
{
   return (false);
}

bool    chessBoard::canItBeCheckMate(const bool reverse, const bool switchPlayers)
{
    int     value;
    char    type;
    string  coord;

    if (switchPlayers == true)
        ++_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";

    value = false;

    for (int i = 0, k = 0; i != 64; i++, k++)
    {
        if (i % 8 == 0)
            k = 0;
        
        coord = "abcdefgh"[i / 8] + to_string(k + 1);
        if (_board.at(getAtValue(coord)).piece != NULL
            && _board.at(getAtValue(coord)).piece->getColor() != _gameInfo._color)
        {
            vector<string>  moves = getPossibleMoves(coord, reverse);
            for (int k = 0; k != moves.size(); k++)
            {
                tryMove(moves.at(k));
                if (isCheckMate(-1) == true)
                    { undoMove(moves.at(k)); value = true; break ; }
                undoMove(moves.at(k));
            }
        }
    }

    if (switchPlayers == true)
        --_gameInfo._turn % 2 == 0 ? _gameInfo._color = "white" : _gameInfo._color = "black";

    return (value);
}


string	chessBoard::getCheckMateMove(void)
{
	;
}

string	chessBoard::getCounterStrike(void)
{
	;
}

string	chessBoard::getCounterCheckMate(void)
{
	;
}

string	chessBoard::getCounterCheck(void)
{
	;
}

string	chessBoard::getCounterAttack(void)
{
	;
}