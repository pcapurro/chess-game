#include "visualGame.hpp"

string	visualGame::waitForNewGame(void)
{
	SDL_Event	event;

	while (1)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_RETURN)
				break ;

			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				_x = event.button.x, _y = event.button.y;

				if (_x > 782 && _y < 60)
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
	SDL_Rect obj = getRectangle(_actualCoords, "promotion");

	displayPromotion(types.at(select), _actualCoords);

	while (1)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
				break ;

			_x = event.button.x, _y = event.button.y;
			string coords = getCoord(_x, _y);

			if (isAbovePromotion(_x, _y, obj) == true)
			{
				SDL_SetCursor(_playCursor);

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					if (_x > obj.x && _x < obj.x + 20 && _y < obj.y + 50 && select != 0)
						select--;
					if (_x > obj.x + 88 && _x < (obj.x + obj.w) && _y < obj.y + 50 && select != 3)
						select++;
					if (_x > obj.x + 32 && _x < (obj.x + obj.w) - 32 && _y > obj.y + 50 && _y < (obj.y + obj.h))
						return (_actualCoords + types.at(select));

					displayPromotion(types.at(select), _actualCoords);
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
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			_x = event.button.x, _y = event.button.y;
			if (_x > 850 || _x < 0 || _y > 800 || _y < 0)
				_x = 0, _y = 0;
			_actualCoords = getCoord(_x, _y);

			if (event.type == SDL_KEYDOWN)
				reactKeyDown(event.key.keysym.sym);

			if (event.type == SDL_MOUSEMOTION)
				reactMouseMotion();

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (_x > 780 && _y < 60)
					return ("restart");
				reactMouseDown(event.button.button);
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (_droppedSrc == _actualCoords)
					_clickSrc = _actualCoords, _droppedSrc.clear();
				else
					{ reactMouseUp(); return (getInput(_actualCoords)); }
			}

			displayGame(true);
		}
	}

	return ("error");
}
