#include "../chessBoard.hpp"

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

void    chessBoard::printWhiteBoard(void) const
{
    int     atValue;
    string  coords;

    for (int i = 9; i != 1; i--)
    {
        cout << ERASE_LINE << " " << i - 1 << " ";
        for (int k = 0; k != 8; k++)
        {
            coords = "abcdefgh"[k] + to_string(i - 1);
            atValue = getAtValue(coords);
            if (_board.at(atValue).piece != NULL)
            {
                char type = _board.at(atValue).piece->getType();
                string color = _board.at(atValue).piece->getColor();
                printPiece(type, color);
            }
            else
                cout << "│ ▕";
        }
        cout << " " << i - 1 << endl;
    }
}

void    chessBoard::printBlackBoard(void) const
{
    int     atValue;
    string  coords;

    for (int i = 1; i != 9; i++)
    {
        cout << ERASE_LINE << " " << i << " ";
        for (int k = 0; k != 8; k++)
        {
            coords = "abcdefgh"[k] + to_string(i);
            atValue = getAtValue(coords);
            if (_board.at(atValue).piece != NULL)
            {
                char type = _board.at(atValue).piece->getType();
                string color = _board.at(atValue).piece->getColor();
                printPiece(type, color);
            }
            else
                cout << "│ ▕";
        }
        cout << " " << i << endl;
    }
}

void    chessBoard::printBoard(const int aiSide) const
{
    if (_gameInfo._turn != 0)
        cout << "\033[12A";

    cout << ERASE_LINE << "    a  b  c  d  e  f  g  h" << endl;
    if (aiSide == -1 || aiSide == 1)
        printWhiteBoard();
    else
        printBlackBoard();
    cout << ERASE_LINE << "    a  b  c  d  e  f  g  h" << endl << endl ;
}


void    chessBoard::printHistory(void) const
{
    cout << ERASE_LINE;
    if (_history.size() > 21)
        cout << endl;
    
    if (_history.empty() != true)
    {
        cout << "Game summary: ";
        for (size_t i = 0; i != _history.size(); i++)
        {
            if (i != 0)
                cout << " ";
            cout << i + 1 << ".";
        
            if (_history.at(i).find('O') != string::npos)
            {
                if (_history.at(i).find("O-O") != string::npos)
                    cout << "O-O";
                if (_history.at(i).find("O-O-O") != string::npos)
                    cout << "O-O-O";
            }
            else
                cout << _history.at(i);
        }
        cout << endl << endl;
    }
}

void    chessBoard::printEndGame(const int value)
{
    string  player;

    _gameInfo._color == "white" ? player = "black" : player = "white";
    player[0] = player[0] - 32;
    if (isCheckMate() == true)
    {
        if (value == 0)
            cout << "\033[1A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Checkmate. " << GREEN << player << " won the game" << COLOR_E << "! 🎉" << endl;
    }
    if (isDraw() == true)
    {
        if (value == 0)
            cout << "\033[1A" << ERASE_LINE << endl << ERASE_LINE;
        cout << "Draw. " << GREY << "No one won the game" << COLOR_E << "." << endl;
    }
    printHistory();
}

void    chessBoard::printEvent(const bool cfail, const bool bfail, const bool blindMode)
{
    string  player;

    cout << ERASE_LINE;
    if (blindMode == true && _gameInfo._turn != 0)
        cout << "\033[1A" << ERASE_LINE;

    if (cfail == true || bfail == true)
    {
        if (blindMode == false)
            cout << "\033[1A" << ERASE_LINE;

        if (cfail == true)
            cout << RED << "Invalid move" << COLOR_E << ". ";
        else
            cout << YELLOW << "Illegal move" << COLOR_E << ". ";
    }
    if (_gameInfo._turn > 0)
    {
        _gameInfo._color == "white" ? player = "black" : player = "white";
        player[0] = player[0] - 32;

        if (cfail == false && bfail == false)
        {
            if (isCheck() == true)
                cout << player << " played " << _gameInfo._lastMove.move << ORANGE 
                    << " (check)" << COLOR_E << ". ";
            else
                cout << player << " played " << _gameInfo._lastMove.move << ". ";
        }
    }
    player = _gameInfo._color;
    player[0] = player[0] - 32;
    cout << player << " to play." << endl;
}
