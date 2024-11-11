#include "../chessBoard.hpp"

size_t  chessBoard::getAtValue(const string coord) const
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).coord[0] == coord[0]
            && _board.at(i).coord[1] == coord[1])
            return (i);
    }
    return (0);
}

vector<string>  chessBoard::getPiecesCoords(void) const
{
    vector<string>  coords;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL)
            coords.push_back(_board.at(i).coord);
    }
    return (coords);
}

vector<string>  chessBoard::getAvailaibleMoves(void)
{
    char            type;
    string          move;
    vector<string>  legalMoves;
    vector<string>  availaibleMoves;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL 
                && _board.at(getAtValue(coord)).piece->getColor() == _gameInfo._color)
            {
                availaibleMoves = getPossibleMoves(coord);
                for (int j = 0; j != availaibleMoves.size(); j++)
                {
                    type = _board.at(getAtValue(coord)).piece->getType();
                    move = string(1, type) + availaibleMoves.at(j);
                    
                    if (move.at(move.length() - 1) == '8' || move.at(move.length() - 1) == '1' && type == 'P')
                        legalMoves.push_back(move + 'Q'), legalMoves.push_back(move + 'B'), \
                        legalMoves.push_back(move + 'N'), legalMoves.push_back(move + 'R');
                    else
                        legalMoves.push_back(move);
                }
                availaibleMoves.clear();
            }
        }
    }
    return (legalMoves);
}

vector<string>	chessBoard::getLegalMoves(void)
{
	vector<string>	legalMoves;
    vector<string>	newLegalMoves;

	legalMoves = getAvailaibleMoves();
    legalMoves.push_back("O-O"), legalMoves.push_back("O-O-O");
	for (int i = 0; i != legalMoves.size(); i++)
	{
        if (legalMoves.at(i) == "O-O-O" || legalMoves.at(i) == "O-O")
        {
            if (legalMoves.at(i) == "O-O-O")
                _gameInfo._lastMove.dest = "O-O-O";
            else
                _gameInfo._lastMove.dest = "O-O";
        }
        else
        {
            _gameInfo._lastMove.action = '-';
            _gameInfo._lastMove.obj = legalMoves.at(i)[0];
            
            _gameInfo._lastMove.src = string(1, legalMoves.at(i)[1]) + legalMoves.at(i)[2];
            _gameInfo._lastMove.dest = legalMoves.at(i).c_str() + 3;
        }
		
		if (isLegal() == true)
			newLegalMoves.push_back(legalMoves.at(i));
	}
	return (newLegalMoves);
}

vector<string>  chessBoard::getCastlingSrcsDests(const string srcdest)
{
    char            y;
    string          src;
    string          dest;
    vector<string>  srcsDests;

    _gameInfo._color == "white" ? y = '1' : y = '8';

    if (srcdest == "O-O")
    {
        src = string(1, 'e') + y, dest = string(1, 'g') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
        src = string(1, 'h') + y, dest = string(1, 'f') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
    }
    else
    {
        src = string(1, 'e') + y, dest = string(1, 'c') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
        src = string(1, 'a') + y, dest = string(1, 'd') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
    }

    cout << "pushing " << srcsDests.at(0) << " ; " << srcsDests.at(1) << endl;

    return (srcsDests);
}

char    chessBoard::getType(const string coord) const
{
    int     atValue;
    char    type;

    atValue = getAtValue(coord);
    type = ' ';
    if (coord != "none")
    {
        if (_board.at(atValue).piece != NULL)
            type = _board.at(atValue).piece->getType();
    }
    return (type);
}

string  chessBoard::getColor(const string coord) const
{
    int     atValue;
    string  color;

    atValue = getAtValue(coord);
    color = "none";
    if (coord != "none")
    {
        if (_board.at(atValue).piece != NULL)
            color = _board.at(atValue).piece->getColor();
    }
    return (color);
}

stack<chessPiece *> chessBoard::orderMaterialsByValue(vector<chessPiece *> materials)
{
    int                 value;
    stack<chessPiece *> stack;

    for (int i = 0; i != 4; i++)
    {
        for (int k = 0; k != materials.size(); k++)
        {
            if (i == 0 && materials.at(k)->getType() == 'Q')
                stack.push(materials.at(k));
            if (i == 1 && materials.at(k)->getType() == 'R')
                stack.push(materials.at(k));
            if (i == 2 && (materials.at(k)->getType() == 'B' || materials.at(k)->getType() == 'N'))
                stack.push(materials.at(k));
            if (i == 3 && materials.at(k)->getType() == 'P')
                stack.push(materials.at(k));
        }
    }
    return (stack);
}

int chessBoard::getStateValue(void) const
{
    if (_gameInfo._checkmate == true)
        return (1);
    if (_gameInfo._draw == true || isAllocated() == false)
        return (2);
    return (0);
}

int chessBoard::getMaterialValue(const char type)
{
    if (type == 'P')
        return (1);
    if (type == 'N' || type == 'B')
        return (3);
    if (type == 'R')
        return (5);
    if (type == 'Q')
        return (9);
    return (0);
}
