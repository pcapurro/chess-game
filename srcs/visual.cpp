#include "../include/shellChess.hpp"
#include "visualGame/visualGame.hpp"

int launchVisualGame(void *gameObjectPtr, void *chessBoardPtr)
{
    visualGame      *gameObject;
    chessBoard      *board;

    gameObject = (visualGame *)gameObjectPtr;
    board = (chessBoard *)chessBoardPtr;
    while (board->isGameOver() == false)
    {
        gameObject->displayGame(board);
        if (gameObject->waitForEvent(board) == 1)
            { board->printEndGame(1); return (1); }

        if (board->playMove(gameObject->getInput()) == FAIL)
            continue ;
        else if (board->isAllocated() == false)
            return (1);
        gameObject->setTurn();
    }
    gameObject->displayGame(board);
    board->printEndGame(1);

    return (0);
}

int initializeVisualGame(void)
{
    visualGame      *gameObject;
    chessBoard      *board;

    gameObject = nullptr;
    gameObject = new (nothrow) visualGame;

    if (gameObject == nullptr)
        return (1);
    if (gameObject->isAllocated() == false)
        { delete gameObject; return (1); }
        
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
    return (0);
}
