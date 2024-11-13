#include "chessAi.hpp"

string  chessAi::getPawnsDev(void)
{
    int value;

    srand(time(nullptr));
    value = rand() % 10;
    if (_gameInfo._turn == 0)
    {
        if (value < 6)
            return ("Pe2e4");
        if (value == 6 || value == 7 || value == 8)
            return ("Pd2d3");
    }
    if (_gameInfo._turn == 1)
    {
        if (_board.at(getAtValue("e4")).piece != NULL)
        {
            if (value == 0)
                return ("Pd7d5");
            if (value < 6)
                return ("Pe7e5");
            if (value >= 6 && value < 9)
                return ("Pd7d6");
        }
        if (_board.at(getAtValue("d4")).piece != NULL)
        {
            if (value < 7)
                return ("Pd7d5");
            if (value > 7)
                return ("Pe7e6");
        }
    }

    return ("");
}

string  chessAi::getKnightsDev(void)
{
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();

    string nb1, nb2;

    if (_gameInfo._color == "white")
        nb1 = "1", nb2 = "3";
    else
        nb1 = "8", nb2 = "6";

    cout << "analyzing cav dev" << endl;

    if (_board.at(getAtValue(string(1, 'g') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'g') + nb1)).piece->getType() == 'N'
        && _board.at(getAtValue(string(1, 'g') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Ng" + nb1 + 'f' + nb2) != legalMoves.end())
        {
            tryMove("g" + nb1 + 'f' + nb2);
            if (isProtected(string(1, 'f') + nb2) == true)
                { undoMove("g" + nb1 + 'f' + nb2); cout << "developing cav" << endl; return ("Ng" + nb1 + 'f' + nb2); }
            undoMove("g" + nb1 + 'f' + nb2);
        }
    }
    if (_board.at(getAtValue(string(1, 'b') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'b') + nb1)).piece->getType() == 'N'
        && _board.at(getAtValue(string(1, 'b') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Nb" + nb1 + 'c' + nb2) != legalMoves.end())
        {
            tryMove("b" + nb1 + 'c' + nb2);
            if (isProtected(string(1, 'c') + nb2) == true)
                { undoMove("b" + nb1 + 'c' + nb2); cout << "developing cav" << endl; return ("Nb" + nb1 + 'c' + nb2); }
            undoMove("b" + nb1 + 'c' + nb2);
        }
    }

    return ("");
}

string  chessAi::getCastling(void)
{
    if (isCastlingPossible("O-O") == true && isCheck() == false)
        return ("O-O");
    if (isCastlingPossible("O-O-O") == true && isCheck() == false)
        return ("O-O-O");

    cout << "no castling" << endl;

    return ("");
}

string  chessAi::getBishopsDev(void)
{
    vector<string>  legalMoves;

    legalMoves = getLegalMoves();

    string nb1, nb2;

    if (_gameInfo._color == "white")
        nb1 = "1", rand() % 2 == 0 ? nb2 = "4" : nb2 = "5";
    else
        nb1 = "8", rand() % 2 == 0 ? nb2 = "5" : nb2 = "4";

    cout << "analyzing bishop dev" << endl;

    if (_board.at(getAtValue(string(1, 'f') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'f') + nb1)).piece->getType() == 'B'
        && _board.at(getAtValue(string(1, 'f') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Bf" + nb1 + 'c' + nb2) != legalMoves.end())
        {
            tryMove("f" + nb1 + 'c' + nb2);
            if (isProtected(string(1, 'c') + nb2) == true)
                { undoMove("f" + nb1 + 'c' + nb2); cout << "developing bishop" << endl; return ("Bf" + nb1 + 'c' + nb2); }
            undoMove("f" + nb1 + 'c' + nb2);
        }
    }
    if (_board.at(getAtValue(string(1, 'c') + nb1)).piece != NULL && _board.at(getAtValue(string(1, 'c') + nb1)).piece->getType() == 'B'
        && _board.at(getAtValue(string(1, 'c') + nb1)).piece->getColor() == _gameInfo._color)
    {
        if (find(legalMoves.begin(), legalMoves.end(), "Bc" + nb1 + 'f' + nb2) != legalMoves.end())
        {
            tryMove("c" + nb1 + 'f' + nb2);
            if (isProtected(string(1, 'f') + nb2) == true)
                { undoMove("c" + nb1 + 'f' + nb2); cout << "developing cav" << endl; return ("Bc" + nb1 + 'f' + nb2); }
            undoMove("c" + nb1 + 'f' + nb2);
        }
    }

    return ("");
}

string  chessAi::getPassiveMove(void)
{
    string          move;
    vector<string>  legalMoves;

    move = getPawnsDev();
    if (move == "")
        move = getBishopsDev();
    if (move == "")
        move = getKnightsDev();
    if (move == "")
        move = getCastling();

    if (move == "")
    {
        legalMoves = getLegalMoves();
        for (int i = 0; i != legalMoves.size(); i++)
        {
            if (legalMoves.at(i)[0] == 'P')
            {
                move = legalMoves.at(i);
                tryMove(move.c_str() + 1);
                if (isProtected(move) == true)
                    { undoMove(move.c_str() + 1); cout << "proposed passive move : " << move << endl; return (move); }
                undoMove(move.c_str() + 1);
            }
        }
    }

    return (move);
}

string	chessAi::getCheckMateMove(void)
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
            moves = getPossibleMoves(coord, true);

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

string  chessAi::preventCastling(const string castle)
{
    vector<string>  legalMoves;

    unSwitchPlayers();
    legalMoves = getLegalMoves();
    switchPlayers();

    for (int i = 0; i != legalMoves.size(); i++)
    {
        tryMove(legalMoves.at(i).c_str() + 1);
        if (isCastlingPossible(castle) == false)
        {
            unSwitchPlayers();
            if (isProtected(legalMoves.at(i).c_str() + 3) == true)
                { switchPlayers(); undoMove(legalMoves.at(i).c_str() + 1); cout << "proposed anti castling solution >" << legalMoves.at(i) << endl; return (legalMoves.at(i)); }
            switchPlayers();
        }
        undoMove(legalMoves.at(i).c_str() + 1);
    }
    
    return ("");
}

string	chessAi::getCounterStrike(void)
{
	string          move;

    vector<string>          legalMoves;
    vector<chessPiece *>    targets;
    stack<chessPiece *>     orderedTargets;
    chessPiece              *target;

    cout << "detecting not protected targets..." << endl;

    switchPlayers();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isProtected(_board.at(i).coord) == false)
            targets.push_back(_board.at(i).piece);
    }
    unSwitchPlayers();

    cout << targets.size() << " not protected" << endl;

    if (targets.size() != 0)
    {
        orderedTargets = orderMaterialsByValue(targets);
        while (orderedTargets.size() != 0)
            target = orderedTargets.top(), orderedTargets.pop();

        cout << target->getType() << " selected" << endl;

        legalMoves = getLegalMoves();
        for (int i = 0; i != legalMoves.size(); i++)
        {
            string dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];
            if (dest == target->getCoord())
                { cout << "proposed attack for " << target->getCoord() << " > " << legalMoves.at(i) << endl; return (legalMoves.at(i)); }
        }
    }

    switchPlayers();
    if (isCheck() == false)
    {
        cout << "analyzing castling..." << endl;
        if (isCastlingPossible("O-O") == true)
        {
            cout << "enemy can O-O" << endl;
            move = preventCastling("O-O");
        }
        if (isCastlingPossible("O-O-O") == true)
        {
            cout << "enemy can O-O-O" << endl;
            move = preventCastling("O-O-O");
        }
    }
    unSwitchPlayers();

    return (move);
}

