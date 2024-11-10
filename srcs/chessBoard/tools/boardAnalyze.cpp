#include "../chessBoard.hpp"

bool    chessBoard::isEndGame(void)
{
    return (false);
}

bool    chessBoard::isProtected(const string coord)
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
    defenders = orderMaterialsByValue(defMaterials);

    if (defenders.size() == 0)
        return (false);

    defenders.push(_board.at(getAtValue(coord)).piece);
    attackers = orderMaterialsByValue(attackMaterials);

    // cout << "attackers >" << endl;
    // while (attackers.size() != 0)
    //     cout << attackers.top()->getType() << endl, attackers.pop();
    // cout << endl;
    // cout << "defenders >" << endl;
    // while (defenders.size() != 0)
    //     cout << defenders.top()->getType() << endl, defenders.pop();

    // defenders = orderMaterialsByValue(defMaterials);
    // defenders.push(_board.at(getAtValue(coord)).piece);
    // attackers = orderMaterialsByValue(attackMaterials);

    while (attackers.size() != 0 && defenders.size() != 0)
    {
        defenderMaterialsEearned += getMaterialValue(attackers.top()->getType()), attackers.pop();
        attackerMaterialsEarned += getMaterialValue(defenders.top()->getType()), defenders.pop();
    }

    if (attackerMaterialsEarned > defenderMaterialsEearned)
        return (false);

    return (true);
}

bool    chessBoard::isSomethingAttacked(void)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
        {
            if (isAttacked(_board.at(i).coord) == true)
                return (true);
        }
    }
    return (false);
}

bool    chessBoard::isAttacked(const string coord)
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

bool    chessBoard::isAttackedByPawn(const string coord)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
        {
            if (_board.at(i).piece->isOnMyWay(coord) == true && _board.at(i).piece->getType() == 'P')
                return (true);
        }
    }
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

string  chessBoard::getBestCounterMateCheck(vector<string> legalMoves)
{
    string          src;
    string          dest;
    string          move;

    vector<string>  attackMoves;
    vector<string>  shieldMoves;
    vector<string>  runAwayMoves;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        src = string(1, legalMoves.at(i)[0]) + legalMoves.at(i)[1];
        dest = legalMoves.at(i).c_str() + legalMoves.at(i).length() - 3;
        if (algebraParser::isChessPiece(dest[dest.length() - 1]) == true)
            dest.erase(dest.length() - 1);
        else
            dest = dest.c_str() + 1;
        
        if (_board.at(getAtValue(dest)).piece != NULL
            && _board.at(getAtValue(dest)).piece->isOnMyWay(src) == false)
            attackMoves.push_back(legalMoves.at(i));
        else
        {
            if (legalMoves.at(i)[0] == 'K')
                runAwayMoves.push_back(legalMoves.at(i));
            else
                shieldMoves.push_back(legalMoves.at(i));
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

    return (move);
}

string  chessBoard::getCounterCheck(void)
{
    string          move;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {   
        tryMove(legalMoves.at(i).c_str() + 1);
        if (isCheck() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        undoMove(legalMoves.at(i).c_str() + 1);
    }

    move = getBestCounterMateCheck(newLegalMoves);

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
        move = getBestCounterMateCheck(newLegalMoves);

    return (move);
}

string	chessBoard::getCounterProtect(void)
{
	string                  move;
    vector<chessPiece *>    targetsList;
    vector<string>          legalMoves;
    vector<string>          moves;
    stack<chessPiece *>     orderedTargets;
    chessPiece              *attackedOne;

    cout << "getting counter protect..." << endl;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
        {
            if (isAttacked(_board.at(i).coord) == true)
                targetsList.push_back(_board.at(i).piece);
        }
    }
    orderedTargets = orderMaterialsByValue(targetsList);
    attackedOne = orderedTargets.top();

    cout << "attacked :" << endl;
    for (int i = 0; i != targetsList.size(); i++)
        cout << targetsList.at(i)->getCoord() << " ; ";
    cout << endl;
    cout << "priority set for " << attackedOne->getCoord() << endl;

    legalMoves = getLegalMoves();
    for (int i = 0; i != legalMoves.size(); i++)
    {
        tryMove(legalMoves.at(i).c_str() + 1);
        if (isAttacked(attackedOne->getCoord()) == false)
            moves.push_back(legalMoves.at(i));
        undoMove(legalMoves.at(i).c_str() + 1);
    }

    vector<string>  runAway;
    vector<string>  protectNormal;
    vector<string>  protectWithPawn;
    string          src;

    for (int i = 0; i != moves.size(); i++)
    {
        src = string(1, moves.at(i)[1]) + moves.at(i)[2];
        if (src == attackedOne->getCoord())
            runAway.push_back(moves.at(i));
        else
        {
            if (moves.at(i)[0] == 'P')
                protectWithPawn.push_back(moves.at(i));
            else
                protectNormal.push_back(moves.at(i));
        }
    }

    srand(time(nullptr));

    if (isAttackedByPawn(attackedOne->getCoord()) == true
        && attackedOne->getType() != 'P')
    {
        if (runAway.size() == 1)
            move = runAway.at(0);
        if (runAway.size() > 1)
            move = runAway.at(rand() % runAway.size());
    }
    else
    {
        if (protectWithPawn.size() >= 1)
        {
            if (protectWithPawn.size() == 1)
                move = protectWithPawn.at(0);
            else
                move = protectWithPawn.at(rand() % protectWithPawn.size());
        }
        else
        {
            if (protectNormal.size() >= 1)
            {
                if (protectNormal.size() == 1)
                    move = protectNormal.at(0);
                else
                    move = protectNormal.at(rand() % protectNormal.size());
            }
            else if (runAway.size() >= 1)
            {
                if (runAway.size() == 1)
                    move = runAway.at(0);
                else
                    move = runAway.at(rand() % runAway.size());
            }
        }
    }

    cout << "proposed solution > " << move << endl;

    return (move);
}

string  chessBoard::getRandomMove(void)
{
    vector<string>  legalMoves;
    string          move;
    int             value;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
        cout << legalMoves.at(i) << " ; ";
    cout << endl;

    srand(time(nullptr));
	value = rand() % legalMoves.size();
	move = legalMoves.at(value);
    return (move);
}
