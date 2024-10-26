#include "../../include/shellChessVisual.hpp"
#include "visualGame/visualGame.hpp"

#include "../shell/chessBoard/chessBoard.hpp"

int validateArguments(const char *argOne, const char *argTwo)
{
    if (strlen(argOne) == 2 || strlen(argTwo) == 2
        || strlen(argOne) > 4 || strlen(argTwo) > 4)
        return (FAIL);
    else
    {
        for (int i = 0; argOne[i] != '\0'; i++)
        {
            if (isdigit(argOne[i]) == 0)
                return (FAIL);
        }
        for (int i = 0; argTwo[i] != '\0'; i++)
        {
            if (isdigit(argTwo[i]) == 0)
                return (FAIL);
        }
    }
    return (SUCCESS);
}    

int launchVisualGame(void *gameObjectPtr, void *chessBoardPtr)
{
    visualGame      *gameObject;
    chessBoard      *board;

    gameObject = (visualGame *)gameObjectPtr;
    board = (chessBoard *)chessBoardPtr;
    while (board->isGameOver() == false)
    {
        gameObject->loadBoard(board);
        gameObject->loadText();
        gameObject->displayFrame();

        if (gameObject->waitForEvent(board) == 1)
            return (1);

        if (board->playMove(gameObject->getInput()) == FAIL)
            continue ;
        else if (board->isAllocated() == false)
            return (1);
        gameObject->setTurn();
    }
    
    gameObject->loadBoard(board);
    gameObject->loadText(1);
    gameObject->displayFrame();

    board->printEndGame(1);

    return (0);
}

int main(const int argc, const char **argv)
{
    if ((argc != 1 && argc != 3)
        || (argc == 3 && validateArguments(argv[1], argv[2]) == FAIL))
    {
        cerr << "Error! Invalid arguments." << endl;
        cerr << "Usage: ./shell-chess [wWidth] [wHeight]" << endl;
        return (1);
    }
    else
    {
        visualGame      *gameObject;
        chessBoard      *board;

        gameObject = nullptr;
        if (argc != 1)
            gameObject = new (nothrow) visualGame(atoi(argv[1]), atoi(argv[2]));
        else
            gameObject = new (nothrow) visualGame;

        if (gameObject == nullptr)
            return (1);
        
        while (1)
        {
            board = new (nothrow) chessBoard;
            if (!board || board == nullptr)
                { delete gameObject; return (1); }
            if (board->isAllocated() == false)
                { delete board; delete gameObject; return (1); }

            if (launchVisualGame(gameObject, board) != 0)
                return (1);
            gameObject->setToDefault();

            if (gameObject->waitForNewGame() == 1)
                break ;
        }
    }
    return (0);
}

// https://alexandre-laurent.developpez.com/tutoriels/sdl-2/creer-premieres-fenetres/