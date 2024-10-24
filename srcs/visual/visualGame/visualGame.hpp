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

        VisualGame(void);
        ~VisualGame(void);

        void    initializeGame(void);

        void    loadWhiteTextures(void);
        void    loadBlackTextures(void);
        void    loadTexture(SDL_Texture *texture, const char *path);
        void    loadTextures(void);

        void    displayFrame(void);
    
    private:

        SDL_Window      *mainWindow;
        SDL_Renderer    *mainRenderer;

        SDL_Texture     *boardTexture;
        SDL_Surface     *baseSurface;
        t_textures      whiteTextures;
        t_textures      blackTextures;

        bool            error;
        bool            state;
};

#endif