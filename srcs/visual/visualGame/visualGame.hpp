#ifndef VISUALGAME_HPP
# define VISUALGAME_HPP

# include "../../../include/shellChessVisual.hpp"
#include "../../shell/chessBoard/chessBoard.hpp"

typedef struct s_textures
{
    SDL_Texture     *king;
    SDL_Texture     *queen;

    SDL_Texture     *bishop;
    SDL_Texture     *knight;
    SDL_Texture     *rook;

    SDL_Texture     *pawn;

}   t_textures;

typedef struct s_texts
{
    SDL_Texture     *whiteWon;
    SDL_Texture     *blackWon;
    SDL_Texture     *whiteToPlay;
    SDL_Texture     *blackToPlay;
    SDL_Texture     *draw;

}   t_text;

class visualGame
{
    public:

        visualGame(const int width = 800, const int height = 800);
        ~visualGame(void);

        void        initializeGame(void);
        void        setToDefault(void);

        void        loadWhiteTextures(void);
        void        loadBlackTextures(void);
        void        loadTexture(const char type, \
                        const char color, const char *path);
        void        loadTextures(void);
        void        loadTexts(void);

        SDL_Texture *getTexture(const char type, const string color) const;
        SDL_Rect    getRectangle(const string coords);
    
        void        loadBoard(const chessBoard *board, const int cx = 0, const int cy = 0);
        void        loadText(const int value = 0);
        void        displayFrame(void);
    
        int         waitForEvent(const chessBoard *board);
        int         waitForNewGame(void);
        int         loadInput(const string coord, const chessBoard *board);
        t_move      getInput(void);
        string      getCoord(const int x, const int y);
        string      getTurnColor(void) const;
        
        void        setTurn(void) { _turn++; };

    private:

        const int       _width;
        const int       _height;

        SDL_Window      *_mainWindow;
        SDL_Renderer    *_mainRenderer;

        SDL_Cursor      *_normalCursor;
        SDL_Cursor      *_playCursor;

        SDL_Texture     *_boardTexture;
        SDL_Surface     *_baseSurface;
        t_textures      _whiteTextures;
        t_textures      _blackTextures;

        t_text          _texts;

        bool            _dropped;
        string          _sourceCoord;

        t_move          _input;
        int             _turn;

        bool            _error;
        bool            _state;
};

#endif