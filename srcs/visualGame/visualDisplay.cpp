#include "visualGame.hpp"

void    visualGame::loadText(const int value)
{
    SDL_Rect    obj;
    string      color;
    
    if (_turn % 2 == 0)
        color = "white";
    else
        color = "black";

    obj.x = 215, obj.y = 14;
    obj.w = 392, obj.h = 51;
    if (value == 0)
    {
        if (color == "white")
            SDL_RenderCopy(_mainRenderer, _textures->texts.whiteToPlay.getTexture(), NULL, &obj);
        if (color == "black")
            SDL_RenderCopy(_mainRenderer, _textures->texts.blackToPlay.getTexture(), NULL, &obj);
    }
    if (value == 1)
    {
        if (color == "white")
            SDL_RenderCopy(_mainRenderer, _textures->texts.blackWon.getTexture(), NULL, &obj);
        if (color == "black")
            SDL_RenderCopy(_mainRenderer, _textures->texts.whiteWon.getTexture(), NULL, &obj);
    }

    if (value == 2)
        SDL_RenderCopy(_mainRenderer, _textures->texts.draw.getTexture(), NULL, &obj);
}

void    visualGame::loadEvaluation(const int value)
{
    SDL_Rect    activObj;
    SDL_Rect    evalObj;

    activObj.x = 25, activObj.y = 724;
    activObj.w = 30, activObj.h = 30;

    evalObj.x = 35, evalObj.y = 80;
    evalObj.w = 10, evalObj.h = 640;

    if (_evaluation == true && value == 0)
    {
        int score;

        SDL_SetRenderDrawColor(_mainRenderer, 76, 153, 0, 255);
        SDL_RenderFillRect(_mainRenderer, &activObj);

        if (_sandBoxMode == false && _aiSide % 2 == 0)
        {
            SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
            SDL_RenderFillRect(_mainRenderer, &evalObj);
            SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 255);
            score = _whiteScore;
        }
        else
        {
            SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 255);
            SDL_RenderFillRect(_mainRenderer, &evalObj);
            SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
            score = _blackScore;
        }

        if (_whiteScore + _blackScore == 0)
            _whiteScore = 50, _blackScore = 50, score = 50;

        evalObj.h = ((score * 640) / (_whiteScore + _blackScore));
        SDL_RenderFillRect(_mainRenderer, &evalObj);
    }
    else
    {
        SDL_SetRenderDrawColor(_mainRenderer, 153, 0, 0, 255);
        SDL_RenderFillRect(_mainRenderer, &activObj);

        SDL_SetRenderDrawColor(_mainRenderer, 164, 164, 164, 255);
        SDL_RenderFillRect(_mainRenderer, &evalObj);
    }
}

void    visualGame::loadMapColors(void)
{
    int         colors[COLOR_NB][3] = COLORS;
    SDL_Rect    obj;

    obj = getRectangle("", "default");

    _boardColors.clear();
    _boardColors.push_back(colors[_boardColor][0]);
    _boardColors.push_back(colors[_boardColor][1]);
    _boardColors.push_back(colors[_boardColor][2]);

    obj.w = 60, obj.h = 66;
    obj.x = 790, obj.y = 734;
    SDL_SetRenderDrawColor(_mainRenderer, _boardColors.at(0), _boardColors.at(1), _boardColors.at(2), 255);
    SDL_RenderFillRect(_mainRenderer, &obj);
}

void    visualGame::loadScore(string color, const int y)
{
    int         score;

    SDL_Rect    obj;
    SDL_Texture *texture;

    visualTexture *numbers[10] = {&_textures->numbers.zero, \
        &_textures->numbers.one, &_textures->numbers.two, \
        &_textures->numbers.three, &_textures->numbers.four, \
        &_textures->numbers.five, &_textures->numbers.six, \
        &_textures->numbers.seven, &_textures->numbers.eight, \
        &_textures->numbers.nine};

    if (color == "white")
        score = _board->getWhiteMaterialsScore() - _board->getBlackMaterialsScore();
    if (color == "black")
        score = _board->getBlackMaterialsScore() - _board->getWhiteMaterialsScore();

    if (score < 0)
        score = 0;

    obj = getRectangle("", string(1, color[0]) + "score");
    obj.y = y;

    texture = _textures->symbols.plus.getTexture();
    SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

    _sandBoxMode == false || _aiSide % 2 != 0 ? obj.y-- : obj.y++;

    string value = to_string(score);
    for (int i = 0; value[i] != '\0'; i++)
    {
        for (int k = 0; k != 10; k++)
        {
            if (numbers[k]->getId() == value[i])
                texture = numbers[k]->getTexture();
        }
        obj.x += 15;

        SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);
    }
}

