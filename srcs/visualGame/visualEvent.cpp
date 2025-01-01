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
				visualInfo._x = event.button.x, visualInfo._y = event.button.y;

				if (visualInfo._x > 782 && visualInfo._y < 60)
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
	SDL_Rect obj = getRectangle(visualInfo._actualCoords, "promotion");

	displayPromotion(types.at(select), visualInfo._actualCoords);

	while (1)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
				break ;

			visualInfo._x = event.button.x, visualInfo._y = event.button.y;
			string coords = getCoord(visualInfo._x, visualInfo._y);

			if (isAbovePromotion(visualInfo._x, visualInfo._y, obj) == true)
			{
				SDL_SetCursor(_playCursor);

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					int x = visualInfo._x;
					int y = visualInfo._y;

					if (x > obj.x && x < obj.x + 20 && y < obj.y + 50 && select != 0)
						select--;
					if (x > obj.x + 88 && x < (obj.x + obj.w) && y < obj.y + 50 && select != 3)
						select++;
					if (x > obj.x + 32 && x < (obj.x + obj.w) - 32 && y > obj.y + 50 && y < (obj.y + obj.h))
						return (visualInfo._actualCoords + types.at(select));

					displayPromotion(types.at(select), visualInfo._actualCoords);
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

			visualInfo._x = event.button.x, visualInfo._y = event.button.y;
			if (visualInfo._x > 850 || visualInfo._x < 0 || visualInfo._y > 800 || visualInfo._y < 0)
				visualInfo._x = 0, visualInfo._y = 0;
			visualInfo._actualCoords = getCoord(visualInfo._x, visualInfo._y);

			if (event.type == SDL_KEYDOWN)
				reactKeyDown(event.key.keysym.sym);

			if (event.type == SDL_MOUSEMOTION)
				reactMouseMotion();

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (visualInfo._x > 780 && visualInfo._y < 60)
					return ("restart");
				reactMouseDown(event.button.button);
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (visualInfo._droppedSrc == visualInfo._actualCoords)
					visualInfo._clickSrc = visualInfo._actualCoords, visualInfo._droppedSrc.clear();
				else
					{ reactMouseUp(); return (getInput(visualInfo._actualCoords)); }
			}

			displayGame(true);
		}
	}

	return ("error");
}
