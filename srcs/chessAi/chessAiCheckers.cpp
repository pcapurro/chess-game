#include "chessAi.hpp"

bool    chessAi::isEndGame(void)
{
    return (false);
}

bool    chessAi::isProtected(const string coord)
{
    int                     attackerMaterialsEarned = 0;
    int                     defenderMaterialsEearned = 0;
    vector<chessPiece *>    attackMaterials;
    vector<chessPiece *>    defMaterials;
    stack<chessPiece *>     attackers;
    stack<chessPiece *>     defenders;

    cout << "evaluating if " << coord << " is protected..." << endl;

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

    cout << "attackers >" << endl;
    for (int i = 0; i != attackMaterials.size(); i++)
        cout << attackMaterials.at(i)->getCoord() << " ; ";
    cout << endl;

    if (defMaterials.size() == 0)
        return (false);

    cout << "defenders >" << endl;
    for (int i = 0; i != defMaterials.size(); i++)
        cout << defMaterials.at(i)->getCoord() << " ; ";
    cout << endl;

    defenders = orderMaterialsByValue(defMaterials);
    defenders.push(_board.at(getAtValue(coord)).piece);
    attackers = orderMaterialsByValue(attackMaterials);

    while (attackers.size() != 0 && defenders.size() != 0)
    {
        attackerMaterialsEarned += getMaterialValue(defenders.top()->getType()), defenders.pop();
        if (defenders.size() == 0)
            break ;
        defenderMaterialsEearned += getMaterialValue(attackers.top()->getType()), attackers.pop();
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
            if (isProtected(_board.at(i).coord) == false)
                { cout << _board.at(i).coord << " not protected" << endl; return (true); }
        }
    }
    return (false);
}

bool    chessAi::isAllyAttacked(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
        {
            if (isAttacked(_board.at(i).coord) == true)
                return (true);
        }
    }

    cout << "nothing attacked" << endl;

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

bool    chessAi::isVictoryNext(void)
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
            vector<string>  moves = getPossibleMoves(coord, true);
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

bool    chessAi::isDefeatNext(void)
{
    switchPlayers();
    if (isVictoryNext() == true)
        { unSwitchPlayers(); return (true); }
    unSwitchPlayers();
    
    return (false);
}
