#include "../../include/header.hpp"

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

vector<string>  getKingSequence(const string move)
{
    vector<string>  coords;
    string          newCoords;

    newCoords = move;
    newCoords[1] = newCoords[1] + 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] - 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[0] = newCoords[0] - 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[0] = newCoords[0] + 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[0] = newCoords[0] + 1;
    newCoords[1] = newCoords[1] + 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[0] = newCoords[0] + 1;
    newCoords[1] = newCoords[1] - 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[0] = newCoords[0] - 1;
    newCoords[1] = newCoords[1] + 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[0] = newCoords[0] - 1;
    newCoords[1] = newCoords[1] - 1;
    coords.push_back(newCoords);

    return (coords);
}

vector<string>  getQueenSequence(const string move)
{
    vector<string>  coords;
    string          newCoords;

    for (int i = 1; i != 8; i++)
    {
        newCoords = move;
        newCoords[0] = newCoords[0] - (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[1] = newCoords[1] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[1] = newCoords[1] - (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] - (i * 1);
        newCoords[1] = newCoords[1] - (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] + (i * 1);
        newCoords[1] = newCoords[1] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] - (i * 1);
        newCoords[1] = newCoords[1] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] + (i * 1);
        newCoords[1] = newCoords[1] - (i * 1);
        coords.push_back(newCoords);
    }
    return (coords);
}

vector<string>  getRookSequence(const string move)
{
    vector<string>  coords;
    string          newCoords;

    for (int i = 1; i != 8; i++)
    {
        newCoords = move;
        newCoords[0] = newCoords[0] - (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[1] = newCoords[1] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[1] = newCoords[1] - (i * 1);
        coords.push_back(newCoords);
    }
    return (coords);
}

vector<string>  getBishopSequence(const string move)
{
    vector<string>  coords;
    string          newCoords;

    for (int i = 1; i != 8; i++)
    {
        newCoords = move;
        newCoords[0] = newCoords[0] - (i * 1);
        newCoords[1] = newCoords[1] - (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] + (i * 1);
        newCoords[1] = newCoords[1] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] - (i * 1);
        newCoords[1] = newCoords[1] + (i * 1);
        coords.push_back(newCoords);

        newCoords = move;
        newCoords[0] = newCoords[0] + (i * 1);
        newCoords[1] = newCoords[1] - (i * 1);
        coords.push_back(newCoords);
    }
    return (coords);
}

vector<string>  getKnightSequence(const string move)
{
    vector<string>  coords;
    string          newCoords;

    newCoords = move;
    newCoords[1] = newCoords[1] + 2;
    newCoords[0] = newCoords[0] - 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] + 2;
    newCoords[0] = newCoords[0] + 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] - 2;
    newCoords[0] = newCoords[0] - 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] - 2;
    newCoords[0] = newCoords[0] + 1;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] + 1;
    newCoords[0] = newCoords[0] - 2;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] - 1;
    newCoords[0] = newCoords[0] - 2;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] + 1;
    newCoords[0] = newCoords[0] + 2;
    coords.push_back(newCoords);

    newCoords = move;
    newCoords[1] = newCoords[1] - 1;
    newCoords[0] = newCoords[0] + 2;
    coords.push_back(newCoords);

    return (coords);
}

vector<string>  getPawnSequence(const string move, const int turn)
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
        coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[1] = newCoords[1] - 2;
        coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[0] = newCoords[0] - 1;
        newCoords[1] = newCoords[1] - 1;
        coords.push_back(newCoords);
    
        newCoords = newMove;
        newCoords[0] = newCoords[0] + 1;
        newCoords[1] = newCoords[1] - 1;
        coords.push_back(newCoords);
    }
    else
    {
        newCoords[1] = newCoords[1] + 1;
        coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[1] = newCoords[1] + 2;
        coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[0] = newCoords[0] + 1;
        newCoords[1] = newCoords[1] + 1;
        coords.push_back(newCoords);

        newCoords = newMove;
        newCoords[0] = newCoords[0] - 1;
        newCoords[1] = newCoords[1] + 1;
        coords.push_back(newCoords);
    }

    return (coords);
}
