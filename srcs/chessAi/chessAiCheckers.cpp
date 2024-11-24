#include "chessAi.hpp"

bool    chessAi::isEndGame(void)
{
    return (false);
}

int     chessAi::getAttackedNumber(void)
{
    int nb = 0;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            nb++;
    }
    return (nb);
}

bool    chessAi::isProtected(const string coord)
{
    int                     attackerMaterialsEarned = 0;
    int                     defenderMaterialsEearned = 0;
    vector<chessPiece *>    attackMaterials;
    vector<chessPiece *>    defMaterials;
    stack<chessPiece *>     attackers;
    stack<chessPiece *>     defenders;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getColor() != _gameInfo._color)
            {
                if (_board.at(i).piece->isOnMyWay(coord, getPiecesCoords(), 1, _gameInfo._enPassantDest) == true)
                    attackMaterials.push_back(_board.at(i).piece);
            }
            else if (_board.at(i).coord != coord)
            {
                if (_board.at(i).piece->isOnMyWay(coord, getPiecesCoords(), 1, _gameInfo._enPassantDest) == true)
                    defMaterials.push_back(_board.at(i).piece);
            }
        }
    }

    if (attackMaterials.size() == 0)
        return (true);

    if (defMaterials.size() == 0)
        return (false);

    defenders = orderMaterialsByValue(defMaterials);
    defenders.push(_board.at(getAtValue(coord)).piece);
    attackers = orderMaterialsByValue(attackMaterials);

    while (attackers.size() != 0 && defenders.size() != 0)
    {
        attackerMaterialsEarned += getMaterialValue(defenders.top()->getType()), defenders.pop();
        if (defenders.size() == 0)
            break ;
        defenderMaterialsEearned += getMaterialValue(attackers.top()->getType()), attackers.pop();
        if (attackerMaterialsEarned > defenderMaterialsEearned)
            break ;
    }

    if (attackerMaterialsEarned > defenderMaterialsEearned)
        return (false);

    return (true);
}

bool    chessAi::isSomethingNotProtected(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            switchPlayers();
            if (isProtected(_board.at(i).coord) == false)
            {
                unSwitchPlayers();
                return (true);
            }
            unSwitchPlayers();
        }
    }
    return (false);
}

bool    chessAi::isDefenseWorth(void)
{
    int targets = 0;
    int attacked = 0;

    for (int i = 0; i != 64; i++)
    {
        switchPlayers();

        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            targets += getMaterialValue(_board.at(i).piece->getType());
        
        unSwitchPlayers();

        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isAttacked(_board.at(i).coord) == true)
            attacked += getMaterialValue(_board.at(i).piece->getType());
    }

    if (targets >= attacked)
        return (false);

    return (true);
}

bool    chessAi::isAllyAttacked(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
        {
            if (isAttacked(_board.at(i).coord) == true)
                _attackedAlly.push_back(_board.at(i).piece);
        }
    }

    if (_attackedAlly.size() != 0)
        return (true);

    return (false);
}

bool    chessAi::isAttacked(const string coord)
{
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            if (_board.at(i).piece->isOnMyWay(coord, boardCoords, 1, _gameInfo._enPassantDest) == true)
            {
                if (isProtected(coord) == false)
                    return (true);
            }
        }
    }
    return (false);
}

bool    chessAi::isAttackedByPawn(const string coord)
{
    vector<string>  boardCoords;

    boardCoords = getPiecesCoords();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            if (_board.at(i).piece->getType() == 'P' && _board.at(i).piece->isOnMyWay(coord, boardCoords, 1, _gameInfo._enPassantDest) == true)
                return (true);
        }
    }
    return (false);
}

bool    chessAi::isVictoryNextNext(void)
{
    string          move;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        tryMove(move);

        if (isVictoryNext() == true && (count(move.begin(), move.end(), 'O') != 0
            || isProtected(string(1, move[2]) + move[3]) == true))
        {
            undoMove(move);
            _attackMove = legalMoves.at(i);
            return (true);
        }

        undoMove(move);
    }
    return (false);
}

bool    chessAi::isVictoryNext(void)
{
    string          move;
    string          target;
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1, target = string(1, move[2]) + move[3];

        if (move[0] != 'O' && _board.at(getAtValue(target)).piece != NULL
            && _board.at(getAtValue(target)).piece->getType() != 'K')
        {
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
    }

    return (false);
}

bool    chessAi::isDefeatNext(void)
{
    switchPlayers();
    if (isVictoryNext() == true)
        { unSwitchPlayers(); return (true); }
    unSwitchPlayers();
    
    return (false);
}
