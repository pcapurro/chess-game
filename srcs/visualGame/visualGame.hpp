#ifndef VISUALGAME_HPP
# define VISUALGAME_HPP

# include "../../include/shellChess.hpp"
#include "../chessBoard/chessBoard.hpp"

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

        void        initializeGame(void);
        void        setToDefault(void);
        void        setToNullPtr(void);

        void	    visualRoutine(void);
        int		    visualLoop(void);

        string      getVisualAnswer(void);

        bool        fail(void) const { return (_error); }

        void        setNewDimensions(const int width, const int height) \
                    { _width = width, _height = height; };

        void        loadBoardTextures(void);
        void        loadWhiteTextures(void);
        void        loadBlackTextures(void);
        void        loadArrowTexture(void);
        void        loadTexture(const char type, \
                        const char color, const char *path);
        void        loadTextures(void);
        void        loadTexts(void);

        SDL_Texture *getTexture(const char type, const string color) const;
        SDL_Rect    getRectangle(const string coords);
    
        void        loadBoard(const int cx = 0, const int cy = 0);
        void        loadText(const int value);
        void        loadArrow(const int value);
        void        displayGame(const int cx = 0, const int cy = 0);
    
        int         waitForEvent();
        int         waitForNewGame(void);
        int         loadInput(const string coord);
        t_move      getInput(void) { return (_input); };
        string      getCoord(const int x, const int y);
        string      getTurnColor(void) const;
        
        void        setTurn(void) { _turn++; };

    private:

        int             _width;
        int             _height;

        SDL_Window      *_mainWindow;
        SDL_Renderer    *_mainRenderer;

        SDL_Cursor      *_normalCursor;
        SDL_Cursor      *_playCursor;

        SDL_Surface     *_baseSurface;
        int             _baseCheck;

        SDL_Texture     *_blackBoardTexture;
        SDL_Texture     *_whiteBoardTexture;
        SDL_Texture     *_arrowTexture;
        t_textures      _whiteTextures;
        t_textures      _blackTextures;
        t_text          _texts;

        chessBoard      *_board;

		const bool		_sandBoxMode;

        bool            _dropped;
        string          _droppedSourceCoords;

        int             _aiSide;

        t_move          _input;
        int             _turn;
        string          _aiColor;

        bool            _error;
};

#endif