#include "../../include/header.hpp"
#include "../chessBoard/pieces/chessPiece.hpp"

bool    isChessDigit(const char c)
{
    if (c != '1' && c != '2' && c != '3' && c != '4'
        && c != '5' && c != '6' && c != '7' && c != '8')
        return (false);
    return (true);
}

bool    isChessPiece(const char c)
{
    if (c != 'K' && c != 'Q' && c != 'R'
        && c != 'B' && c != 'N')
        return (false);
    return (true);
}

bool    isChessCoord(const char c)
{
    if (c != 'a' && c != 'b' && c != 'c' && c != 'd'
        && c != 'e' && c != 'f' && c != 'g' && c != 'h')
        return (false);
    return (true);
}

string  algebraicParser::getLeftSequence(void) const
{
    string  left;

    for (int i = 0; _move.move[i] != '\0'; i++)
    {
        if (_move.move[i] == 'x' || _move.move[i] == '-')
            break ;
        left = left + _move.move[i];
    }
    return (left);
}

string  algebraicParser::getRightSequence(void) const
{
    string  right;

    for (int i = 0; _move.move[i] != '\0'; i++)
    {
        if (_move.move[i] == 'x' || _move.move[i] == '-')
        {
            right = _move.move.c_str() + i + 1;
            break ;
        }
    }
    if (right[right.length() - 1] == '#' || right[right.length() - 1] == '+')
        right.erase(right.length() - 1);
    return (right);
}

vector<string>  getKingSequence(const string move, const char sign)
{
    vector<string>  coords;
    string          newCoords;
    King            king('K', "white", move);

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            newCoords = "abcdefgh"[k] + to_string(i - 1);
            if (king.isOnMyWay(newCoords) == true
                && sign == 'i' || newCoords[0] == sign)
                coords.push_back(newCoords);
        }
    }
    return (coords);
}

vector<string>  getQueenSequence(const string move, const char sign)
{
    vector<string>  coords;
    string          newCoords;
    Queen           queen('Q', "white", move);

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            newCoords = "abcdefgh"[k] + to_string(i - 1);
            if (queen.isOnMyWay(newCoords) == true
                && sign == 'i' || newCoords[0] == sign)
                coords.push_back(newCoords);
        }
    }
    return (coords);
}

vector<string>  getRookSequence(const string move, const char sign)
{
    vector<string>  coords;
    string          newCoords;
    Rook            rook('R', "white", move);

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            newCoords = "abcdefgh"[k] + to_string(i - 1);
            if (rook.isOnMyWay(newCoords) == true
                && sign == 'i' || newCoords[0] == sign)
                coords.push_back(newCoords);
        }
    }
    return (coords);
}

vector<string>  getBishopSequence(const string move, const char sign)
{
    vector<string>  coords;
    string          newCoords;
    Bishop          bishop('B', "white", move);

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            newCoords = "abcdefgh"[k] + to_string(i - 1);
            if (bishop.isOnMyWay(newCoords) == true
                && sign == 'i' || newCoords[0] == sign)
                coords.push_back(newCoords);
        }
    }
    return (coords);
}

vector<string>  getKnightSequence(const string move, const char sign)
{
    vector<string>  coords;
    string          newCoords;
    Knight          knight('K', "white", move);

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            newCoords = "abcdefgh"[k] + to_string(i - 1);
            if (knight.isOnMyWay(newCoords) == true
                && sign == 'i' || newCoords[0] == sign)
                coords.push_back(newCoords);
        }
    }
    return (coords);
}

vector<string>  getPawnSequence(const string move, const int turn, const char sign)
{
    vector<string>  coords;
    string          newMove;
    string          newCoords;

    newMove = move;
    if (move.length() > 2)
        newMove.at(newMove.length() - 1) = '\0';

    newCoords = newMove;
    if (turn % 2 == 0)
    {
        newCoords[1] = newCoords[1] - 1;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[1] = newCoords[1] - 2;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[0] = newCoords[0] - 1;
        newCoords[1] = newCoords[1] - 1;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);
    
        newCoords = newMove;
        newCoords[0] = newCoords[0] + 1;
        newCoords[1] = newCoords[1] - 1;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);
    }
    else
    {
        newCoords[1] = newCoords[1] + 1;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[1] = newCoords[1] + 2;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[0] = newCoords[0] + 1;
        newCoords[1] = newCoords[1] + 1;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[0] = newCoords[0] - 1;
        newCoords[1] = newCoords[1] + 1;
        if (sign == 'i' || newCoords[0] == sign)
            coords.push_back(newCoords);
    }

    return (coords);
}
