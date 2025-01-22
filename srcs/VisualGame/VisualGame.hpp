#ifndef VISUALGAME_HPP
# define VISUALGAME_HPP

# include "../../includes/Visual.hpp"
# include "./VisualObjects.hpp"
# include "./VisualTexture.hpp"
# include "../ChessBoard/ChessBoard.hpp"
# include "../ChessAi/ChessAi.hpp"

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

class VisualGame
{
	public:

		VisualGame(const bool sandBoxMode);
		~VisualGame(void);

		void		visualRoutine(void);
		bool		fail(void) const
			{ return (_error); }

	private:

		void		initializeGame(void);
		void		setToDefault(void);
		void		setToNullPtr(void);

		void		loadTexts(void);
		void		loadLetters(void);
		void		loadNumbers(void);
		void		loadBoardTextures(void);
		void		loadWhiteTextures(void);
		void		loadBlackTextures(void);
		void		loadTextures(void);

		SDL_Texture*	getTexture(const char type, const string& color) const;
		SDL_Rect		getRectangle(const string& coords, const string& type = "") const;

		string		getKingCoords(const string& color) const;

		int			visualLoop(void);
		string		getVisualAnswer(void);

		bool		isCodeDetected(void) const;
		bool		isColorTargetZone(const int x, const int y) const;
		bool		isEvaluationTargetZone(const int x, const int y) const;
		bool		isBoardTargetZone(const string& coord, const int x, const int y) const;
		bool		isBoardZone(const int x, const int y) const;

		bool		isAbovePromotion(const int x, const int y, SDL_Rect& obj) const;
		bool		isPromotion(const string& coord) const;

		void		loadMap(void);
		void		loadHints(void);
		void		loadCoords(void);
		void		loadPath(void);
		void		loadEvaluation(const int value);
		void		loadScore(const string& color, const int y);
		void		loadCapturedComplex(vector<char> &captured, const string& color);
		void		loadCaptured(vector<char> &captured, const string& color);
		void		loadCaptures(void);
		void		loadMapColors(void);
		void		loadBoard(const string& color);
		void		loadText(const int value);
		void		loadCheck(void);
		void		loadDraw(void);
		void		loadCheckMate(void);

		void		displayPromotion(const char type, const string& coord);
		void		displayGame(const bool value = false);
		void		displayMoveAnimation(const string& move);
	
		void		reactKeyDown(const int key);
		void		reactMouseMotion(void);
		void		reactMouseDown(const int key);
		void		reactMouseUp(void);

		string		waitForEvent(void);
		string		waitForPromotion(void);
		string		waitForNewGame(void);

		string		getInput(const string& coord);

		string		getCoord(const int x, const int y) const;
		string		getTurnColor(void) const;

		vector<char>	getOrderedCaptured(const vector<char> &captured) const;

		const bool		_sandBoxMode;

		const int		_width;
		const int		_height;

		SDL_Window*		_mainWindow;
		SDL_Renderer*	_mainRenderer;

		SDL_Cursor*		_normalCursor;
		SDL_Cursor*		_playCursor;

		Textures*		_textures;

		ChessBoard*		_board;
		ChessAi*		_ai;

		VisualInfos		_visualInfo;

		bool			_error;
};

#endif