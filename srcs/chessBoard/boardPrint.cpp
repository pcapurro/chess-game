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
        cout << "Checkmate. " << GREEN << player << " won the game! 🎉" << COLOR_E << endl;
    }
    else
    {
        cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Draw. No one won the game." << endl;
    }
    printHistory();
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

void    chessBoard::printPiece(const char type, const string color)
{
    if (type == 'P' && color == "white")
        cout << "[♟]";
    if (type == 'P' && color == "black")
        cout << "[♟]";

    if (type == 'N' && color == "white")
        cout << "[♞]";
    if (type == 'N' && color == "black")
        cout << "[♘]";

    if (type == 'B' && color == "white")
        cout << "[♝]";
    if (type == 'B' && color == "black")
        cout << "[♗]";

    if (type == 'R' && color == "white")
        cout << "[♜]";
    if (type == 'R' && color == "black")
        cout << "[♖]";

    if (type == 'Q' && color == "white")
        cout << "[♛]";
    if (type == 'Q' && color == "black")
        cout << "[♕]";

    if (type == 'K' && color == "white")
        cout << "[♚]";
    if (type == 'K' && color == "black")
        cout << "[♔]";
}

void    chessBoard::printBoard(void)
{
    int     atValue;
    char    type;
    string  color;
    string  coords;

    if (_turn != 0)
    {
        if (_turn == 1)
            cout << "\033[10A";
        else
            cout << "\033[9A";
        for (int i = 0; i != 10; i++)
            cout << ERASE_LINE;
    }

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = "abcdefgh"[k] + to_string(i - 1);
            atValue = getAtValue(coords);
            if (_board.at(atValue).piece != NULL)
            {
                type = _board.at(atValue).piece->getType();
                color = _board.at(atValue).piece->getColor();
                printPiece(type, color);
            }
            else
                cout << "[ ]";
        }
        cout << endl;
    }
    cout << endl;
}
