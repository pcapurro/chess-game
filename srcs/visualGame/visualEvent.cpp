#include "visualGame.hpp"

string	visualGame::waitForNewGame(void)
{
	SDL_Event	event;

	while (1)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN \
				&& event.key.keysym.sym == SDLK_RETURN)
				break ;

			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				_visualInfo._x = event.button.x, _visualInfo._y = event.button.y;

				if (_visualInfo._x > 782 && _visualInfo._y < 60)
				{
					if (event.type == SDL_MOUSEMOTION)
						SDL_SetCursor(_playCursor);
					if (event.type == SDL_MOUSEBUTTONDOWN)
						return ("restart");
				}
				else
					SDL_SetCursor(_normalCursor);
			}
		}
	}
	return ("error");
}

string  visualGame::waitForPromotion(void)
{
	int				select = 0;
	vector<char>	types;
	SDL_Event		event;

	types.push_back('Q'), types.push_back('B'), types.push_back('N'), types.push_back('R');
	SDL_Rect obj = getRectangle(_visualInfo._actualCoords, "promotion");

	displayPromotion(types.at(select), _visualInfo._actualCoords);

	while (1)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
				break ;

			_visualInfo._x = event.button.x, _visualInfo._y = event.button.y;
			string coords = getCoord(_visualInfo._x, _visualInfo._y);

			if (isAbovePromotion(_visualInfo._x, _visualInfo._y, obj) == true)
			{
				SDL_SetCursor(_playCursor);

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					int x = _visualInfo._x;
					int y = _visualInfo._y;

					if (x > obj.x && x < obj.x + 20 && y < obj.y + 50 && select != 0)
						select--;
					if (x > obj.x + 88 && x < (obj.x + obj.w) && y < obj.y + 50 && select != 3)
						select++;
					if (x > obj.x + 32 && x < (obj.x + obj.w) - 32 && y > obj.y + 50 && y < (obj.y + obj.h))
						return (_visualInfo._actualCoords + types.at(select));

					displayPromotion(types.at(select), _visualInfo._actualCoords);
				}
			}
			else
				SDL_SetCursor(_normalCursor);
		}
	}

	return ("error");
}

string	visualGame::waitForEvent(void)
{
	SDL_Event	event;

	while (1)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			_visualInfo._x = event.button.x, _visualInfo._y = event.button.y;
			if (_visualInfo._x > 850 || _visualInfo._x < 0 || _visualInfo._y > 800 || _visualInfo._y < 0)
				_visualInfo._x = 0, _visualInfo._y = 0;
			_visualInfo._actualCoords = getCoord(_visualInfo._x, _visualInfo._y);

			if (event.type == SDL_KEYDOWN)
				reactKeyDown(event.key.keysym.sym);

			if (event.type == SDL_MOUSEMOTION)
				reactMouseMotion();

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (_visualInfo._x > 780 && _visualInfo._y < 60)
					return ("restart");
				reactMouseDown(event.button.button);
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (_visualInfo._droppedSrc == _visualInfo._actualCoords)
					_visualInfo._clickSrc = _visualInfo._actualCoords, _visualInfo._droppedSrc.clear();
				else
					{ reactMouseUp(); return (getInput(_visualInfo._actualCoords)); }
			}

			displayGame(true);
		}
	}

	return ("error");
}
