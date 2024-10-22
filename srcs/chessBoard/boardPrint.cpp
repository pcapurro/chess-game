#include "../../include/header.hpp"

void    chessBoard::printPiece(const char type, const string color) const
{
    if (type == 'P' && color == "white")
        cout << "│♟▕";
    if (type == 'P' && color == "black")
        cout << "│♙▕";

    if (type == 'N' && color == "white")
        cout << "│♞▕";
    if (type == 'N' && color == "black")
        cout << "│♘▕";

    if (type == 'B' && color == "white")
        cout << "│♝▕";
    if (type == 'B' && color == "black")
        cout << "│♗▕";

    if (type == 'R' && color == "white")
        cout << "│♜▕";
    if (type == 'R' && color == "black")
        cout << "│♖▕";

    if (type == 'Q' && color == "white")
        cout << "│♛▕";
    if (type == 'Q' && color == "black")
        cout << "│♕▕";

    if (type == 'K' && color == "white")
        cout << "│♚▕";
    if (type == 'K' && color == "black")
        cout << "│♔▕";
}

void    chessBoard::printBoard(void) const
{
    int     atValue;
    char    type;
    string  color;
    string  coords;

    if (_turn != 0)
        cout << "\033[12A";
    cout << ERASE_LINE << "    a  b  c  d  e  f  g  h" << endl;
    for (int i = 9; i != 1; i--)
    {
        cout << ERASE_LINE << " " << i - 1 << " ";
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
                cout << "│ ▕";
        }
        cout << " " << i - 1 << endl;
    }
    cout << ERASE_LINE << "    a  b  c  d  e  f  g  h" << endl << endl ;
}


void    chessBoard::printHistory(void) const
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

    _color == "white" ? player = "black" : player = "white";
    player[0] = player[0] - 32;
    if (isCheckMate() == true)
    {
        cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Checkmate. " << GREEN << player << " won the game! 🎉" << COLOR_E << endl;
        printHistory();
    }
    if (isDraw() == true)
    {
        cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Draw. No one won the game." << endl;
        printHistory();
    }
}

void    chessBoard::printEvent(const bool cfail, const bool bfail, const int value)
{
    string  player;

    cout << ERASE_LINE;
    if (value == 3 && _turn != 0)
        cout << "\033[1A" << ERASE_LINE;

    if (cfail == true || bfail == true)
    {
        if (value != 3)
            cout << "\033[1A" << ERASE_LINE;

        if (cfail == true)
            cout << RED << "Invalid move. " << COLOR_E;
        else
            cout << YELLOW << "Illegal move. " << COLOR_E;
    }
    if (_turn > 0)
    {
        _color == "white" ? player = "black" : player = "white";
        player[0] = player[0] - 32;

        if (cfail == false && bfail == false)
        {
            if (isCheck() == true)
                cout << player << " played " << _lastMove.move << ORANGE << " (check). " << COLOR_E;
            else
                cout << player << " played " << _lastMove.move << ". ";
        }
    }
    player = _color;
    player[0] = player[0] - 32;
    cout << player << " to play." << endl;
}
