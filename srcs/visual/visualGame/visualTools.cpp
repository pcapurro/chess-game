#include "visualGame.hpp"

t_move  visualGame::getInput(void)
{
    _turn++;
    return (_input);
}

string  visualGame::getCoord(const int x, const int y)
{

    if (x > 0 && y > 0 && x >= _width / 10 && x <= _width / 10 * 9
        && y >= (_height / 10) && y <= (_height / 10 * 9))
    {
        int xZone;
        int yZone;

        for (int i = 0; i != 8; i++)
        {
            yZone = (_height / 10 ) * (i + 1);
            for (int k = 0; k != 8; k++)
            {
                xZone = (_width / 10 ) * (k + 1);
                if (x >= xZone && x <= xZone + (_width / 10 ) && y >= yZone && y <= yZone + (_height / 10 ))
                    return (string(1, "abcdefgh"[k]) + string(1, "87654321"[i]));
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
