#include "../include/header.hpp"

void    systemError(void)
{
    printGradually("System error. Shutting down", 2);
    exit(1);
}

void    initWelcome(void)
{
    string  input;
    printTitle();
    getline(cin, input);
    if (cin.fail() == true)
        systemError();
    cout << "\033[2A" << ERASE_LINE << endl;
}

int main(int argc, char **argv)
{
    initWelcome();
    printLoading();

    string game [] = {"e4", "d6", "d4", "Nf6", "Nc3", "g6", "Be3", "Bg7", "Qd2", "c6", "f3", "b5", "Nge2",
                        "Nbd7", "Bh6", "Bxh6", "Qxh6", "Bb7", "a3", "e5", "O-O-O", "Qe7", "Kb1", "a6",
                        "Nc1", "O-O-O", "Nb3", "exd4", "Rxd4", "c5", "Rd1", "Nb6", "g3", "Kb8", "Na5",
                        "Ba8", "Bh3", "d5", "Qf4", "Ka7", "Rhe1", "d4", "Nd5", "Nbxd5", "exd5", "Qd6",
                        "Rxd4", "cxd4", "Re7", "Kb6", "Qxd4", "Kxa5", "b4", "Ka4", "Qc3", "Qxd5", "Ra7",
                        "Bb7", "Rxb7", "Qc4", "Qxf6", "Kxa3", "Qxa6", "Kxb4", "c3", "Kxc3", "Qa1", "Kd2",
                        "Qb2", "Kd1", "Bf1", "Rd2", "Rd7", "Rxd7", "Bxc4", "bxc4", "Qxh8", "Rd3", "Qa8",
                        "c3", "Qa4", "Ke1", "f4", "f5", "Kc1", "Rd2", "Qa7"}; //
    int i = 0; //

    chessBoard  *board;

    board = new chessBoard;
    if (board->isAllocated() == false)
        delete board, systemError();
    else
    {
        string          input;
        algebraicParser checker;

        while (board->isCheckMate() == false && board->isAllocated() == true)
        {
            board->announceEvent(1, checker.fail(), board->fail());
            cout << ERASE_LINE << "> ";
            // getline(cin, input); //
            input = game[i]; //
            cout << "playing... " << input << endl;
        
            if (cin.fail() == true)
                systemError();
            else
            {
                checker = input;
                if (checker.fail() == true)
                    exit(0);
                if (board->playMove(checker.getParsedMove()) == FAIL)
                    exit(0);
            }
            i++; //
            board->printBoard();
            checker.setTurn(board->getActualTurn());
        }
        board->announceEvent(5);
        delete board;
    }
    return (0);
}
