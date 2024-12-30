#ifndef VISUALGAME_HPP
# define VISUALGAME_HPP

# include "../../includes/visual.hpp"
# include "./visualTexture.hpp"
# include "../chessBoard/chessBoard.hpp"
# include "../chessAi/chessAi.hpp"

# define WIDTH 850
# define HEIGHT 800

# define COLOR_NB 7

# define COLORS \
{ \
    {0, 135, 0}, \
    {0, 0, 153}, \
    {153, 0, 0}, \
    {205, 102, 0}, \
    {90, 0, 90}, \
    {128, 64, 0}, \
    {160, 160, 160} \
}

typedef struct s_pieces
{
    visualTexture     king;
    visualTexture     queen;

    visualTexture     bishop;
    visualTexture     knight;
    visualTexture     rook;

    visualTexture     pawn;

}   t_pieces;

typedef struct s_texts
{
    visualTexture     whiteWon;
    visualTexture     blackWon;
    visualTexture     whiteToPlay;
    visualTexture     blackToPlay;
    visualTexture     draw;

}   t_text;

typedef struct s_letters
{
    visualTexture   a;
    visualTexture   b;
    visualTexture   c;
    visualTexture   d;

    visualTexture   e;
    visualTexture   f;
    visualTexture   g;
    visualTexture   h;

}   t_letters;

typedef struct s_numbers
{
    visualTexture zero;
    visualTexture one;
    visualTexture two;
    visualTexture three;
    visualTexture four;

    visualTexture five;
    visualTexture six;
    visualTexture seven;
    visualTexture eight;
    visualTexture nine;

}   t_numbers;

typedef struct s_symbols
{
    visualTexture plus;

    visualTexture checkMateWhite;
    visualTexture checkMateBlack;

}   t_symbols;

typedef struct s_textures
{
    visualTexture   boardTexture;
    visualTexture   promotion;

    t_pieces        whiteTextures;
    t_pieces        blackTextures;

    t_letters       letters;
    t_numbers       numbers;

    t_symbols       symbols;

    t_text          texts;

}   t_textures;

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
        void        loadLetters(void);
        void        loadNumbers(void);
        void        loadBoardTextures(void);
        void        loadWhiteTextures(void);
        void        loadBlackTextures(void);
        void        loadTextures(void);

        SDL_Texture *getTexture(const char type, const string color) const;
        SDL_Rect    getRectangle(const string coords, const string type = "") const;

        string      getKingCoords(const string color);

        int		    visualLoop(void);
        string      getVisualAnswer(void);

        bool        isCodeDetected(void);
        bool        isColorTargetZone(const string coord, const int x, const int y);
        bool        isEvaluationTargetZone(const string coord, const int x, const int y);
        bool        isBoardTargetZone(const string coord, const int x, const int y);

        bool        isAbovePromotion(const int x, const int y, SDL_Rect obj);
        bool        isPromotion(const string coord);

        void        loadMap(void);
        void        loadCoords(void);
        void        loadPath(void);
        void        loadEvaluation(const int value);
        void        loadScore(string color, const int y);
        void        loadCapturedComplex(vector<char> &captured, const string color);
        void        loadCaptured(vector<char> &captured, const string color);
        void        loadCaptures(void);
        void        loadMapColors(void);
        void        loadBoard(const string color);
        void        loadText(const int value);
        void        loadCheck(void);
        void        loadDraw(void);
        void        loadCheckMate(void);

        void        displayPromotion(const char type, const string coord);
        void        displayGame(void);
        void        displayMoveAnimation(const string move);
    
        void        reactKeyDown(const int key);
        void        reactMouseMotion(void);
        void        reactMouseDown(const int key);
        void        reactMouseUp(void);

        string      waitForEvent(void);
        string      waitForPromotion(void);
        string      waitForNewGame(void);

        string      getInput(const string coord);

        string      getCoord(const int x, const int y) const;
        string      getTurnColor(void) const;

        vector<char>    getOrderedCaptured(const vector<char> &captured);

        const bool		_sandBoxMode;

        const int       _width;
        const int       _height;

        int             _boardColor;
        vector<int>     _boardColors;

        bool            _evaluation;
        int             _whiteScore;
        int             _blackScore;

        bool                _code;
        vector<SDL_Keycode> _keyHistory;

        SDL_Window      *_mainWindow;
        SDL_Renderer    *_mainRenderer;

        SDL_Cursor      *_normalCursor;
        SDL_Cursor      *_playCursor;

        t_textures      *_textures;

        chessBoard      *_board;
        chessAi         *_ai;

        int             _x;
        int             _y;

        string          _droppedSrc;
        string          _clickSrc;
        string          _droppedDest;

        bool            _visualCoords;
        string          _actualCoords;

        string          _lastAiMove;
        string          _lastMove;

        int             _aiSide;
        int             _turn;

        bool            _error;
};

#endif