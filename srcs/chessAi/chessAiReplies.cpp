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
    int               value;
    string            move;
    vector<string>    legalMoves;
    vector<string>    pawns;

    cout << "searching basic dev or castling..." << endl;

    move = getPawnsDev();
    if (move == "")
        move = getBishopsDev();
    if (move == "")
        move = getKnightsDev();
    if (move == "")
        move = getCastling();

    cout << "basic dev or castling found." << endl;

    if (move == "")
    {
        cout << "searching for passive pawn dev..." << endl;

        legalMoves = getLegalMoves();
        for (int i = 0; i != legalMoves.size(); i++)
        {
            srand(time(nullptr));
            if (legalMoves.at(i)[0] == 'P')
            {
                move = legalMoves.at(i);
                if (count(move.begin(), move.end(), 'O') == 0)
                    move = move.c_str() + 1,

                tryMove(move);
                if (isProtected(string(1, move[2]) + move[3]) == true)
                    pawns.push_back(legalMoves.at(i));
                undoMove(move);
            }
        }

        if (pawns.size() == 1)
            move = pawns.at(0);
        else if (pawns.size() > 1)
            move = (pawns.at(rand() % pawns.size()));

        if (move != "")
            cout << "passive pawn dev found." << endl;
    }

    return (move);
}

string	chessAi::getCheckMateMove(void)
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
        switchPlayers();
        if (isCheckMate(-1) == true)
        {
            undoMove(move);
            unSwitchPlayers();
            return (legalMoves.at(i));
        }
        unSwitchPlayers();
        undoMove(move);
    }
    return ("");
}

string  chessAi::preventCastling(const string castle)
{
    vector<string>  legalMoves;
    string          move;

    unSwitchPlayers();
    legalMoves = getLegalMoves();
    switchPlayers();

    for (int i = 0; i != legalMoves.size(); i++)
    {
        move = legalMoves.at(i);
        if (count(move.begin(), move.end(), 'O') == 0)
            move = move.c_str() + 1;

        tryMove(move);
        if (isCastlingPossible(castle) == false)
        {
            unSwitchPlayers();
            if (isProtected(string(1, move[2]) + move[3]) == true)
                { switchPlayers(); undoMove(move); cout << "proposed anti castling solution >" << legalMoves.at(i) << endl; return (legalMoves.at(i)); }
            switchPlayers();
        }
        undoMove(move);
    }
    
    return ("");
}

