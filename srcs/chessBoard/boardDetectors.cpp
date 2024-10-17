#include "../../include/header.hpp"

string  chessBoard::getQueenPath(const string src, const string dest)
{
    int src_x = src[0] - 97;
    int src_y = atoi(src.c_str() + 1);
    
    int dest_x = dest[0] - 97;
    int dest_y = atoi(dest.c_str() + 1);

    string  coords;
    string  newCoords;

    return (coords);
}

string  chessBoard::getRookPath(const string src, const string dest)
{
    int src_x = src[0] - 97;
    int src_y = atoi(src.c_str() + 1);
    
    int dest_x = dest[0] - 97;
    int dest_y = atoi(dest.c_str() + 1);

    string  coords;
    string  newCoords;

    for (int i = 0; i != 8; i++)
    {
        ;
    }
    return (coords);
}

string  chessBoard::getBishopPath(const string src, const string dest)
{
    int src_x = src[0] - 97;
    int src_y = atoi(src.c_str() + 1);
    
    int dest_x = dest[0] - 97;
    int dest_y = atoi(dest.c_str() + 1);

    string  coords;
    string  newCoords;

    for (int i = 0; i != 8; i++)
    {
        if (src_x < dest_x && src_y < dest_y)
            src_x++, src_y++;
        if (src_x > dest_x && src_y < dest_y)
            src_x--, src_y++;
        if (src_x > dest_x && src_y > dest_y)
            src_x--, src_y--;
        if (src_x < dest_x && src_y > dest_y)
            src_x++, src_y--;

        newCoords = newCoords + "abcdefgh"[src_x] + to_string(src_y);
        coords = coords + newCoords;
        if (isThereSomething(newCoords) == true || newCoords == dest)
            break ;
        newCoords.clear();
    }
    return (coords);
}

bool    chessBoard::isTheWayClear(const char type, const string src, const string dest)
{
    string  coords;

    if (type == 'B')
        coords = getBishopPath(src, dest);
    if (type == 'R')
        coords = getRookPath(src, dest);
    if (type == 'Q')
        coords = getQueenPath(src, dest);

    if (coords.find(dest) == string::npos)
        return (false);
    cout << "chemin possible" << endl;
    exit(0);
    return (true);
}