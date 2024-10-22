#include "../../include/header.hpp"

void    chessBoard::printHistory(void)
{
    cout << ERASE_LINE << "Game summary: ";
    for (int i = 0; i != _history.size(); i++)
    {
        cout << i + 1 << "." << _history.at(i) << " ";
    }
    cout << endl;
}

void    chessBoard::printEndGame(void)
{
    string  player;

    player = getOppositeColor();
    player[0] = player[0] - 32;
    if (isCheckMate() == true)
    {
        cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Checkmate. " << player << " won the game! 🎉" << endl;
        printHistory();
    }
    else
    {
        cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Draw. " << player << " No one won the game." << endl;
        printHistory();
    }
}

void    chessBoard::printEvent(const int value, const bool cfail, const bool bfail, const string move)
{
    string  player;

    if (value == 1)
    {
        player = _color;
        player[0] = player[0] - 32;

        if (cfail == true || bfail == true)
            cout << player << " to play." << endl;
        else
            cout << ERASE_LINE << player << " to play." << endl;
    }
    if (value == 2)
    {
        player = getOppositeColor();
        player[0] = player[0] - 32;

        if (_turn != 0 && _turn != 1)
            cout << "\033[3A";
        else
            cout << "\033[2A";
        cout << ERASE_LINE;

        if (isCheck() == true)
            cout << player << " played " << move << ORANGE << " (check)." << COLOR_E << endl;
        else
            cout << player << " played " << move << "." << endl;
    }
}

void    chessBoard::printBoard(void)
{
    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[k] + to_string(i - 1);
            if (_board.at(getAtValue(coord)).piece != NULL)
            {
                if (_board.at(getAtValue(coord)).piece->getType() == 'P')
                    cout << "[P]";
                if (_board.at(getAtValue(coord)).piece->getType() == 'K')
                    cout << "[K]";
                if (_board.at(getAtValue(coord)).piece->getType() == 'Q')
                    cout << "[Q]";
                if (_board.at(getAtValue(coord)).piece->getType() == 'R')
                    cout << "[R]";
                if (_board.at(getAtValue(coord)).piece->getType() == 'N')
                    cout << "[N]";
                if (_board.at(getAtValue(coord)).piece->getType() == 'B')
                    cout << "[B]";
            }
            else
                cout << "[ ]";
        }
        cout << endl;
    }
    cout << endl;
}
