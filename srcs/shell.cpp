#include "../include/header.hpp"

void    initWelcome(void)
{
    string  input;
    printTitle();
    getline(cin, input);
    if (cin.fail() == true)
        systemError();
    cout << "\033[2A" << ERASE_LINE << endl;
}

void    shellGame(const int value)
{
    chessBoard  *board;

    board = new chessBoard;
    if (board->isAllocated() == false)
        delete board, systemError();
    else
    {
        string          input;
        algebraicParser checker;

        board->printBoard();
        while (board->isGameOver() == false)
        {
            board->printEvent(checker.fail(), board->fail());
            
            cout << ERASE_LINE << "> ";
            getline(cin, input);
            cout << "\033[1A";
        
            if (cin.fail() == true)
                systemError();
            else
            {
                checker = input;
                if (checker.fail() == true || board->playMove(checker.getParsedMove()) == FAIL)
                    continue ;
            }
            board->printBoard();
            checker.setTurn(board->getActualTurn());
        }
        board->printEndGame();
        delete board;
    }
}