void    visualGame::loadCapturedComplex(vector<char> &captured, const string color)
{
    SDL_Rect        obj;
    SDL_Texture     *texture;

    visualTexture *white[5] = {&_textures->whiteTextures.pawn, &_textures->whiteTextures.bishop, \
        &_textures->whiteTextures.knight, &_textures->whiteTextures.rook, &_textures->whiteTextures.queen};

    visualTexture *black[5] = {&_textures->blackTextures.pawn, &_textures->blackTextures.bishop, \
        &_textures->blackTextures.knight, &_textures->blackTextures.rook, &_textures->blackTextures.queen};

    if (color == "white")
        obj = getRectangle("", "wscore");
    if (color == "black")
        obj = getRectangle("", "bscore");

    obj.w = 33, obj.h = 33;
    for (size_t i = 0; i != captured.size(); i++)
    {
        for (int k = 0; k != 5; k++)
        {
            if (color == "white" && black[k]->getId() == captured.at(i))
                texture = black[k]->getTexture();
            if (color == "black" && white[k]->getId() == captured.at(i))
                texture = white[k]->getTexture();
        }

        SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

        obj.x += 10;
        if (captured.at(i) == 'R')
            obj.x += 15;
        if (captured.at(i) == 'B' || captured.at(i) == 'Q')
            obj.x += 21;
        if (captured.at(i) == 'N')
            obj.x += 5;

        if (obj.x >= 800 || i == captured.size() - 1
            || (i != captured.size() - 1 && captured.at(i) != captured.at(i + 1)))
        {
            obj.x = 760;
            if (color == "white")
                _aiSide % 2 == 0 ? obj.y += 40 : obj.y -= 40;
            if (color == "black")
                _aiSide % 2 == 0 ? obj.y -= 40 : obj.y += 40;
        }
    }

    loadScore(color, obj.y);
}

void    visualGame::loadCaptured(vector<char> &captured, const string color)
{
    SDL_Rect        obj;
    SDL_Texture     *texture;

    visualTexture *white[5] = {&_textures->whiteTextures.pawn, &_textures->whiteTextures.bishop, \
        &_textures->whiteTextures.knight, &_textures->whiteTextures.rook, &_textures->whiteTextures.queen};

    visualTexture *black[5] = {&_textures->blackTextures.pawn, &_textures->blackTextures.bishop, \
        &_textures->blackTextures.knight, &_textures->blackTextures.rook, &_textures->blackTextures.queen};

    visualTexture *numbers[10] = {&_textures->numbers.zero, \
        &_textures->numbers.one, &_textures->numbers.two, \
        &_textures->numbers.three, &_textures->numbers.four, \
        &_textures->numbers.five, &_textures->numbers.six, \
        &_textures->numbers.seven, &_textures->numbers.eight, \
        &_textures->numbers.nine};

    if (color == "white")
        obj = getRectangle("", "wscore");
    if (color == "black")
        obj = getRectangle("", "bscore");

    char object = ' ';

    for (size_t i = 0; i != captured.size(); i++)
    {
        if (object == ' ' || object != captured.at(i))
        {
            obj.w = 33, obj.h = 33;

            for (int k = 0; k != 5; k++)
            {
                if (color == "white" && black[k]->getId() == captured.at(i))
                    texture = black[k]->getTexture();
                if (color == "black" && white[k]->getId() == captured.at(i))
                    texture = white[k]->getTexture();
            }

            SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

            int value = count(captured.begin(), captured.end(), captured.at(i));
            string nb = to_string(value);

            obj.w = 14, obj.h = 35;
            obj.x += 20;

            for (int i = 0; nb[i] != '\0'; i++)
            {
                for (int k = 0; k != 10; k++)
                {
                    if (numbers[k]->getId() == nb[i])
                        texture = numbers[k]->getTexture();
                }
                obj.x += 15;
                SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);
            }

            obj.x = 760;
            if (color == "white")
                _aiSide % 2 == 0 ? obj.y += 40 : obj.y -= 40;
            if (color == "black")
                _aiSide % 2 == 0 ? obj.y -= 40 : obj.y += 40;

        }
        object = captured.at(i);
    }

    loadScore(color, obj.y);
}

