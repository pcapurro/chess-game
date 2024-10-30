#include "visualGame.hpp"

string  visualGame::getCoord(const int x, const int y)
{
    int xZone;
    int yZone;

    if (x > 0 && y > 0 && x >= _width / 10 && x <= _width / 10 * 9
        && y >= (_height / 10) && y <= (_height / 10 * 9))
    {
        for (int i = 0; i != 8; i++)
        {
            if (_aiSide != 0)
                yZone = (_height / 10) * (i + 1);
            else
                yZone = (_height / 10) * (8 - i);

            for (int k = 0; k != 8; k++)
            {
                xZone = (_width / 10 ) * (k + 1);
                if (x >= xZone && x <= xZone + (_width / 10 ) && y >= yZone && y <= yZone + (_height / 10 ))
                    return (string(1, "abcdefgh"[k]) + string(1, "12345678"[i]));
            }
        }
    }
    return ("none");
}

string  visualGame::getTurnColor(void) const
{
    if (_turn % 2 != 0)
        return (string("white"));
    return (string("black"));
}
