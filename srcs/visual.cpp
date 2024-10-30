#include "../include/shellChess.hpp"
#include "visualGame/visualGame.hpp"

int launchVisualGame(void *gameObjectPtr, void *chessBoardPtr, const bool sandBoxMode)
{
    visualGame      *gameObject;
    chessBoard      *board;

    gameObject = (visualGame *)gameObjectPtr;
    board = (chessBoard *)chessBoardPtr;
    while (board->isGameOver() == false)
    {
        gameObject->displayGame(board);
        if (gameObject->waitForEvent(board) == 1)
            { board->printEndGame(1); return (2); }

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

int initializeVisualGame(const bool sandBoxMode)
{
    visualGame      *gameObject;
    chessBoard      *board;

    gameObject = nullptr;
    gameObject = new (nothrow) visualGame;

    if (gameObject == nullptr)
        { memoryFailed(); return (1); }
    if (gameObject->isAllocated() == false)
        { memoryFailed(); delete gameObject; return (1); }
        
    while (1)
    {
        board = new (nothrow) chessBoard;
        if (!board || board == nullptr)
            { delete gameObject; memoryFailed(); return (1); }
        if (board->isAllocated() == false)
            { delete board, delete gameObject; memoryFailed(); return (1); }

        int value = launchVisualGame(gameObject, board, sandBoxMode);

        delete board;
        if (value == 1)
            { delete gameObject; memoryFailed(); return (1); }
        if (value == 2)
            { delete gameObject; return (0); }
            
        gameObject->setToDefault();
        if (gameObject->waitForNewGame() == 1)
            break ;
    }
    delete gameObject;

    return (0);
}
