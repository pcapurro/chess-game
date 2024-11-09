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
    char    type;

    if (switchPlayers == true)
        ++_turn % 2 == 0 ? _color = "white" : _color = "black";

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL && _board.at(getAtValue(coord)).piece->getColor() != _color)
            {
                type = _board.at(getAtValue(coord)).piece->getType();
                vector<string>  moves = getPossibleMoves(coord, reverse);
                for (int k = 0; k != moves.size(); k++)
                {
                    tryMove(moves.at(k));

                    if (isCheckMate(-1) == true)
                    {
                        _checkMateMove = string(1, type) + moves.at(k);
                        undoMove(moves.at(k));
                        if (switchPlayers == true)
                            --_turn % 2 == 0 ? _color = "white" : _color = "black";
                        return (true);
                    }
    
                    undoMove(moves.at(k));
                }
            }
        }
    }

    if (switchPlayers == true)
        --_turn % 2 == 0 ? _color = "white" : _color = "black";

    return (false);
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