string  chessAi::getBestCounterMateCheck(vector<string> legalMoves)
{
    string          src;
    string          dest;
    string          move;

    vector<string>  attackMoves;
    vector<string>  shieldMoves;
    vector<string>  othersMoves;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        src = string(1, legalMoves.at(i)[0]) + legalMoves.at(i)[1];
        dest = legalMoves.at(i).c_str() + legalMoves.at(i).length() - 3;
        if (algebraParser::isChessPiece(dest[dest.length() - 1]) == true)
            dest.erase(dest.length() - 1);
        else
            dest = dest.c_str() + 1;
        
        if (_board.at(getAtValue(dest)).piece != NULL
            && _board.at(getAtValue(dest)).piece->isOnMyWay(src) == false
            && legalMoves.at(i)[0] != 'K')
            attackMoves.push_back(legalMoves.at(i));
        else
        {
            if (legalMoves.at(i)[0] == 'K')
                othersMoves.push_back(legalMoves.at(i));
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
            if (othersMoves.size() != 0)
                moves = &othersMoves;
        }
    }

    if (moves->size() == 1)
        move = moves->at(0);
    if (moves->size() > 1)
        move = moves->at(rand() % moves->size());

    return (move);
}

string  chessAi::getCounterCheck(void)
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

string	chessAi::getCounterCheckMate(void)
{
    string          move;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {   
        tryMove(legalMoves.at(i).c_str() + 1);
        if (isDefeatNext() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        undoMove(legalMoves.at(i).c_str() + 1);
    }

    if (newLegalMoves.size() == 0)
        return (move);
    else
        move = getBestCounterMateCheck(newLegalMoves);

    return (move);
}

string	chessAi::getCounterProtect(void)
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
    while (orderedTargets.size() != 0)
        attackedOne = orderedTargets.top(), orderedTargets.pop();

    cout << "attacked :" << endl;
    for (int i = 0; i != targetsList.size(); i++)
        cout << targetsList.at(i)->getCoord() << "-" << targetsList.at(i)->getType() << " ; ";
    cout << endl;
    cout << "priority set for " << attackedOne->getCoord() << endl;

    legalMoves = getLegalMoves();

    string  testingMove;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        if (legalMoves.at(i) == "O-O" || legalMoves.at(i) == "O-O-O")
            testingMove = legalMoves.at(i);
        else
            testingMove = legalMoves.at(i).c_str() + 1;

        tryMove(testingMove);
        cout << "testing " << testingMove << endl;
        if (isAttacked(attackedOne->getCoord()) == false)
            moves.push_back(legalMoves.at(i));
        undoMove(testingMove);
    }

    cout << "possible solutions :" << endl;
    for (int i = 0; i != moves.size(); i++)
        cout << moves.at(i) << " ; ";
    cout << endl;

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

    cout << runAway.size() << " solutions of runaway" << endl;
    cout << protectWithPawn.size() << " solutions of protectWithPawn" << endl;
    cout << protectNormal.size() << " solutions of protectNormal" << endl;

    srand(time(nullptr));

    if (isAttackedByPawn(attackedOne->getCoord()) == true
        && attackedOne->getType() != 'P')
    {
        cout << "attacked by pawn" << endl;
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

string  chessAi::getRandomMove(void)
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