void    visualGame::loadCaptures(void)
{
    vector<char>    whiteCaptured;
    vector<char>    blackCaptured;

    whiteCaptured = _board->getWhiteCaptured();
    blackCaptured = _board->getBlackCaptured();

    whiteCaptured = getOrderedCaptured(whiteCaptured);
    blackCaptured = getOrderedCaptured(blackCaptured);

    if (whiteCaptured.size() > 0)
        loadCaptured(whiteCaptured, "white");
    if (blackCaptured.size() > 0)
        loadCaptured(blackCaptured, "black");
}

void    visualGame::loadPath(void)
{
    SDL_Rect    obj;

    if (_droppedSrc != "")
    {
        obj = getRectangle(_droppedSrc);
        SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
        SDL_RenderFillRect(_mainRenderer, &obj);

        SDL_SetRenderDrawColor(_mainRenderer, 0, 255, 128, 100);
        SDL_RenderFillRect(_mainRenderer, &obj);
    }

    if (_lastMove != "")
    {
        obj = getRectangle(string(1, _lastMove[0]) + _lastMove[1]);
        SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
        SDL_RenderFillRect(_mainRenderer, &obj);

        SDL_SetRenderDrawColor(_mainRenderer, 204, 204, 0, 100);
        SDL_RenderFillRect(_mainRenderer, &obj);

        obj = getRectangle(string(1, _lastMove[2]) + _lastMove[3]);
        SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
        SDL_RenderFillRect(_mainRenderer, &obj);

        SDL_SetRenderDrawColor(_mainRenderer, 204, 204, 0, 100);
        SDL_RenderFillRect(_mainRenderer, &obj);
    }
}

void    visualGame::loadMap(void)
{
    SDL_Rect    obj;
    bool        state;

    loadMapColors();
    obj = getRectangle("", "default");
    SDL_RenderCopy(_mainRenderer, _textures->boardTexture.getTexture(), NULL, &obj);

    state = true;
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coords = string(1, "hgfedcba"[k]) + string(1, "87654321"[i]);

            if ((state == true && k % 2 == 0)
                || (state == false && k % 2 != 0))
            {
                obj = getRectangle(coords);
                SDL_SetRenderDrawColor(_mainRenderer, _boardColors.at(0), _boardColors.at(1), _boardColors.at(2), 255);
                SDL_RenderFillRect(_mainRenderer, &obj);
            }
        }
        state = !state;
    }
}

void    visualGame::loadCoords(void)
{
    SDL_Rect    obj;
    string      coords;

    visualTexture *letters[8] = {&_textures->letters.h, &_textures->letters.g, \
        &_textures->letters.f, &_textures->letters.e, \
        &_textures->letters.d, &_textures->letters.c, \
        &_textures->letters.b, &_textures->letters.a};

    visualTexture *numbers[8] = {&_textures->numbers.one, &_textures->numbers.two, \
        &_textures->numbers.three, &_textures->numbers.four, \
        &_textures->numbers.five, &_textures->numbers.six, \
        &_textures->numbers.seven, &_textures->numbers.eight};

    for (int i = 0; i != 8; i++)
    {
        coords = string(1, "hgfedcba"[i]) + "1";
        obj = getRectangle(coords, "coordsl");
        SDL_RenderCopy(_mainRenderer, letters[i]->getTexture(), NULL, &obj);

        coords = string(1, 'h') + "12345678"[i];
        obj = getRectangle(coords, "coordsn");
        SDL_RenderCopy(_mainRenderer, numbers[i]->getTexture(), NULL, &obj);
    }

    if (_x >= 105 && _x <= 745 && _y >= 80 && _y <= 720
        && _visualCoords == true && _actualCoords != "none" && _actualCoords != ""
        && (_sandBoxMode == true || ((_aiSide % 2 == 0 && _turn % 2 != 0) || (_aiSide % 2 != 0 && _turn % 2 == 0))))
    {
        SDL_Texture *texture;

        obj.w = 28, obj.h = 18;
        obj.x = _x - 28, obj.y = _y - 18;

        SDL_SetRenderDrawColor(_mainRenderer, 192, 192, 192, 255);
        SDL_RenderFillRect(_mainRenderer, &obj);

        for (int i = 0; i != 8; i++)
        {
            if (letters[i]->getId() == _actualCoords[0])
                texture = letters[i]->getTexture();
        }

        obj.w = 10, obj.h = 27;

        obj.x += 3, obj.y = obj.y - 5;
        SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

        for (int i = 0; i != 8; i++)
        {
            if (numbers[i]->getId() == _actualCoords[1])
                texture = numbers[i]->getTexture();
        }

        obj.x += 12;
        SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);
    }
}

