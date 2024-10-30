#include "visualGame.hpp"

int visualGame::loadInput(const string coord, const chessBoard *board)
{
    _input.obj = board->getType(_droppedSourceCoords);
    _input.src = _droppedSourceCoords;
    _input.dest = coord;

    if (_input.obj == 'K')
    {
        if ((_input.dest == "g1" && _input.src == "e1") || (_input.dest == "g8" && _input.src == "e8"))
            _input.dest = "O-O";
        if ((_input.dest == "c1" && _input.src == "e1") || (_input.dest == "c8" && _input.src == "e8"))
            _input.dest = "O-O-O";
    }

    if (_input.obj == 'P')
    {
        if (_input.dest[1] == '8' && _input.src[1] == '7'
            || _input.dest[1] == '1' && _input.src[1] == '2')
            _input.dest = _input.dest + 'Q';
    }

    _dropped = true;
    _droppedSourceCoords.clear();

    return (0);
}

int visualGame::waitForNewGame(void)
{
    SDL_Event   event;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
                && event.key.keysym.sym == SDLK_ESCAPE))
                return (1);
            
            if (event.key.keysym.sym == SDLK_RETURN)
                break ;

            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                setNewDimensions(event.window.data1, event.window.data2);
        }
    }
    return (0);
}

int visualGame::waitForEvent(const chessBoard *board)
{
    SDL_Event   event;
    string      coord;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
                && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN)))
                return (1);

            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP
                || event.type == SDL_MOUSEMOTION)
            {
                coord = getCoord(event.button.x, event.button.y);
                if (board->getType(coord) != ' ' && board->getColor(coord) == getTurnColor())
                {
                    SDL_SetCursor(_playCursor);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        _dropped = false, _droppedSourceCoords = coord;
                }
                else
                    SDL_SetCursor(_normalCursor);

                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    setNewDimensions(event.window.data1, event.window.data2);
                
                if (event.type == SDL_MOUSEBUTTONUP)
                    return (loadInput(coord, board));

                displayGame(board, event.button.x, event.button.y);
            }
        }
    }
    return (0);
}
