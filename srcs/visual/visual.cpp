#include "../../include/shellChessVisual.hpp"
#include "visualGame/visualGame.hpp"

int     visualGame(void *gameObject)
{
    VisualGame  *gameObj;

    gameObj = (VisualGame *)gameObject;
    gameObj->displayFrame();
    return (0);
}

int main(const int argc, const char **argv)
{
    VisualGame  *gameObject;

    gameObject = new (std::nothrow) VisualGame;
    if (gameObject == nullptr)
        return (1);
    visualGame(gameObject);
    return (0);
}

// https://alexandre-laurent.developpez.com/tutoriels/sdl-2/creer-premieres-fenetres/