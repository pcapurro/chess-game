#ifndef VISUALGAME_HPP
# define VISUALGAME_HPP

# include "../../../include/shellChessVisual.hpp"

typedef struct s_textures
{
    SDL_Texture     *king;
    SDL_Texture     *queen;

    SDL_Texture     *bishop;
    SDL_Texture     *knight;
    SDL_Texture     *rook;

    SDL_Texture     *pawn;

}   t_textures;

class VisualGame
{
    public:

        VisualGame(const int width = 800, const int height = 800);
        ~VisualGame(void);

        void    initializeGame(void);

        void    loadWhiteTextures(void);
        void    loadBlackTextures(void);
        void    loadTexture(SDL_Texture *texture, const char *path);
        void    loadTextures(void);

        void    loadBoard(void);
        void    displayFrame(void);
    
    private:

        const int       _width;
        const int       _height;

        SDL_Window      *_mainWindow;
        SDL_Renderer    *_mainRenderer;

        SDL_Texture     *_boardTexture;
        SDL_Surface     *_baseSurface;
        t_textures      _whiteTextures;
        t_textures      _blackTextures;

        bool            _error;
        bool            _state;
};

#endif