#include "../../include/shellChessVisual.hpp"
#include "visualGame/visualGame.hpp"

int validateArguments(const char *arg1, const char *arg2)
{
    if (strlen(arg1) == 2 || strlen(arg2) == 2
        || strlen(arg1) > 4 || strlen(arg2) > 4)
        return (FAIL);
    else
    {
        for (int i = 0; arg1[i] != '\0'; i++)
        {
            if (isdigit(arg1[i]) == 0)
                return (FAIL);
        }
        for (int i = 0; arg2[i] != '\0'; i++)
        {
            if (isdigit(arg2[i]) == 0)
                return (FAIL);
        }
    }
    return (SUCCESS);
}    

int visualGame(void *gameObject)
{
    VisualGame  *gameObj;

    gameObj = (VisualGame *)gameObject;
    gameObj->displayFrame();
    // ...
    return (0);
}

int main(const int argc, const char **argv)
{
    cout << argc << endl;

    if ((argc != 1 && argc != 3)
        || (argc == 3 && validateArguments(argv[1], argv[2]) == FAIL))
    {
        cerr << "Error! Invalid arguments." << endl;
        cerr << "Usage: ./shell-chess [wWidth] [wHeight]" << endl;
        return (1);
    }
    else
    {
        VisualGame  *gameObject;

        gameObject = nullptr;
        if (argc != 1)
            gameObject = new (nothrow) VisualGame(atoi(argv[1]), atoi(argv[2]));
        else
            gameObject = new (nothrow) VisualGame;

        if (!gameObject || gameObject == nullptr)
            return (1);
        visualGame(gameObject);
    }
    return (0);
}

// https://alexandre-laurent.developpez.com/tutoriels/sdl-2/creer-premieres-fenetres/