void    visualGame::loadBoard(const string color)
{
    char        objType;
    string      coords;
    string      objColor;
    SDL_Rect    obj;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = string(1, "hgfedcba"[k]) + string(1, "87654321"[i]);
            objType = _board->getType(coords);
            objColor = _board->getColor(coords);

            if (objType != ' ' && objColor == color && coords != _droppedDest)
            {
                if (coords != _droppedSrc)
                {
                    obj = getRectangle(coords);
                    obj.h = 80, obj.w = 80;

                    if (obj.x > 0 && obj.y > 0 && obj.x < _width && obj.y < _height)
                        SDL_RenderCopy(_mainRenderer, getTexture(objType, objColor), NULL, &obj);
                }
            }
        }
    }

    if (_x != -1 && _y != -1)
    {
        objType = _board->getType(_droppedSrc);
        objColor = _board->getColor(_droppedSrc);

        obj.x = _x - 28, obj.y = _y - 40;
        SDL_RenderCopy(_mainRenderer, getTexture(objType, objColor), NULL, &obj);
    }

}

void    visualGame::loadCheck(void)
{
    string      color;
    string      kingCoords;
    SDL_Rect    obj;

    _turn % 2 == 0 ? color = "white" : color = "black";
    kingCoords = getKingCoords(color);
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 242, 255, 0, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);
}

void    visualGame::loadDraw(void)
{
    string      color;
    SDL_Rect    obj;

    _turn % 2 == 0 ? color = "white" : color = "black";
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 128, 128, 128, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    _turn % 2 == 0 ? color = "black" : color = "white";
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 128, 128, 128, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);
}

void    visualGame::loadCheckMate(void)
{
    string      color;
    string      kingCoords;
    SDL_Rect    obj;

    _turn % 2 == 0 ? color = "white" : color = "black";
    kingCoords = getKingCoords(color);
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 215, 0, 21, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    obj = getRectangle(kingCoords);
    obj.h = obj.h / 3, obj.w = obj.w / 3;
    SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);

    color == "white" ? color = "black" : color = "white";
    kingCoords = getKingCoords(color);
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 0, 190, 60, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    obj = getRectangle(kingCoords);
    obj.h = obj.h / 3, obj.w = obj.w / 3;
    SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);
}

void    visualGame::displayMoveAnimation(const string move)
{
    int         destX, destY;
    string      src, dest;
    SDL_Rect    obj;

    src = string(1, move[0]) + move[1];
    dest = string(1, move[2]) + move[3];

    obj.x = getRectangle(src).x;
    obj.y = getRectangle(src).y;

    destX = getRectangle(dest).x;
    destY = getRectangle(dest).y;

    _droppedSrc = src;
    while (obj.y != destY || obj.x != destX)
    {
        if ((src[0] == dest[0] && src[1] != dest[1]) || (src[0] != dest[0] && src[1] != dest[1]))
            destY > obj.y ? obj.y++ : obj.y--;
        if ((src[0] != dest[0] && src[1] == dest[1]) || (src[0] != dest[0] && src[1] != dest[1]))
            destX > obj.x ? obj.x++ : obj.x--;

        _x = obj.x + 28, _y = obj.y + 40;
        displayGame(true);
        usleep(500);
    }
}

void    visualGame::displayPromotion(const char type, const string coord)
{
    SDL_Rect    obj;
    string      color;

    _x = -1, _y = -1;
    displayGame();

    _turn % 2 == 0 ? color = "white" : color = "black";

    obj = getRectangle(coord);
    SDL_RenderCopy(_mainRenderer, getTexture(type, color), NULL, &obj);

    obj = getRectangle(coord, "promotion");
    SDL_RenderCopy(_mainRenderer, _textures->promotion.getTexture(), NULL, &obj);

    SDL_RenderPresent(_mainRenderer);
}

void    visualGame::displayGame(const bool value)
{
    SDL_RenderClear(_mainRenderer);

    loadEvaluation(_board->getStateValue());

    loadMap();
    loadPath();

    loadCaptures();

    if (_board->isItCheckMate() == true)
        loadCheckMate();
    else if (_board->isItCheck() == true)
        loadCheck();
    else if (_board->isItDraw() == true)
        loadDraw();

    if (_turn % 2 == 0)
        loadBoard("black"), loadBoard("white");
    else
        loadBoard("white"), loadBoard("black");

    loadCoords();

    loadText(_board->getStateValue());

    if (value == true)
        SDL_RenderPresent(_mainRenderer);
}
