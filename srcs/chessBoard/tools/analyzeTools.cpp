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

bool    chessBoard::canItBeCheckMateNow(void)
{
    string  coord;

    for (int i = 0, k = 0; i != 64; i++, k++)
    {
        if (i % 8 == 0)
            k = 0;
        coord = "abcdefgh"[i / 8] + to_string(k + 1);

        if (_board.at(getAtValue(coord)).piece != NULL
            && _board.at(getAtValue(coord)).piece->getColor() == _gameInfo._color)
        {
            vector<string>  moves = getPossibleMoves(coord);
            for (int k = 0; k != moves.size(); k++)
            {
                tryMove(moves.at(k));
                switchPlayers();
                if (isCheckMate(-1) == true)
                    { undoMove(moves.at(k)); unSwitchPlayers(); return (true); }
                unSwitchPlayers();
                undoMove(moves.at(k));
            }
        }
    }

    return (false);
}

bool    chessBoard::canItBeCheckMateNext(void)
{
    switchPlayers();
    if (canItBeCheckMateNow() == true)
        { unSwitchPlayers(); return (true); }
    unSwitchPlayers();
    
    return (false);
}

string	chessBoard::getCheckMateMove(void)
{
    char            type;
    string          move;
    string          coord;
    vector<string>  moves;

    for (int i = 0, k = 0; i != 64; i++, k++)
    {
        if (i % 8 == 0)
            k = 0;
        coord = "abcdefgh"[i / 8] + to_string(k + 1);

        if (_board.at(getAtValue(coord)).piece != NULL
            && _board.at(getAtValue(coord)).piece->getColor() == _gameInfo._color)
        {
            type = _board.at(getAtValue(coord)).piece->getType();
            moves = getPossibleMoves(coord);

            for (int k = 0; k != moves.size(); k++)
            {
                tryMove(moves.at(k));
                switchPlayers();
                if (isCheckMate(-1) == true)
                {
                    undoMove(moves.at(k));
                    unSwitchPlayers();
                    return (string(1, type) + moves.at(k)[0] \
                            + moves.at(k)[1] + (moves.at(k).c_str() + 2));
                }
                unSwitchPlayers();
                undoMove(moves.at(k));
            }
        }
    }

    return ("");
}

string	chessBoard::getCounterStrike(void)
{
	string          move;

    return (move);
}

string	chessBoard::getCounterCheckMate(void)
{
    string          move;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {   
        tryMove(legalMoves.at(i).c_str() + 1);
        if (canItBeCheckMateNext() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        undoMove(legalMoves.at(i).c_str() + 1);
    }

    if (newLegalMoves.size() == 0)
        return (move);
    else
    {
        vector<string>  attackMoves;
        vector<string>  shieldMoves;
        vector<string>  runAwayMoves;

        for (int i = 0; i != newLegalMoves.size(); i++)
        {
            if (isThereSomething(newLegalMoves.at(i).c_str() + newLegalMoves.at(i).size() - 2) == true)
                attackMoves.push_back(newLegalMoves.at(i));
            else
            {
                if (newLegalMoves.at(i)[0] == 'K')
                    runAwayMoves.push_back(newLegalMoves.at(i));
                else
                    shieldMoves.push_back(newLegalMoves.at(i));
            }
        }

        vector<string>  *moves;

        if (attackMoves.size() != 0)
            moves = &attackMoves;
        else
        {
            if (shieldMoves.size() != 0)
                moves = &shieldMoves;
            else
            {
                if (runAwayMoves.size() != 0)
                    moves = &runAwayMoves;
            }
        }

        if (moves->size() == 1)
            move = moves->at(0);
        if (moves->size() > 1)
            move = moves->at(rand() % moves->size());
    }

    return (move);
}

string	chessBoard::getCounterAttack(void)
{
	string  move;

    return (move);
}

string  chessBoard::getRandomMove(void)
{
    vector<string>  legalMoves;
    string          move;
    int             value;

    legalMoves = getLegalMoves();
    srand(time(nullptr));
	value = rand() % legalMoves.size();
	move = legalMoves.at(value);
    return (move);
}
