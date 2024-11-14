#ifndef VISUALGAME_HPP
# define VISUALGAME_HPP

# include "../../include/chessGame.hpp"
# include "../chessBoard/chessBoard.hpp"

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

        visualGame(const bool sandBoxMode);
        ~visualGame(void);

        void	    visualRoutine(void);
        bool        fail(void) const { return (_error); }

    private:

        void        initializeGame(void);
        void        setToDefault(void);
        void        setToNullPtr(void);

        void        loadTexts(void);
        void        loadBoardTextures(void);
        void        loadWhiteTextures(void);
        void        loadBlackTextures(void);
        void        loadArrowTexture(void);
        void        loadTexture(const char type, const char color, const char *path);
        void        loadTextures(void);

        SDL_Texture *getTexture(const char type, const string color) const;
        SDL_Rect    getRectangle(const string coords, const float fx = 0, \
                                    const float fy = 0, const string type = "") const;

        string      getKingCoords(const string color);

        int		    visualLoop(void);
        string      getVisualAnswer(void);
  
        void        loadBoard(const string color, const int cx = 0, const int cy = 0);
        void        loadText(const int value);
        void        loadArrow(const int value);
        void        loadCheck(void);
        void        loadDraw(void);
        void        loadCheckMate(void);
        void        loadMove(void);
        void        displayPromotion(const char type, const string coord);
        void        displayGame(const int cx = 0, const int cy = 0);
    
        string      waitForEvent(void);
        string      waitForPromotion(const string coord);
        int         waitForNewGame(void);

        string      getInput(const string coord);

        string      getCoord(const int x, const int y) const;
        string      getTurnColor(void) const;

        bool        isAbovePromotion(const int x, const int y, SDL_Rect obj);

        const bool		_sandBoxMode;

        const int       _width;
        const int       _height;

        SDL_Window      *_mainWindow;
        SDL_Renderer    *_mainRenderer;

        SDL_Cursor      *_normalCursor;
        SDL_Cursor      *_playCursor;

        SDL_Surface     *_baseSurface;
        int             _baseCheck;

        SDL_Texture     *_blackBoardTexture;
        SDL_Texture     *_whiteBoardTexture;
        SDL_Texture     *_checkMateWhiteTexture;
        SDL_Texture     *_checkMateBlackTexture;
        SDL_Texture     *_promotionTexture;
        SDL_Texture     *_arrowTexture;
        t_textures      _whiteTextures;
        t_textures      _blackTextures;
        t_text          _texts;

        chessBoard      *_board;

        string          _droppedSrc;
        string          _clickSrc;
        string          _droppedDest;

        string          _lastAiMove;

        int             _aiSide;
        int             _turn;

        bool            _error;
};

#endif