string	chessAi::getCounterStrike(void)
{
	string                  move;
    string                  testMove;
    vector<string>          legalMoves;
    vector<chessPiece *>    targets;
    stack<chessPiece *>     orderedTargets;
    vector<chessPiece *>    attackers;
    stack<chessPiece *>     orderedAttackers;
    chessPiece              *target;
    chessPiece              *attacker;

    if (_victoryNextNext == true)
        return (_attackMove);

    cout << "detecting not protected targets..." << endl;

    switchPlayers();
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
            && isProtected(_board.at(i).coord) == false)
            targets.push_back(_board.at(i).piece);
    }
    unSwitchPlayers();

    cout << targets.size() << " enemies not protected:" << endl;
    for (int i = 0; i != targets.size(); i++)
        cout << targets.at(i)->getType() << " ; ";
    cout << endl;

    legalMoves = getLegalMoves();

    if (targets.size() == 0)
    {
        for (int i = 0; i != legalMoves.size(); i++)
        {
            if (count(legalMoves.at(i).begin(), legalMoves.at(i).end(), 'O') == 0)
            {
                string  dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];

                testMove = legalMoves.at(i);
                if (count(testMove.begin(), testMove.end(), 'O') == 0)
                    testMove = testMove.c_str() + 1;

                tryMove(testMove);
                if (isSomethingNotProtected() == true && isProtected(dest) == true)
                {
                    undoMove(testMove);
                    cout << "threat found with " << legalMoves.at(i) << endl;
                    return (legalMoves.at(i));
                }
                undoMove(testMove);
            }
        }
    }
    else
    {
        orderedTargets = orderMaterialsByValue(targets);
        cout << "ordered targets size > " << orderedTargets.size() << endl;
        while (orderedTargets.size() != 0)
            target = orderedTargets.top(), orderedTargets.pop();

        cout << target->getType() << " selected" << endl;

        for (int i = 0; i != legalMoves.size(); i++)
        {
            string  src = string(1, legalMoves.at(i)[1]) + legalMoves.at(i)[2];
            string  dest = string(1, legalMoves.at(i)[3]) + legalMoves.at(i)[4];

            if (dest == target->getCoord())
                attackers.push_back(_board.at(getAtValue(src)).piece);
        }
    }

    cout << attackers.size() << " attackers found" << endl;

    if (attackers.size() != 0)
    {
        orderedAttackers = orderMaterialsByValue(attackers);
        attacker = orderedAttackers.top();

        cout << attacker->getType() << " selected by priority" << endl;

        cout << "proposed attack for " << target->getCoord() << " > " << attacker->getCoord() << target->getCoord() << endl;
        return (string(1, attacker->getType()) + attacker->getCoord() + target->getCoord());
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

    if (move == "")
        cout << "can't prevent castling." << endl;

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
        if (othersMoves.size() != 0)
            moves = &othersMoves;
        else
        {
            if (shieldMoves.size() != 0)
                moves = &shieldMoves;
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
    string          testMove;
    vector<string>  legalMoves;
    vector<string>  newLegalMoves;

    legalMoves = getLegalMoves();

    for (int i = 0; i != legalMoves.size(); i++)
    {
        testMove = legalMoves.at(i);
        if (count(testMove.begin(), testMove.end(), 'O') == 0)
            testMove = testMove.c_str() + 1;

        tryMove(testMove);
        if (isCheck() == false)
            newLegalMoves.push_back(legalMoves.at(i));
        undoMove(testMove);
    }

    // trier

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
    vector<string>          legalMoves;
    vector<string>          moves;
    stack<chessPiece *>     orderedTargets;
    vector<chessPiece *>     targets;
    chessPiece              *target;
    chessPiece              *attackedOne;

    cout << "getting counter protect..." << endl;

    cout << "attacked :" << endl;
    for (int i = 0; i != _attackedAlly.size(); i++)
        cout << _attackedAlly.at(i)->getCoord() << "-" << _attackedAlly.at(i)->getType() << " ; ";
    cout << endl;

    orderedTargets = orderMaterialsByValue(_attackedAlly);
    while (orderedTargets.size() != 0)
        attackedOne = orderedTargets.top(), orderedTargets.pop();

    cout << "priority set for " << attackedOne->getCoord() << endl;

    legalMoves = getLegalMoves();

    string  testMove;
    int     attacked;
    bool    capture;

    for (int i = 0; i != legalMoves.size(); i++)
    {
        testMove = legalMoves.at(i);
        if (count(testMove.begin(), testMove.end(), 'O') == 0)
            testMove = testMove.c_str() + 1;

        capture = false;
        attacked = getAttackedNumber();
        if (_board.at(getAtValue(string(1, testMove[2]) + testMove[3])).piece != NULL)
            capture = true;

        tryMove(testMove);
        if (isProtected(attackedOne->getCoord()) == true && isProtected(string(1, testMove[2]) + testMove[3]) == true)
            moves.push_back(legalMoves.at(i));
        if (capture == true && attacked <= getAttackedNumber())
            moves.push_back(legalMoves.at(i));
        undoMove(testMove);
    }

    cout << "possible solutions :" << endl;
    for (int i = 0; i != moves.size(); i++)
        cout << moves.at(i) << " ; ";
    cout << endl;

    vector<string>  runAway;
    vector<string>  protectNormal;
    vector<string>  protectAttack;
    vector<string>  protectWithPawn;
    vector<string>  protectExchange;
    string          src;
    string          dest;

    for (int i = 0; i != moves.size(); i++)
    {
        src = string(1, moves.at(i)[1]) + moves.at(i)[2];
        dest = string(1, moves.at(i)[3]) + moves.at(i)[4];
        if (src == attackedOne->getCoord() && _board.at(getAtValue(dest)).piece == NULL)
            runAway.push_back(moves.at(i));
        else
        {
            if (_board.at(getAtValue(dest)).piece != NULL)
            {
                if (src == attackedOne->getCoord() && attackedOne->getType() == _board.at(getAtValue(dest)).piece->getType())
                    protectExchange.push_back(moves.at(i));
                else
                {
                    int attacked = getAttackedNumber();

                    cout << "attacked > " << attacked << endl;

                    tryMove(moves.at(i).c_str() + 1);
                    if (getAttackedNumber() < attacked)
                        protectAttack.push_back(moves.at(i)), cout << getAttackedNumber() << " < attacked now" << endl;
                    undoMove(moves.at(i).c_str() + 1);
                }
            }
            else
            {
                if (moves.at(i)[0] == 'P')
                    protectWithPawn.push_back(moves.at(i));
                else
                    protectNormal.push_back(moves.at(i));
            }
        }
    }

    if (moves.size() == runAway.size() && runAway.size() > 1
        && _gameInfo._turn < 21)
    {
        for (int i = 0; i != runAway.size() && runAway.size() > 1; i++)
        {
            if (runAway.at(i)[0] == 'N' || runAway.at(i)[0] == 'B')
            {
                if (_gameInfo._color == "white" && runAway.at(i)[4] == '1')
                    runAway.erase(runAway.begin() + i), i = 0;
                if (_gameInfo._color == "black" && runAway.at(i)[4] == '8')
                    runAway.erase(runAway.begin() + i), i = 0;
            }
        }
    }

    if (protectAttack.size() != 0)
    {
        while (orderedTargets.size() != 0)
            orderedTargets.pop();
        targets.clear();

        for (int i = 0; i != protectAttack.size(); i++)
        {
            string destCoords = string(1, protectAttack.at(i)[3]) + protectAttack.at(i)[4];
            targets.push_back(_board.at(getAtValue(destCoords)).piece);
        }

        orderedTargets = orderMaterialsByValue(targets);
        while (orderedTargets.size() != 0)
            target = orderedTargets.top(), orderedTargets.pop();
    }

    cout << runAway.size() << " solutions of runaway" << endl;
    cout << protectAttack.size() << " solutions of protectAttack" << endl;
    cout << protectWithPawn.size() << " solutions of protectWithPawn" << endl;
    cout << protectNormal.size() << " solutions of protectNormal" << endl;
    cout << protectExchange.size() << " solutions of protectExchange" << endl;

    srand(time(nullptr));

    if (protectAttack.size() >= 1 || protectExchange.size() >= 1)
    {
        if (protectAttack.size() >= 1)
        {
            for (int i = 0; i != protectAttack.size(); i++)
            {
                string dest = string(1, protectAttack.at(i)[3]) + protectAttack.at(i)[4];
                if (dest == target->getCoord())
                    return (protectAttack.at(i));
            }
        }
        if ((protectExchange.size() >= 1 && protectExchange.size() == moves.size()) || rand() % 2 == 0)
            return (protectExchange.at(0));
    }
    else
    {
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
